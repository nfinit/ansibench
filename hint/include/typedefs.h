/******************************************************************************/
/* "HINT" -- Hierarchical INTegration.                                        */
/* Copyright (C) 1994 by Iowa State University Research Foundation, Inc.      */
/*                                                                            */
/* Files needed for use:                                                      */
/*     * hint.c             ---- Driver source                                */
/*     * hkernel.c          ---- Kernel source                                */
/*     * hint.h             ---- General include file                         */
/*     * typedefs.h         ---- Include file for DSIZE and ISIZE             */
/*     * README             ---- These are the rules. Follow them!!!          */
/******************************************************************************/
/******************************************************************************/
/*      Defines                                                               */
/******************************************************************************/
#define NOERROR    0      /* Self explanatory                                 */
#define DISCRET    1      /* Error condition for out of discretization error  */
#define NOMEM      2      /* Error for out of memory                          */
/******************************************************************************/
/*      Type Defines                                                          */
/******************************************************************************/

#define QMSIZE long

#if defined(LDOUBLE)
#define DSIZE long double
#define DFILE "longdouble"

#elif defined(DOUBLE)
#define DSIZE double
#define DFILE "double"
#define DSIZEF REAL*8
#define MPI_DSIZE MPI_DOUBLE

#elif defined(FLOAT)
#define DSIZE float
#define DFILE "float"
#define DSIZEF REAL*4
#define MPI_DSIZE MPI_FLOAT

#elif defined(LONG)
#define DSIZE long
#define DFILE "long"
#define DSIZEF INTEGER*4

#elif defined(INT)
#define DSIZE int
#define DFILE "int"
#define DSIZEF INTEGER
#define MPI_DSIZE MPI_INT

#elif defined(SHORT)
#define DSIZE short
#define DFILE "short"
#define DSIZEF INTEGER*2

#elif defined(CHAR)
#define DSIZE char
#define DFILE "char"
#define DSIZEF INTEGER*1
#endif

#if defined(ILONG)
#define ISIZE long
#define ISIZEF INTEGER*4

#elif defined(IINT)
#define ISIZE int
#define ISIZEF INTEGER
#endif
