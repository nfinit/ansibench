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

#include "hint.h"

DSIZE
Hint(DSIZE *scx, DSIZE *scy, DSIZE *dmax, ISIZE *mcnt, RECT *rect, 
                           DSIZE *errs, ISIZE *ixes, ERROR *eflag)
{
    DSIZE   errio,       /* Error value for io                                */
            errjo,       /* Error value for jo                                */
            sh,          /* Sum of areas, high bound                          */
            sl,          /* Sum of areas, low bound                           */
            tm,          /* Temporary value for computing function            */
            tm2;         /* Temporary value for doubling tm                   */

    ISIZE   inc, jnc,    /* Indices of queue positions                        */
            io,          /* Index of left child                               */
            iq,          /* Index of end of the sorted error queue            */
            it,          /* Iteration counter                                 */
            itmp,        /* Temporary                                         */
            jo,          /* Index of right child                              */
            ma;          /* Index of parent                                   */


   /* Initialize the first interval.                                          */
      rect[0].xl = (DSIZE)0;    
      rect[0].xr = *scx;      
      rect[0].dx = *scx;     
      rect[0].fll = *scy;   
      rect[0].flh = *scy;  
      rect[0].frl = (DSIZE)0;
      rect[0].frh = (DSIZE)0;
      rect[0].ahi = *dmax;
      rect[0].alo = (DSIZE)0;
      iq = 0;
      errs[iq] = rect[0].ahi - rect[0].alo;
      ixes[iq] = iq;      
      sh = rect[0].ahi;
      sl = rect[0].alo;

      for (it = 0; ((it < *mcnt - 1) && (it <= iq)); it++) 
      {
          io = ma = ixes[it];        /* Head of list has maximum error        */
          jo = it + 1;               /* Find right child index                */

          tm = rect[ma].dx; 
       /* Since dx is always a power of 2, it halves evenly.                  */
          rect[io].dx  = rect[jo].dx = tm / (DSIZE)2;

       /* Right child gets right boundary.                                    */
          rect[jo].xr  = rect[ma].xr;
       /* New point in the middle is shared by child subintervals             */
          rect[io].xr  = rect[io].xl + 
                         rect[io].dx; 
          rect[jo].xl  = rect[io].xr;
       /* Right child gets right f value upper and lower bounds               */
          rect[jo].frl = rect[ma].frl;
          rect[jo].frh = rect[ma].frh;
       /* Note that the left child simply inherits much of its info from ma.  */

       /* This is the function evaluation.                                    */
          tm =  (*scx + rect[io].xr); 
          tm2 = (*scy * (*scx - rect[io].xr));
          itmp = tm2 / tm;
          rect[io].frl = itmp;

       /* Here we need boolean true == 1. Otherwise use if's.                 */
          rect[io].frh = rect[io].frl + ((tm * rect[io].frl) != tm2);
          rect[jo].fll = rect[io].frl;
          rect[jo].flh = rect[io].frh;

       /* Compute the left daughter error.                                    */
          tm = (rect[io].fll - rect[io].frh) * (rect[io].dx - (DSIZE)2);
          if (tm < (DSIZE)0)
              tm = (DSIZE)0;
          errio = (rect[io].flh - rect[io].frh  + 
                   rect[io].fll - rect[io].frl) * 
                  (rect[io].dx - (DSIZE)1) - tm;

       /* Repeat for the right daughter.                                      */
          tm = (rect[jo].fll - rect[jo].frh) * (rect[jo].dx - (DSIZE)2);
          if (tm < (DSIZE)0)
              tm = (DSIZE)0;
          errjo = (rect[jo].flh - rect[jo].frh  + 
                   rect[jo].fll - rect[jo].frl) * 
                  (rect[jo].dx - (DSIZE)1) - tm;

       /* Compute indices for io and jo on the queue.                         */
       /* This is done with a boolean. If boolean true is not 1 use if's.     */
          inc = (errio < errjo) + 1;
          jnc = 3 - inc;

       /* Put on both io and jo. If one is zero we will not use it.           */
          errs[iq + inc] = errio;
          ixes[iq + inc] = io;
          errs[iq + jnc] = errjo;
          ixes[iq + jnc] = jo;

       /* Decide how much to increment iq. Again we need boolean true == 1.   */
          iq = iq + (errs[iq + 2] != 0) + 1;

       /* Remove parent sum contributions. Replace with child contributions.  */
          tm = rect[ma].alo;
          rect[io].alo = rect[io].frl * rect[io].dx;
          rect[jo].alo = rect[jo].frl * rect[jo].dx;
          sl -= tm;                    
          sl += rect[io].alo + rect[jo].alo; 
          tm = rect[ma].ahi;
          rect[io].ahi = rect[io].flh * rect[io].dx;
          rect[jo].ahi = rect[jo].flh * rect[jo].dx;
          sh -= tm;
          sh += rect[io].ahi + rect[jo].ahi;
      }
      if (it > iq) {
          *eflag = DISCRET;
	  }
      else {
#pragma mips_frequency_hint FREQUENT
          *eflag = NOERROR;
	  }
      return  (sh - sl);
}
