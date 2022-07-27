/******************************************************************************/
/* "HINT" -- Hierarchical INTegration.                                        */
/* Copyright (C) 1994 by Iowa State University Research Foundation, Inc.      */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation.  You should have received a copy of the      */
/* GNU General Public License along with this program; if not, write to the   */
/* Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.    */
/*                                                                            */
/* Files needed for use:                                                      */
/*     * hint.c             ---- Driver source                                */
/*     * hkernel.c          ---- Kernel source                                */
/*     * hint.h             ---- General include file                         */
/*     * typedefs.h         ---- Include file for DSIZE and ISIZE             */
/*     * README             ---- These are the rules. Follow them!!!          */
/******************************************************************************/

/* Refer to hint.h and typedefs.h for all-capitalized definitions.            */
#include       "hint.h"    

/* 2022-07-26: An apparent bug in some versions of ARM GCC erroneously
 * optimizes out some variables in this section causing the initialization to
 * hang determining DMAX. Because it is not essential to the benchmark itself,
 * GCC optimization is disabled for this section                              */
#pragma GCC push_options
#pragma GCC optimize ("O0")
int main(int argc, char *argv[])
{
    FILE    *curv;        /* Output file for QUIPS curve                      */
#ifndef DEBUG
    char    filnm[80];    /* Output file name                                 */
#endif
    Speed   qdata[NSAMP]; /* Array to keep track of QUIPs and time            */

    ERROR   eflag;        /* Stopping condition returned from Hint            */

    ISIZE   imax,         /* Maximum representable index                      */
            itm,          /* Scratch values to find imax                      */
            n,            /* Number of goal subintervals                      */
            nscout;       /* Number of survey subintervals                    */

	volatile
	ISIZE   itm2;         /* Scratch to prevent use of registers              */
 
    volatile
    DSIZE   tm1;          /* Scratch to prevent use of registers              */

    DSIZE   dmax,         /* Maximum associative whole number                 */
            gamut,        /* Range of result from Hint, high minus low bound  */
            scx,          /* Scale factor for x values                        */
            scy,          /* Scale factor for y values                        */
            tm, tm2;      /* Scratch values to find dmax                      */

	double  memref,
			bandwt;

    double  delq,         /* Change in Quality                                */
			quips,        /* QUality Improvement Per Second                   */
            qpnet,        /* Net QUIPS; integral of QUIPS d(log t)            */
            qpeak,        /* Peak QUIPS attained                              */
            qprat,        /* Ratio of current QUIPS to peak QUIPS             */
			qptmp,        /* QUIPS temporary for calculating Net QUIPS        */
            t,            /* Time for a given trial                           */
            t0,           /* Starting time                                    */
            t1,           /* Ending time                                      */
            tdelta,       /* Timer resolution                                 */
            /* tlast, */       /* Time of last recorded trial                      */
            tscout;       /* Time for initial survey                          */

    int     dbits,        /* Number of bits of accuracy for dmax              */
            ibits,        /* Number of bits for imax                          */
            i, j, k,      /* Loop counters                                    */
            laps,         /* Approximate number of laps in a trial            */
            memuse;       /* Amount of memory used, in bytes                  */

    printf("         _    _\n");
    printf("         |    |  _ _   _ _____ TM\n");
    printf("         |--  |  | |\\  | | | |\n");
    printf("         |  --|  | | \\ |   |\n");
    printf("         |    |  | |  \\|   |\n");
    printf("         ^    ^  ^ ^   ^   ^\n\n");
    printf("*** The  HINT  PERFORMANCE ANALYZER ***\n");
    printf("   Version 1.0.1  June 1994-July 2022\n");
    printf("   John L. Gustafson & Quinn O. Snell\n");
    printf("     Scalable Computing Laboratory\n");
    printf("   236 Wilhelm, Iowa State University\n");
    printf("        Ames, Iowa    50011-3020\n");
    printf("            (515) 294 - 9294\n\n");
    printf("Copyright (C) 1994");
    printf(" Iowa State University Research Foundation, Inc.\n");
    printf("Modified for strict ANSI C compatibility 07/2022\n");
    printf("Please send results and questions to: hint@scl.ameslab.gov\n");
    printf("When sending results please follow the form in README\n");
    printf("________________________________________________________\n");
/* 2022-07-26: Notify user the program does not take arguments
 *             (this resolves unused parameter warnings)                      */
  if (argc > 1) printf("NOTE: This program does not take arguments.\n"); 
	printf("RECT is %d bytes\n",sizeof(RECT));
#ifdef DEBUG
    curv = stdout;
#else
    sprintf(filnm,"data/%s",DFILE);
    if ((curv = fopen(filnm, "w")) == NULL)
    {
        printf("Could not open data file\n");
        exit(1);
    }
#endif

 /* Attempt to find timer resolution. Loop until the time changes.            */
    for (t0 = When(); ((t1 = When()) == t0););
    tdelta = t1 - t0;

 /* Find the largest associative whole number, dmax.                          */
    dbits = 0;
    tm = (DSIZE)1;
    tm2 = tm + tm;
    tm1 = tm2 + 1;
 /* Double until it fails to increment or it overflows.                       */
    while (((tm1 - tm2) == (DSIZE)1) && (tm2 > (DSIZE)0)) 
    {
        dbits++;
        tm  += tm;
        tm2 += tm2;
        tm1  = tm2 + 1;
    }
    dbits++;
 /* We use a grid of dmax + 1 squares, but this might overflow, so back off 1.*/
    dmax = tm + (tm - 1);
    printf("Apparent number of bits of accuracy: %d\n", dbits);   
    printf("Maximum associative whole number:    %.0f\n",(double)dmax);

 /* Find the largest representable index number.                              */
    ibits = 0;
    itm = (ISIZE)1;
    itm2 = itm + itm;
 /* Double it until it overflows.                                             */
    while (itm2 > (ISIZE)0) 
    {
        ibits++;
        itm  += itm;
        itm2 += itm2;
    }
    imax = itm;
    printf("Maximum number of bits of index:     %d\n", ibits);     
    printf("Maximum representable index:         %.0f\n\n", (double)imax); 

 /* Calculate usable maxima, from whichever is most restrictive.              */
    if ((ibits + ibits) < dbits)
    {
        dmax = (DSIZE)imax * (DSIZE)imax - 1;
        dbits = ibits + ibits;
    }
    printf("Index-limited data accuracy:         %d bits\n", dbits); 
    printf("Maximum usable whole number:         %.0f\n",(double)dmax);

 /* Half the bits, biased downward, go to x.                                  */
    j = (dbits)/2;         

 /* Now loop to take 2 to the appropriate power for grid dimensions.          */
    for (i = 0, scx = 1; i < j; scx += scx, i++);
    for (i = 0, scy = 1; i < dbits - j; scy += scy, i++);
    printf("Grid: %.0f wide by %.0f high.\n",(double)scx,(double)scy);

 /* 2022-07-26: Initialize tscout to 0 to fix compiler warnings               */
    tscout = 0; 

 /* This loop is used as a survey.                                            */
    for (nscout = NMIN, laps = 3; nscout < scx; )
    {
        t = Run(laps, &gamut, scx, scy, dmax, nscout, &eflag);

        if (eflag != NOERROR)
        {
            nscout /= 2;
            break;
        }
        else if ((t > RUNTM) && (eflag == NOERROR))
        {
            tscout = t;
            break;
        }
        else
        {
            tscout =  t;
            nscout *= 2;
            if (nscout > scx)
            {
                nscout /= 2;
                break;
            }
        }
    }
    if (tscout == 0)
    {
        printf( "Data type for %s is too small\n", argv[0]);
        exit(0);
    }
    if ((tscout < RUNTM) && (eflag == NOMEM))
       printf("Memory is not sufficient for > %3.1f second runs.\n",
                                                                         RUNTM);
    else if (tscout < RUNTM)
       printf("Precision is not sufficient for > %3.1f second runs.\n",
                                                                         RUNTM);

 /* This loop is the main loop driver of the HINT kernel.                     */
    for (t = 0, i = 0, n = NMIN, qpeak = 0, qprat = 1; 
        ((i < NSAMP) && (t < STOPTM) && (n < scx) && (qprat > STOPRT));
        i++, n = ((int)(n * ADVANCE) > n)? (n * ADVANCE) : n + 1)
    {     
        printf(".");
        fflush(stdout);

     /* Use enough laps to fill RUNTM time, roughly.                          */
        laps = MAX(RUNTM * nscout / (tscout * n), 1);
        t = Run(laps, &gamut, scx, scy, dmax, n, &eflag);
        if (t == 0)
            t = tdelta;

        if (eflag != NOERROR)
            break;
            
     /* Calculate QUIPS. We must add 1 to dmax, but do it in steps.           */
     /* This is to avoid overflow of dmax                                     */
		delq = (double)dmax / gamut - 1;
        quips = delq / t + 1.0 / gamut / t;
        qdata[i].t  = t;
        qdata[i].qp = quips;
        qdata[i].delq = delq;
        qdata[i].n  = n;
        qpeak = MAX(qpeak, quips);
        qprat = quips / qpeak;
    }
    memuse = (int)(qdata[i-1].n * (sizeof(RECT)+sizeof(DSIZE)+sizeof(ISIZE)));
    if ((qprat > STOPRT) && (eflag == NOMEM))
        #if defined(ILONG)
        printf("\nThis run was memory limited at %ld subintervals -> %d bytes\n",
        #else
        printf("\nThis run was memory limited at %d subintervals -> %d bytes\n",
        #endif
                                                 n, memuse);
    printf("\nDone with first pass. Now computing net QUIPS\n");

	memref = (DSREFS * sizeof(DSIZE) + ISREFS * sizeof(ISIZE)) * qdata[i-1].n;
	memref /= (1024 * 1024);
	bandwt = memref / qdata[i-1].t;
    fprintf(curv,"%12.10f %f %f %f %10d %f\n", 
            qdata[i-1].t, qdata[i-1].qp, qdata[i-1].delq,
            (double)qdata[i-1].n, memuse, bandwt);
    
 /* Now go backwards through the data to calculate net QUIPS, and filter data.*/
    for (qpnet = qdata[i-1].qp, j = i - 2; j >= 0; j--)
    {
     /* If more work takes less time, we need to rerun the case of less work. */
        for (k = 0; ((qdata[j+1].t < qdata[j].t) && (k < PATIENCE)); k++)
        {
            printf("#"); /* todi */
            laps  = MAX(RUNTM * nscout / (tscout * qdata[j].n), 1);
            t = Run(laps, &gamut, scx, scy, dmax, qdata[j].n, &eflag);
            if (t == 0)
                t = tdelta;

	    delq = (double)dmax / gamut - 1;
            quips = delq / t + 1.0 / gamut / t;
            qdata[j].t  = t;
            qdata[j].qp = quips;
        }
        if (qdata[j+1].t < qdata[j].t)
        {
            #if defined(ILONG)
            printf(" Forcing a time for %ld subintervals\n", qdata[j].n);
            #else
            printf(" Forcing a time for %d subintervals\n", qdata[j].n);
            #endif
            qdata[j].t  = qdata[j+1].t;
			delq = (double)dmax / gamut - 1;
            qdata[j].qp = delq / qdata[j].t + 1.0 / gamut / qdata[j].t;
        }
        memuse = (int)(qdata[j].n * (sizeof(RECT)+sizeof(DSIZE)+sizeof(ISIZE)));
		memref = (DSREFS * sizeof(DSIZE) + ISREFS * sizeof(ISIZE)) * qdata[j].n;
		memref /= (1024 * 1024);
		bandwt = memref / qdata[j].t;
        fprintf(curv,"%12.10f %f %f %f %10d %f\n", 
                qdata[j].t, qdata[j].qp, qdata[j].delq,
                (double)qdata[j].n, memuse, bandwt);

     /* Now calculate the addition to the net QUIPS.                          */
     /* This is calculated as the sum of QUIPS(j) * (1 - time(j) / time(j+1)).*/
        qptmp = qdata[j].qp * qdata[j].t / qdata[j+1].t;
        qpnet += (qdata[j].qp - qptmp);
    }
    printf("\nFinished with %f net QUIPs\n", qpnet);
    fclose(curv);
    return 0;
}
#pragma GCC push_options

double
Run(int laps,
    DSIZE *gamut, DSIZE scx, DSIZE scy, DSIZE dmax, ISIZE memry, ERROR *eflag)
{
    RECT    *rect=NULL;   /* Array for saving hierarchical information        */
    ISIZE   *ixes=NULL;   /* Array for indices of queued entries              */
    DSIZE   *errs=NULL;   /* Array of error values                            */
 
    int     i, j;         /* Loop counters                                    */

    double  t0, t1, tm,   /* Time variables                                   */
            mint = 1e32;  /* Minimum time recorded for a given run            */

    *eflag = NOERROR;

 /* Allocate the memory for the arrays.                                       */
    rect = (RECT  *)malloc((MSIZE)(memry * sizeof(RECT)));
    errs = (DSIZE *)malloc((MSIZE)(memry * sizeof(DSIZE) * 2));
    ixes = (ISIZE *)malloc((MSIZE)(memry * sizeof(ISIZE) * 2));

 /* If the memory is unavailable, free what was allocated and return.         */
    if ((rect == NULL) || (errs == NULL) || (ixes == NULL))
    {
        if (rect != NULL)
            free(rect);
        if (errs != NULL)
            free(errs);
        if (ixes != NULL)
            free(ixes);
        *eflag = NOMEM;
        return (-NOMEM);
    }

    for (i = 0; i < NTRIAL; i++)
    {
        t0 = When();

     /* Run the benchmark for this trial.                                     */
        for (j = 0; j < laps; j++)
            *gamut = Hint(&scx, &scy, &dmax, &memry, rect, errs, ixes, eflag);

        t1 = When();

     /* Track the minimun time thus far for this trial.                       */
        tm = (t1 - t0) / laps;
        mint = MIN(mint, tm);
    }

 /* Free up the memory.                                                       */
    free(rect);
    free(errs);
    free(ixes);

    return (mint);
}
    
/* Return the current time in seconds, using a double precision number.       */
double
When(void)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}
