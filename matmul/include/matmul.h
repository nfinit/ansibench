#define MATMUL
#include <stdio.h>
/* MATMUL.H   HEADER FILE FOR USE WITH MATMUL.C

*******************************************************************************

  This is the Header file for MATMUL

  MATMUL is an interactive program that sets up, carries out,
  and times a matrix multiplication.  MATMUL can use several different
  algorithms and matrix sizes, and can be run on many different computers.

  The original MATMUL was written by John Burkardt of the Pittsburgh
  Supercomputing Center.

  This C version was created by Paul Puglielli of the Piitsburgh
  Supercomputing Center.


*******************************************************************************
  Making a version for a given machine:
  If on a UNIX machine, use the "make.csh" script to compile the most optimized
  executable possible.

  On VMS use the make.com script

  On the PC enter the line "#define MACHINE IBM_PC to the top of the matmul.h
  header file and compiler with any C Compiler.
******************************************************************************/

#define MAXPLT 250  /* NUMBER OF RUNS POSSIBLE */

/** MACHINE TYPES **/
#define CRAY        0
#define CM2         1
#define DEC_ULTRIX  2
#define VAX_VMS     3
#define IBM_PC      4
#define APPLE_MAC   5
#define HP_9000     6
#define VAX_STATION 7
#define IBM_RS6     8
#define MAX_MACH    9

/** Set LENA to a maximum depending on type of MACHINE **/
#if MACHINE == APPLE_MAC
#define LENA   128
#elif MACHINE == CRAY
#define LENA   512
#elif MACHINE == IBM_PC
#define LENA   128
#elif MACHINE == IBM_RS6
#define LENA   256
#elif MACHINE == VAX_STATION
#define LENA  128
#elif MACHINE == HP_9000
#define LENA  512
#define _INCLUDE_HPUX_SOURCE
#else
#define LENA   256
#endif


#define TRUE  1
#define FALSE 0

#define NROLL 4
const char LASTMOD[10]="25-MAR-92";
/* All GLOBAL variables are listed here. */
char cplot[MAXPLT][10],  /* array to hold commands             */
     command[30],       /* string to hold current command     */
     order[15],          /* type of Multiplication order       */
     filed[15],         /* data file name string              */
     filee[45],         /* explain file name.  string         */
     fileh[15],         /* string for help file name          */
     filei[15],         /* string for ".inp" file name        */
     fileo[15],         /* string for ".out" file name        */
     output[80],        /* buffer for output                  */
     machine[MAX_MACH][80]; /* string table of Machine names*/


FILE *ifiled,           /* file pointer for ".dat" file       */
     *ifilee,           /* file pointer for explain file      */
     *ifileh,           /* file pointer for help file         */
     *ifilei,           /* file pointer for ".inp" file       */
     *ifileo;           /* file pointer for ".out" file       */

int
    n=16,
    ilo,
    ihi,
    ido,
    nlo,
    nhi,
    ninc,
    nmult,
    lda= LENA ,
    ierr,
    iplot,
    lplot[MAXPLT],
    noplot[MAXPLT],
    nplot[MAXPLT];


#if MACHINE == VAX_VMS
int
#else
long
#endif
     sec1,             /* second part of start time                */
     sec2,             /* second part of end time                  */
     micro1,           /* microsecond part of start time           */
     micro2,           /* microsecond part of end time             */
     tot_seconds,      /* total seconds a multiplication took      */
     tot_microseconds; /* total microseconds a multiplication took */

/* these shorts are used as LOGICALS*/
short ashow,
      cshow,
      fshow,
      lshow,
      nshow,
      tshow,
      mshow,
      langshow,
      noshow;

float
      a[LENA][LENA], /* Array A destination of B*C*/
      b[LENA][LENA], /* Array B */
      c[LENA][LENA], /* Array C */
      aplot[MAXPLT], /* hold values of A(n,n) for each run */
      tplot[MAXPLT], /* hold values of TIME for each run   */
      fplot[MAXPLT]; /* hold value of MFLOPS for each run  */


