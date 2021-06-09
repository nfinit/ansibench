# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <time.h>

# define MACHINE APPLE_MAC

# include "matmul.h"

void abortm ( );
void chop(char*,int,int);
void Docom();
void Explain ( );
void Flclos ( );
void Flopen ( );
void Gbye ( );
void Getcom ( );
void Getlda(char*);
void Getn(char*);
void Getord(char*, int*);
void Getsho(char* ,int);
void Hello ( );
void Help ( );
void Init ( );
int  min(int,int);
void Mult ( );
int Nstep ( );
void Pdump ( );
void Printr ( );
void Putinp();
void Putout();
void Record ( );
void Result(short lchop);
#if MACHINE == VAX_VMS
void second(int*);
#elif MACHINE ==  IBM_PC
void second(long*);
#elif MACHINE ==  IBM_RS6
void second(long*);
#elif MACHINE ==  CRAY
extern float SDOT();
extern SAXPY();
extern SGEMM();
void second(long*);
#else
void second(long*,long*);
#endif
void Setval ( );
void Shoord ( );
void taxpy(int n,float *sa,float *sx,int  incx,float *sy,int incy);
void _TDOT();
float tdot();
void TSTART ( );
void TSTOP ( );
void TMSTART ( );
void TMSTOP ( );
void Zero ( int len );

/******************************************************************************/

int main ( )

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for MATMUL.

  Discussion:

    MATMUL is an interactive C program that sets up, carries out,
    and times a matrix multiplication.  MATMUL can use several different
    algorithms and matrix sizes, and can be run on many different computers.

    The main program is very simple.

    First some initialization is done, and then the program gets a command
    from the user, executes it, and repeats.

  File usage:

    matmul.inp, record of input, created by MATMUL.
    matmul.out, record of input/output, created by MATMUL.
    matmul.hlp, help file.  (Not available)
    matmul.dat, data file, created by MATMUL.
    matmul.exp, explanation file, read by MATMUL.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    15 May 2009

  Author:

    John Burkardt, Paul Puglielli.
*/
{
  Init ( );

  for ( ; ; )
  {
    Getcom ( );
    Docom ( );
  }
  return 0;
}
/******************************************************************************/

void abortm ( )

/******************************************************************************/
/*
  Purpose:

    ABORTM is called to terminate execution.

  Discussion:

    ABORTM dumps the results to a file, says "goodbye" to the user,
    and closes all files.
*/
{
  Pdump();
  Gbye();
  Flclos();

  exit ( 1 );
}
/******************************************************************************/

void chop ( char *STRING, int ILO, int IHI )

/******************************************************************************/
/*
  CHOP "chops" out entries ILO through IHI of STRING, shifts the string
  down, and pads the end of the string with NULLs.
*/
{
   size_t l;
   int i,j;

   l=strlen(STRING);
   i=ILO;
   for(j=IHI+1;j<l;j++)
     STRING[i++]=STRING[j];
   memset(STRING+i,'\0',l-i);

  return;
}
/******************************************************************************/

void CHRCTI ( char *STRING, int *INTVAL )

/******************************************************************************/
/*
  CHRCTI accepts a STRING of characters and reads an integer
  from STRING into INTVAL.  The STRING must begin with an integer
  but that may be followed by other information.
  CHRCTI will read as many characters as possible until it reaches
  the end of the STRING, or encounters a character which cannot be
  part of the number.
*/
{
  *INTVAL=atoi(STRING);
}

/******************************************************************************/

char *CHRDB2 ( char *str )

/******************************************************************************/
/*
  CHRDB2 accepts a STRING of characters.  It replaces all nulls
  by blanks.  It replaces all strings of consecutive blanks by a single
  blank, left justifying the remainder and padding with blanks.
*/
{
  char oldchar,newchar;
  size_t l;
  int i,j;

  l=strlen(str);
  j=0;
  newchar=' ';
  for(i=1;i<=l;i++)
  {
    oldchar=newchar;
    if (str[i] == '\0') str[i]=' ';
    newchar=str[i];
    str[i]=' ';
    if ((oldchar != ' ') || (newchar != ' '))
    {
      j++;
      str[j]=newchar;
    }
  }
  return str;
}
/******************************************************************************/

double cpu_time ( )

/******************************************************************************/
/*
  Purpose:

    CPU_TIME returns the current reading on the CPU clock.

  Discussion:

    The CPU time measurements available through this routine are often
    not very accurate.  In some cases, the accuracy is no better than
    a hundredth of a second.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    06 June 2005

  Author:

    John Burkardt

  Parameters:

    Output, double CPU_TIME, the current reading of the CPU clock, in seconds.
*/
{
  double value;

  value = ( double ) clock ( )
        / ( double ) CLOCKS_PER_SEC;

  return value;
}
/******************************************************************************/

void Docom ( void )

/******************************************************************************/
/*
  DOCOM figures out what the user's command is, and carries it out.
*/
{
  char out[80];

  if ( command[0] == 'A' )
  {
    abortm ( );
  }
  else if (command[0] == 'E')
    Explain();
  else if (command[0] == 'H')
    Help();
  else if ((strncmp(command,"LDA=",4) == 0))
    Getlda(command+4);
  else if (command[0] == 'M')
  {
    ido=1;
    ilo=0;
    ihi=0;
    n=nlo;
    Result(TRUE);
    do
    {
      ilo=iplot+1;
      Mult();
      ihi=iplot;
      Result(FALSE);
      ido=2;
      Nstep();
    }while(ido == 1);
    Putout("The matrix multiplication has been carried out.\n");
  }
  else if ((strncmp(command,"N=",2) == 0))
    Getn(command+2);
  else if ((strncmp(command,"NOSHOW=",7) == 0))
    Getsho(command+7,FALSE);
  else if ((strncmp(command,"NOSHOW",6) == 0))
  {
    strcpy(command,"NOSHOW=ALL");
    Getsho(command+7,FALSE);
  }
  else if ((strncmp(command,"ORDER=",6) == 0))
    Getord(command+6,&ierr);
  else if (command[0] == 'Q')
  {
    Putout("Please type \"Y\" to confirm that you want to quit.\n");
    Getcom();
    if (command[0] == 'Y')
      abortm();
  }
  else if (command[0] == 'P')
  {
    Printr();
    Shoord();
    Result(FALSE);
  }
  else if ((strncmp(command,"SHOW=",5) == 0))
    Getsho(command+5,TRUE);
  else if ((strncmp(command,"SHOW",4) == 0))
  {
    strcpy(command,"SHOW=ALL");
    Getsho(command+5,TRUE);
  }
  else
  {
    Putout("Your command was not recognized.\n");
    sprintf(out,"You typed %s\n",command);
    Putout(out);
    Putout("type HELP for a list of commands.\n");
  }

  memset(command,'\0',(int)strlen(command));

  return;
}
/******************************************************************************/

void Explain()

/******************************************************************************/
/*
  EXPLAIN prints a brief explanation of MATMUL for beginners. To do so,
  it reads a file "matmul.exp" and prints it out to the screen.
*/
{
  int line=0;
  char outline[80];

  ifilee = fopen ( filee, "rt" );

  if ( !ifilee )
  {
    Putout("EXPLANATION file is not available!\n");
    sprintf(outline,"MATMUL could not find the file %s.\n",filee);
    Putout(outline);
    Putout("which explains the program.  This is not a fatal\n");
    Putout("error, but it means the EXPLAIN command won't work.\n");
    return;
  }

  for(line=0;!feof(ifilee);line++)
  {
    fgets(output,120,ifilee);
    printf("%s",output);
    if (line>22)
    {
      getchar();
      line=0;
    }
  }
  fclose ( ifilee );

  ifilee=NULL;

  return;
}
/******************************************************************************/

void Flclos()

/******************************************************************************/
/*
  FLCLOS closes all the files
*/
{
  if (ifilei)
    fclose(ifilei);
  if (ifileo)
    fclose(ifileo);
  if (ifileh)
    fclose(ifileh);
  if (ifiled)
    fclose(ifiled);

  return;
}
/******************************************************************************/

void Flopen()

/******************************************************************************/
/*
  FLOPEN opens all the files. EXCEPT for matmul.dat, which is opened in Pdump.
*/
{
  char outline[80];
  ifileo=fopen(fileo,"w");
  if(!ifileo)
  {
     sprintf(outline,"MATMUL could not open the output file %s",fileo);
     Putout(outline);
     Putout("This is not a serious problem, but it does mean there\n");
     Putout("will not be a transcript of the input and output\n");
  }

  ifilei=fopen(filei,"w");
  if(!ifilei)
  {
     sprintf(outline,"MATMUL could not open the output file %s\n",filei);
     Putout(outline);
     Putout("This is not a serious problem, but it does mean there\n");
     Putout("will not be a record of you output.\n");
  }
/*
HELP system not available yet!
  ifileh=fopen(fileh,"r");
  if(!ifileh)
  {
    sprintf(outline,"MATMUL could not open the help file %s\n",fileh);
    Putout(outline);
    Putout("This is not a serious problem, but it does mean that\n");
    Putout("the full help system will not be available.\n");
  }
*/
   ifileh=NULL;

  return;
}
/******************************************************************************/

void Gbye()

/******************************************************************************/
/*
   GBYE says goodbye to the user, and prints a reminder about files created
   by the program.
*/
{
  char outline[80];

  if(ifilei)
    sprintf(outline,"A copy of your input is in the file %s\n",filei);
  else
    sprintf(outline,"MATMUL could not create the input file %s\n",filei);
  Putout(outline);

  if(ifiled)
    sprintf(outline,"A copy of your results is in the file %s\n",filed);
  else
    sprintf(outline,"MATMUL could not create the result file %s\n",filed);
  Putout(outline);

  if(ifileo)
    sprintf(outline,"A copy of the entire session is in the file %s\n",fileo);
  else
    sprintf(outline,"MATMUL could not create the session file %s\n",fileo);
  Putout(outline);

  printf ( "\n" );
  printf ( "MATMUL:\n" );
  printf ( "  Normal end of execution.\n" );

  return;
}
/******************************************************************************/

void Getcom()

/******************************************************************************/
/*
  GETCOM reads the next command from the user.
*/
{
  short i;
  char cx;

  Putout("Command?  (Type H for help):");
  for(i=0;((cx=getchar()) != '\n'); i++)
    command[i]=toupper(cx);
  Putinp();

  return;
}
/******************************************************************************/

void Getlda(char *str)

/******************************************************************************/
/*
  GETLDA gets a new value of LDA from the user.
*/
{
  char outline[80];
  int temp;

  CHRCTI(str,&temp);
  if (str == NULL)
    Putout("I did not understand your definition of LDA.\n");
  if(temp < 0)
  {
    Putout("The assignment of LDA was not acceptable!\n");
    Putout("LDA must be positive.\n");
  }
  else if (temp > LENA)
  {
    Putout("The assignment of LDA was not acceptable!\n");
    sprintf(outline,"LDA must be no greater than %d.\n",LENA);
    Putout(outline);
  }
  else
  {
    lda=temp;
    sprintf(outline,"LDA has been set to %d.\n",lda);
    Putout(outline);
  }

  if (lda < n)
  {
    n=lda;
    Putout("\nNote: Since the value of N must always be no greater\n");
    Putout("than LDA, MATMUL has just decreased the value of N.\n");
    sprintf(outline,"N has been set to %d\n",n);
    Putout(outline);
  }

  return;
}
/******************************************************************************/

void Getn ( char *str )

/******************************************************************************/
/*
  GETN reads a new value of N from the user.
*/
{
  char outline[80];
  char s[80];
  int temp;
  int i;
  int j;
  int l;
  int mult;

  if ( !str[0] )
  {
    Putout("I could not understand your definition of N.\n");
    return;
  }

  l=strlen(str);
  memset(s,'\0',l);

/*
  Get first number
*/
  for(i=0;( (i<l) && (str[i] != ',') ); i++)
  {
    s[i]=str[i];
  }

  CHRCTI(s,&temp);
  memset(s,'\0',l);
  if (temp <= 0)
  {
    Putout("The value of N that you chose is not acceptable!\n");
    Putout("N must be positive\n");
  }
  else if (temp > LENA)
  {
    Putout("The value of N that you chose is not acceptable!\n");
    sprintf(outline,"N must be no greater than %d\n",LENA);
    Putout(outline);
  }
  else
  {
    n=temp;
    nlo=temp;
    nhi=temp;
    sprintf(outline,"N has been set to %d\n",n);
    Putout(outline);
  }

/*
  Read second number
*/

/*
  if (str[i] == NULL)
*/
  if ( !str[i] )
    return;

  i++;
  for(j=0;((i<l) && (str[i] != ',')); i++,j++)
    s[j]=str[i];

  CHRCTI(s,&temp);
  memset(s,'\0',l);
  if (temp <= 0)
  {
    Putout("The value of NHI that you chose is not acceptable!\n");
    Putout("NHI must be greater than zero\n");
  }
  else if (temp > LENA)
  {
    Putout("The value of NHI that you chose is not acceptable!\n");
    sprintf(outline,"NHI must be no greater than %d\n",LENA);
    Putout(outline);
  }
  else
  {
    nhi=temp;
    sprintf(outline,"NHI has been set to %d\n",nhi);
    Putout(outline);
    ninc=1;
  }

/* Check for multipy */
  i++;
  if (str[i] == '*')
  {
    mult=TRUE;
    i++;
  }
  else
    mult=FALSE;

/*
  Get third and last number
*/
  if ( !str[i] )
    return;

  for(j=0;((i<l) && (str[i] != '\0')); i++,j++)
    s[j]=str[i];

  CHRCTI(s,&temp);
  if ( mult == FALSE)
  {
    ninc=temp;
    if ((nlo > nhi) && (ninc > 1)) ninc*=-1;
    sprintf(outline,"NINC has been set to %d\n",ninc);
    Putout(outline);
  }
  else
  {
    ninc=0;
    nmult=temp;
    sprintf(outline,"NMULT has been set to %d\n",nmult);
    Putout(outline);
  }
  return;
}
/******************************************************************************/

void Getord(char *str, int *error)

/******************************************************************************/
/*
  GETORD reads a new value of ORDER from the user.
*/
{
  char ctemp[10],outline[80];

  strncpy(ctemp,str,10);
  if (
   (strncmp(ctemp,"ALL",3)!=0)    && (strncmp(ctemp,"IJK",3)!=0)    &&
   (strncmp(ctemp,"IKJ",3)!=0)    && (strncmp(ctemp,"JIK",3)!=0)    &&
   (strncmp(ctemp,"JKI",3)!=0)    && (strncmp(ctemp,"KIJ",3)!=0)    &&
   (strncmp(ctemp,"KJI",3)!=0)    && (strncmp(ctemp,"R8_IJK",6)!=0)   &&
   (strncmp(ctemp,"UIJK",4)!=0)   && (strncmp(ctemp,"IUJK",4)!=0)   &&
   (strncmp(ctemp,"IJUK",4)!=0)   && (strncmp(ctemp,"PIJKA",5)!=0)  &&
   (strncmp(ctemp,"PIJKP",5)!=0)  && (strncmp(ctemp,"SDOT",4)!=0)   &&
   (strncmp(ctemp,"TAXPYC",6)!=0) && (strncmp(ctemp,"TAXPYR",6)!=0) &&
   (strncmp(ctemp,"SAXPYC",6)!=0) && (strncmp(ctemp,"IIJK",4)!=0)   &&
   (strncmp(ctemp,"TDOT",4)!=0)   && (strncmp(ctemp,"SAXPYR",6)!=0) &&
   (strncmp(ctemp,"SGEMM",5)!=0)  && (strncmp(ctemp,"SGEMMS",6)!=0) &&
   (strncmp(ctemp,"MIJK",4)!=0)   &&(strncmp(ctemp,"NIJK",4)!=0)    &&
   (strncmp(ctemp,"SIJK",4)!=0)   &&(strncmp(ctemp,"MXMA",4)!=0))
  {
     Putout("The order you chose was not a valid choice.\n");
     Putout("\nYour command was not carried out.\n");
     *error=1;
  }
  else
  {
     sprintf(outline,"ORDER has been set to %s\n",ctemp);
     Putout(outline);
     strcpy(order,ctemp);
  }
  return;
}
/******************************************************************************/

void Getsho(char *str,int lval)

/******************************************************************************/
/*
  GETSHO gets information from the user about what is to be printed out
  as results after a multiplication is carried out.
*/
{
  if ((strncmp(str,"ALL",3) == 0) || (strncmp(str,"all",3) == 0))
    mshow=langshow=ashow=cshow=fshow=lshow=nshow=noshow=tshow=lval;
  else if ((strncmp(str,"MACHINE",7) == 0) || (strncmp(str,"machine",7) == 0))
    mshow=lval;
  else if ((strncmp(str,"LANGUAGE",8) == 0) || (strncmp(str,"language",8) == 0))
    langshow=lval;
  else if ((strncmp(str,"A(N,N)",6) == 0) || (strncmp(str,"a(n,n)",6) == 0))
    ashow=lval;
  else if ((strncmp(str,"ORDER",5) == 0) || (strncmp(str,"order",5) == 0))
    cshow=lval;
  else if ((strncmp(str,"MFLOPS",6) == 0) || (strncmp(str,"mflops",6) == 0))
    fshow=lval;
  else if ((strncmp(str,"LDA",3) == 0) || (strncmp(str,"lda",3) == 0))
    lshow=lval;
  else if ((str[0]=='N') || (str[0]=='n'))
    nshow=lval;
  else if ((strncmp(str,"OPS",3) == 0) || (strncmp(str,"ops",3) == 0))
    noshow=lval;
  else if ((strncmp(str,"TIME",4) == 0) || (strncmp(str,"time",4) == 0))
    tshow=lval;
  else
  {
    Putout("That is not a legal name! \n");
    Putout("Legal names are ORDER, LDA, N, TIME, OPS, LANGUAGE, MACHINE, MFLOPS and A(N,N).\n");
  }
  return;
}
/******************************************************************************/

void Hello()

/******************************************************************************/
/*
  HELLO says hello to the user, printing the version, machine, and so on.
*/
{
  char out[80];

  printf ( "\n" );
  printf ( "MATMUL\n" );
  printf ( "  C version\n" );
  printf ( "  An interactive demonstration of the speed of");
  Putout(" matrix multiplication.\n");
  sprintf(out,"Version 1.0c, last compiled on %s.  ",LASTMOD);
  Putout(out);
  sprintf(out,"This version is for a %s\n",machine[MACHINE]);
  Putout(out);
  Putout("\nIf you\'ve never used this program before, type EXPLAIN.\n\n");
  return;
}
/******************************************************************************/

void Help()

/******************************************************************************/
/*
  HELP prints a list of the available commands.
*/
{
  Putout("This is the list of legal commands.\n");
  if(ifilee)
    Putout("E           Explain what this program does.\n");
  Putout("H           Help. List the legal commands.\n");
  Putout("LDA=value   Assigns the leading dimension of arrays.\n");
  Putout("M           Multiply two matrices.\n");
  Putout("N=value     Assigns the size of the arrays.\n");
  Putout("ORDER=name  Chooses the algorithm for multiplication.\n");
  Putout("P           Prints out current values and results.\n");
  Putout("Q           Quit.\n");
  Putout("NOSHOW=name Value of NAME should not be included in output.\n");
  Putout("            NAME=ORDER, LDA, N, TIME, OPS or MFLOPS\n");
  Putout("SHOW=name   Value of NAME should be included in output.\n");
  Putout("            NAME=ORDER, LDA, N, TIME, OPS or MFLOPS\n\n");
  return;
}
/*****************************************************************************/

void r8_ijk ( )

/*****************************************************************************/
/*
  Purose:

    R8_IJK uses R8 arithmetic and IJK order.
*/
{
  double da[LENA][LENA];
  double db[LENA][LENA];
  double dc[LENA][LENA];
  int i;
  int j;
  int k;

  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < n; j++ )
    {
      da[i][j] = 0.0;
      db[i][j] = 1.0;
      dc[i][j] = 1.0;
    }
  }

  sec1 = cpu_time ( );

  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < n; j++ )
    {
      for ( k = 0; k < n; k++ )
      {
        da[i][k] = da[i][k] + db[i][j] * dc[j][k];
      }
    }
  }
  sec2 = cpu_time ( );

  a[n-1][n-1] = ( float ) da[n-1][n-1];

  return;
}


void NIJK()
/******************************************************************************
  NIJK multiplies A=B*C using index order IJK with integers instead of
  floating point numbers.
******************************************************************************/
{
  int i,j,k;
  long ia[LENA][LENA];
  long ib[LENA][LENA],ic[LENA][LENA];

  for(i=0;i<n; i++)
  for(j=0;j<n;j++)
  {
     ia[i][j]=0;
     ib[i][j]=1;
     ic[i][j]=1;
  }
  sec1 = cpu_time ( );
  for (i=0;i < n;i++)
    for (j=0; j < n; j++)
       for (k=0; k < n; k++)
         ia[i][k]=ia[i][k]+ib[i][j]*ic[j][k];
  sec2 = cpu_time ( );
  a[n-1][n-1]=(float)ia[n-1][n-1];
  return;
}


void IUJK()
/******************************************************************************
  IUJK multiplies A=B*C using index order IJK and unrolling on J.
******************************************************************************/
{
  int i,j,k,jhi;

  jhi=(n/NROLL)*NROLL;
  jhi--;

  sec1 = cpu_time ( );
  for (i=0;i <n; i++)
    for (j=0; j < jhi;j+=NROLL)
       for (k=0; k < n; k++)
       {
         a[i][k]=a[i][k]+b[i][j]*c[j][k];
         a[i][k]=a[i][k]+b[i][j+1]*c[j+1][k];
         a[i][k]=a[i][k]+b[i][j+2]*c[j+2][k];
         a[i][k]=a[i][k]+b[i][j+3]*c[j+3][k];
       }
  for (i=0; i < n; i++)
    for (j=jhi+1;j < n;j++)
       for (k=0; k < n; k++)
         a[i][k]=a[i][k]+b[i][j]*c[j][k];

  sec2 = cpu_time ( );
  return;
}

void IJUK()
/******************************************************************************
  IJUK multiplies A=B*C using index order IJK and unrolling on K.
******************************************************************************/
{
  int i,j,k,khi;

  khi=(n/NROLL)*NROLL;
  khi--;

  sec1 = cpu_time ( );
  for (i=0;i < n; i++)
    for (j=0; j < n; j++)
       for (k=0; k <khi;k+=NROLL)
       {
         a[i][k]=a[i][k]+b[i][j]*c[j][k];
         a[i][k+1]=a[i][k+1]+b[i][j]*c[j][k+1];
         a[i][k+2]=a[i][k+2]+b[i][j]*c[j][k+2];
         a[i][k+3]=a[i][k+3]+b[i][j]*c[j][k+3];
       }
  for (i=0; i < n; i++)
    for (j=0; j < n; j++)
       for (k=khi+1;k < n;k++)
         a[i][k]=a[i][k]+b[i][j]*c[j][k];

  sec2 = cpu_time ( );
  return;
}

void UIJK()
/******************************************************************************
  UIJK multiplies A=B*C using index order IJK and unrolling on I.
******************************************************************************/
{
  int i,j,k,iroll;

  iroll=(n/NROLL)*NROLL;
  iroll--;

  sec1 = cpu_time ( );
  for (i=0;i < iroll;i+=NROLL)
    for (j=0; j < n; j++)
       for (k=0; k < n; k++)
       {
         a[i][k]=a[i][k]+b[i][j]*c[j][k];
         a[i+1][k]=a[i+1][k]+b[i+1][j]*c[j][k];
         a[i+2][k]=a[i+2][k]+b[i+2][j]*c[j][k];
         a[i+3][k]=a[i+3][k]+b[i+3][j]*c[j][k];
       }
  for (i=iroll+1;i < n;i++)
    for (j=0; j < n; j++)
       for (k=0; k < n; k++)
         a[i][k]=a[i][k]+b[i][j]*c[j][k];

  sec2 = cpu_time ( );
  return;
}

void PIJKA()
/******************************************************************************
  PIJKA multiplies A=B*C using index order IJK with pointers to arrays A and
  B.
******************************************************************************/
{
  int i,j,k;
  float *bptr,*cptr,*bp = &b[0][0],*cp = &c[0][0];

  sec1 = cpu_time ( );
  for (bptr=bp,i=0;i<n;i++,bptr=bp+LENA)
  {
   for(cptr=cp,j=0;j<n;j++,bptr++,cptr=cp+LENA)
   {
     for(k=0;k<n;k++,cptr++)
       a[i][k]+=(*bptr)*(*cptr);
   }
  }
  sec2 = cpu_time ( );
  return;
}

void PIJKP()
/******************************************************************************
  PIJKP multiplies A=B*C using index order IJK with pointer to arrays A, B
  and C
******************************************************************************/
{
  int i,j,k;
  float *bptr,*cptr,*bp = &b[0][0],*cp = &c[0][0],*aptr,*ap = &a[0][0];

  sec1 = cpu_time ( );
  for (bptr=bp,i=0;i<n;i++,bptr=bp+LENA,ap+=LENA)
  {
   for(cptr=cp,j=0;j<n;j++,bptr++,cptr=cp+LENA)
   {
     for(aptr=ap,k=0;k<n;k++,cptr++,aptr++)
       *aptr+=(*bptr)*(*cptr);
   }
  }
  sec2 = cpu_time ( );
  return;
}

void TAXPYC()
/******************************************************************************
  TAXPYC multiplies A=B*C taxpy routine from BLAS.  TAXPYC is used to carry
  out the multiplication coloumnwise.
******************************************************************************/
{
  int j,k,LDA=LENA;

  sec1 = cpu_time ( );
  for (j=0; j < n; j++)
    for (k=0;k < n;k++)
      taxpy(n,&c[j][k],&b[0][j],LDA,&a[0][k],LDA);
  sec2 = cpu_time ( );
  return;
}


void TAXPYR()
/******************************************************************************
  TAXPYR multiplies A=B*C taxpy routine from BLAS.  TAXPYR is used to carry
  out the multiplication rowwise.
******************************************************************************/
{
  int i,j,one=1;

  sec1 = cpu_time ( );
  for (i=0;i < n;i++)
    for (j=0; j < n; j++)
      taxpy(n,&b[i][j],&c[j][0],one,&a[i][0],one);
  sec2 = cpu_time ( );
  return;
}
#if (MACHINE == CRAY)

void SAXPYC()
/******************************************************************************
  SAXPYC multiplies A=B*C using the SAXPY routine from SCILIB.  SAXPYC is
  used to carrys out the multipication coloumnwise.
******************************************************************************/
{
  int j,k,LDA=LENA;

  sec1 = cpu_time ( );
  for (j=0; j < n; j++)
    for (k=0;k < n;k++)
      SAXPY(&n,&c[j][k],&b[0][j],&LDA,&a[0][k],&LDA);
  sec2 = cpu_time ( );
  return;
}

void SAXPYR()
/******************************************************************************
  SAXPYR multiplies A=B*C using the SAXPY routine from SCILIB.  SAXPYR is
  used to carry out the multiplication rowwise.
******************************************************************************/
{
  int i,j,one=1;

  sec1 = cpu_time ( );
  for (i=0;i < n;i++)
    for (j=0; j < n; j++)
      SAXPY(&n,&b[i][j],&c[j][0],&one,&a[i][0],&one);
  sec2 = cpu_time ( );
  return;
}

void _SGEMMS()
/******************************************************************************
  SGEMMS multiplies A=B*C using the SGEMMS routine from SCILIB.  SGEMMS uses
  Strassen's method.
******************************************************************************/
{
  int LDA=LENA,wn=2.34*n*n;
  float alpha=1.0,beta=1.0,work[wn];
  char transa='N',transb='N';

  sec1 = cpu_time ( );
    SGEMMS(&transa,&transb,&n,&n,&n,&alpha,&c,&LDA,&b,&LDA,&beta,&a,&LDA,&work);
  sec2 = cpu_time ( );
  return;
}

void _SGEMM()
/******************************************************************************
  SGEMM multiplies A=B*C using the SCILIB routine SGEMM.
******************************************************************************/
{
  int LDA=LENA;
  float alpha=1.0,beta=1.0;
  char transa='N',transb='N';

  sec1 = cpu_time ( );
    SGEMM(&transa,&transb,&n,&n,&n,&alpha,&c,&LDA,&b,&LDA,&beta,&a,&LDA);
  sec2 = cpu_time ( );
  return;
}

void _MXMA()
/******************************************************************************
  MXMA multiplies A=B*C using the SCILIB routine MXMA.
******************************************************************************/
{
  int LDA=LENA;
  int alpha=1.0,beta=1.0;

  sec1 = cpu_time ( );
    MXMA(&b,&alpha,&LDA,&c,&beta,&LDA,&a,&beta,&LDA,&n,&n,&n);
  sec2 = cpu_time ( );
  return;
}

void _SDOT()
/******************************************************************************
  SDOT multiplies A=B*C using the SCILIB routine SDOT.
******************************************************************************/
{
  int i,j,one=1,LDA=LENA;

  sec1 = cpu_time ( );
  for (i=0;i < n;i++)
    for (j=0; j < n; j++)
      a[i][j]=SDOT(&n,&b[i][0],&one,&c[0][j],&LDA);
  sec2 = cpu_time ( );
  return;
}
#endif

void _TDOT()
/******************************************************************************
  TDOT multiplies A=B*C using the level 1 BLAS routine TDOT.
******************************************************************************/
{
  int i,j,one=1,LDA=LENA;

  sec1 = cpu_time ( );
  for (i=0;i < n;i++)
    for (j=0; j < n; j++)
      a[i][j]=tdot(n,&b[i][0],one,&c[0][j],LDA);
  sec2 = cpu_time ( );
  return;
}

void IJK()
/******************************************************************************
  IJK multiplies A=B*C using index order IJK.
******************************************************************************/
{
  int i,j,k;

  sec1 = cpu_time ( );
  for (i=0;i < n;i++)
    for (j=0; j < n; j++)
       for (k=0; k < n; k++)
         a[i][k]=a[i][k]+b[i][j]*c[j][k];
  sec2 = cpu_time ( );
  return;
}

void IKJ()
/******************************************************************************
  IKJ multiplies A=B*C using index order IKJ.
******************************************************************************/
{
  int i,j,k;
  sec1 = cpu_time ( );
  for (i=0;i < n;i++)
    for (k=0; k < n; k++)
       for (j=0; j < n; j++)
          a[i][k]=a[i][k]+b[i][j]*c[j][k];
  sec2 = cpu_time ( );
  return;
}

#if MACHINE == CRAY

void MIJK()
/******************************************************************************
  MIJK multiplies A=B*C using index order IJK with the outer most loop
  multitasked.
******************************************************************************/
{
  int i,j,k;

  TMSTART();
#pragma _CRI taskloop defaults
  for (i=0;i < n;i++) /* do in parallel*/
    for (j=0; j < n; j++)/*scalar loop*/
       for (k=0; k < n; k++)/* vector loop */
         a[i][k]=a[i][k]+b[i][j]*c[j][k];
  TMSTOP();
  return;
}
#endif

void SIJK()
/******************************************************************************
  SIJK multiplies A=B*C using index order IJK in scalar mode.
******************************************************************************/
{
  int i,j,k;

  sec1 = cpu_time ( );
#pragma novector
  for (i=0;i < n;i++)
#pragma novector
    for (j=0; j < n; j++)
#pragma novector
       for (k=0; k < n; k++)
         a[i][k]=a[i][k]+b[i][j]*c[j][k];
  sec2 = cpu_time ( );
  return;
}


void Init ( )
/******************************************************************************
 INIT does initializations; setting variables, opening files, saying hello.
******************************************************************************/
{
  Setval();
  Flopen();
  Hello();
  return;
}



void JIK()
/******************************************************************************
  JIK multiplies A=B*C using index order JIK.
******************************************************************************/
{

  int i,j,k;
  sec1 = cpu_time ( );
  for (j=0; j < n; j++)
    for (i=0;i < n;i++)
       for (k=0; k < n; k++)
          a[i][k]=a[i][k]+b[i][j]*c[j][k];
  sec2 = cpu_time ( );
  return;
}

/******************************************************************************/

void JKI()

/******************************************************************************/
/*
  JKI multiplies A=B*C using index order JKI.
*/
{
  int i,j,k;

  sec1 = cpu_time ( );
  for (j=0; j < n; j++)
    for (k=0; k <n; k++)
      for (i=0;i < n;i++)
          a[i][k]=a[i][k]+b[i][j]*c[j][k];
  sec2 = cpu_time ( );
  return;
}


void KIJ()
/******************************************************************************
  KIJ multiplies A=B*C using index order KIJ.
******************************************************************************/
{
  int i,j,k;

  sec1 = cpu_time ( );
   for (k=0; k < n; k++)
    for (i=0; i < n; i++)
      for (j=0; j < n; j++)
          a[i][k]=a[i][k]+b[i][j]*c[j][k];
  sec2 = cpu_time ( );
  return;
}
/******************************************************************************/

void KJI()

/******************************************************************************/
/*
  KJI multiplies A=B*C using index order KJI.
*/
{
  int i,j,k;
  sec1 = cpu_time ( );
   for (k=0; k < n; k++)
     for (j=0; j < n; j++)
       for (i=0;i < n;i++)
          a[i][k]=a[i][k]+b[i][j]*c[j][k];
  sec2 = cpu_time ( );
  return;
}

/******************************************************************************/

int min(int x,int y)

/******************************************************************************/
/*
  min returns the minimum of a and b
*/
{
  int value;

  if (x<=y)
    value = x;
  else
    value = y;

  return value;
}
/******************************************************************************/

void Mult ( )

/******************************************************************************/
/*
  MULT carries out the matrix multiplication, using the requested method.
  If the method was "ALL", then use every available method.
*/
{
  char ctemp[10];

  strcpy(ctemp,order);

  if((strncmp(order,"IJK",3)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"IJK");
    Zero(n);
    IJK();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"IKJ",3)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"IKJ");
    Zero(n);
    IKJ();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"JIK",3)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"JIK");
    Zero(n);
    JIK();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"JKI",3)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"JKI");
    Zero(n);
    JKI();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"KIJ",3)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"KIJ");
    Zero(n);
    KIJ();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"KJI",3)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"KJI");
    Zero(n);
    KJI();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"UIJK",4)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"UIJK");
    Zero(n);
    UIJK();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"IUJK",4)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"IUJK");
    Zero(n);
    IUJK();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"IJUK",4)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"IJUK");
    Zero(n);
    IJUK();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"PIJKA",5)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"PIJKA");
    Zero(n);
    PIJKA();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"PIJKP",5)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"PIJKP");
    Zero(n);
    PIJKP();
    Record();
    strcpy(order,ctemp);
  }
#if MACHINE != IBM_PC
  if((strncmp(order,"R8_IJK",6)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"R8_IJK");
    r8_ijk ( );
    Record();
    strcpy(order,ctemp);
  }
#endif
  if((strncmp(order,"NIJK",4)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"NIJK");
    NIJK();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"TAXPYC",6)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"TAXPYC");
    Zero(n);
    TAXPYC();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"TAXPYR",6)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"TAXPYR");
    Zero(n);
    TAXPYR();
    Record();
    strcpy(order,ctemp);
  }
#if (MACHINE == CRAY)
  if((strncmp(order,"MIJK",4)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"MIJK");
    Zero(n);
    MIJK();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"SIJK",4)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"SIJK");
    Zero(n);
    SIJK();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"SAXPYC",6)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"SAXPYC");
    Zero(n);
    SAXPYC();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"SAXPYR",6)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"SAXPYR");
    Zero(n);
    SAXPYR();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"MXMA",4)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"MXMA");
    Zero(n);
    _MXMA();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"SGEMM",6)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"SGEMM");
    Zero(n);
    _SGEMM();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"SGEMMS",6)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"SGEMMS");
    Zero(n);
    _SGEMMS();
    Record();
    strcpy(order,ctemp);
  }
  if((strncmp(order,"SDOT",4)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"SDOT");
    Zero(n);
    _SDOT();
    Record();
    strcpy(order,ctemp);
  }
#endif
  if((strncmp(order,"TDOT",4)==0) || (strncmp(order,"ALL",3)==0))
  {
    strcpy(order,"TDOT");
    Zero(n);
    _TDOT();
    Record();
    strcpy(order,ctemp);
  }
}
/******************************************************************************/

int Nstep ( )

/******************************************************************************/
{
  if (ninc != 0)
  {
    if ( ((nlo < nhi) && (ninc > 0)) || ((nlo > nhi) && (ninc < 0)) )
    {
      n+=ninc;
      ido=1;
      if ( ((n < nhi) && (nhi <= nlo)) || ((n > nhi) && (nhi >= nlo)) )
      {
	ido=0;
	n=nlo;
      }
    }
    else
      ido=2;
  return(ido);
  }
  if (nmult > 1)
  {
    if ( nlo < nhi)
    {
      n= n*nmult;
      ido=1;
      if ( ((n < nhi) && (nhi <= nlo)) || ((n > nhi) && (nhi >= nlo)) )
      {
        ido=0;
        n=nlo;
      }
    }
    else
      ido = 2;
  return(ido);
  }

  ido=3;
  return(ido);
}
/******************************************************************************/

void Pdump()

/******************************************************************************/
/*
 PDUMP writes the timing results to a data file.
*/
{
  int i;
  if(iplot >0 )
  {
    ifiled=fopen(filed,"w");
    if(ifiled)
      for(i=1;i<=iplot;i++)
        fprintf(ifiled,"%-5s %-3d %-3d %-9.6f %-11d %-9.6f %-6.3f\n",
	      cplot[i],lplot[i],nplot[i],tplot[i],noplot[i],fplot[i],aplot[i]);
  }
  else
    ifiled=NULL;

  return;
}
/******************************************************************************/

void Printr()

/******************************************************************************/
/*
  PRINTR prints out the current values of parameters that the user should
  be interested in, including:

  the algorithm,
  the leading dimension,
  the maximum allowable dimension,
  the actual size of arrays,
  the number of multiplications carried out.
*/
{ char outline[80];
  sprintf(outline,"The algorithm chosen is %s\n",order);
  Putout(outline);
  sprintf(outline,"The leading dimension of arrays, LDA, is %d\n",lda);
  Putout(outline);
  sprintf(outline,"The maximum legal choice for LDA is %d\n",LENA);
  Putout(outline);
  sprintf(outline,"The actual size of the arrays, N, is %d\n",n);
  Putout(outline);
  sprintf(outline,"A total of %d cases have been run.\n",iplot);
  Putout(outline);

  return;
}



void Putinp()
/******************************************************************************
 PUTINP prints the user's most recent input line to the command file and
 to the output file.
******************************************************************************/
{
  size_t i;

  i=strlen(command);
  if (i)
  {
    if (ifilei)
      fprintf(ifilei,"%s\n",command);
    if (ifileo)
      fprintf(ifileo,"%s\n",command);
  }
  else
  {
    fprintf(ifilei," \n");
    fprintf(ifilei," \n");
  }
  return;
}


void Putout(char *outstr)
/******************************************************************************
  PUTOUT prints a line of output to the user's screen, and to the output file.
******************************************************************************/
{
   size_t i;

   i=strlen(outstr);
   if (i)
   {
      printf("%s",outstr);
      if (ifileo)
         fprintf(ifileo,"%s",outstr);
   }
   else
   {
     printf("\n");
     if (ifileo)
       fprintf(ifileo,"\n");
   }
  return;
}

void Record()
/******************************************************************************
  RECORD stores the results for the latest multiplication into various arrays.
******************************************************************************/
{
  if(iplot < MAXPLT)
  {
    iplot++;
    aplot[iplot]=a[n-1][n-1];
    strcpy(cplot[iplot],order);
    lplot[iplot]=lda;
    nplot[iplot]=n;
#if MACHINE == VAX_VMS
    tot_seconds=sec2-sec1;
    tplot[iplot]=(float)tot_seconds/100.0;
#elif ((MACHINE == IBM_PC) || (MACHINE == IBM_RS6))
    tot_seconds=sec2-sec1;
    tplot[iplot]=(float)tot_seconds/CLOCKS_PER_SEC;
#elif MACHINE == CRAY
    tot_seconds=sec2-sec1;
    tplot[iplot]=(float)tot_seconds*0.000000006;
#else
    tot_seconds=sec2-sec1;
    tot_microseconds=micro2-micro1;
    tot_microseconds=tot_microseconds+(tot_seconds*1000000);
    tplot[iplot]=(float)((tot_microseconds/1000000.0));
#endif

    if(tplot[iplot] == 0.0)tplot[iplot]=1.0;
    noplot[iplot]=2*n*n*n;
    fplot[iplot]=0.000001 * (float)((float)noplot[iplot]/tplot[iplot]);
  }
  else
  {
    Putout("There is no more room to record results.\n");
    Putout("This is not a serious error, but it does mean\n");
    Putout("and any further results will not make it into\n");
    Putout("the results file.\n");
  }
  return;
}



void Result ( short lchop )
/******************************************************************************
 RESULT prints out the results of all, or some, of the multiplications.
******************************************************************************/
{
  char out[81];
  int i;

  if ( ilo <= ihi )
  {
/*
  Prepare the header string.  Then chop out items that are not being shown.
  It's important to do this chopping in reverse order!
*/
 memset(out,'\0',80);

 sprintf(out," %-8s %3s %3s %10s %8s %10s %8s %-12s %8s\n","ORDER","LDA","N","Time","Ops","MFLOPS","A(N,N)","MACHINE","LANGUAGE");

    if (lchop)
    {
      if (!langshow)  chop(out,70,78);
      if (!mshow)  chop(out,57,69);
      if (!ashow)  chop(out,48,56);
      if (!fshow)  chop(out,37,47);
      if (!noshow) chop(out,28,36);
      if (!tshow)  chop(out,17,27);
      if (!nshow)  chop(out,13,16);
      if (!lshow)  chop(out,9,12);
      if (!cshow)  chop(out,0,8);
      Putout(out);
    }

    memset(out,'\0',80);
/*Print out the values requested.*/
    for(i=ilo;i<=min(ihi,iplot);i++)
    {
      sprintf(out," %-8s %3d %3d %10.6f %8d %10.6f %8.3f %-12s %8s\n",cplot[i],lplot[i],nplot[i],tplot[i],noplot[i],fplot[i],aplot[i],machine[MACHINE],"C   ");
      if (lchop)
      {
      if (!langshow)  chop(out,70,78);
      if (!mshow)  chop(out,57,69);
      if (!ashow)  chop(out,48,56);
      if (!fshow)  chop(out,37,47);
      if (!noshow) chop(out,28,36);
      if (!tshow)  chop(out,17,27);
      if (!nshow)  chop(out,13,16);
      if (!lshow)  chop(out,9,12);
      if (!cshow)  chop(out,0,8);
      }
      if (lplot[i] != 0) Putout(out);
    }
  }
  return;
}

float tdot(int n,float *sx,int incx,float *sy,int incy )
/******************************************************************************
  the C code for the TDOT routine
******************************************************************************/
/*
    PURPOSE
        Forms the dot product of a vector.

    INPUT
        n       Number of elements to sum.
        sx      Address of first element of x vector.
        incx    Incrament for the x vector.
        sy      Address of first element of y vector.
        incy    incrament for the y vector.

    OUPUT
        sdot    Dot product x and y.  float returned
        due to `C' language features.
*/
{
  int i;
  float  stemp=0.0e0;

  if( n<1 )
    return( stemp );

  if( incx == incy )
  {
    if( incx == 1 )
    {
      /* Both increments = 1 */
      for( i=0; i<n; i++, sx++, sy++ )
        stemp += (*sx)*(*sy);
      return( stemp );
    }
    if( incx>0 )
    {
      /* Equal, positive, non-unit increments. */
      for( i=0; i<n; i++, sx+=incx, sy+=incx)
        stemp += (*sx)*(*sy);
      return( stemp );
    }
  }
  /* Unequal or negative increments. */
  if( incx < 0 ) sx += ((-n+1)*incx + 1);
  if( incy < 0 ) sy += ((-n+1)*incy + 1);
  for( i=0; i<n; i++,sx+=incx,sy+=incy )
    stemp += (*sx)*(*sy);
  return( stemp );
}

void Setval()
/*****************************************************************************
  SETVAL initializes all the COMMON block data.
*****************************************************************************/
{
 int i,j;

   mshow=langshow=ashow=cshow=fshow=lshow=noshow=nshow=tshow=TRUE;

   strcpy ( filed, "matmul.dat" );
   strcpy ( fileh, "matmul.hlp" );
   strcpy ( filei, "matmul.inp" );
   strcpy ( fileo, "matmul.out" );

   strcpy(machine[CRAY],"Cray YMP");
   strcpy(machine[CM2],"CM-2");
   strcpy(machine[DEC_ULTRIX],"DEC Station");
   strcpy(machine[VAX_VMS],"VAX/VMS");
   strcpy(machine[IBM_PC],"IBM PC");
   strcpy(machine[IBM_RS6],"IBM RS6000");
   strcpy(machine[HP_9000],"HP 9000");
   strcpy(machine[VAX_STATION],"VAX Station");
   strcpy(machine[APPLE_MAC],"Apple Macintosh");

/*
  We have to wait til we know which MACHINE we're using before we can
  figure out the name of the explanation file.
*/

#if ((MACHINE == APPLE_MAC) || MACHINE == IBM_PC)
   strcpy(filee,"matmul.exp");
#elif (MACHINE == VAX_VMS)
   strcpy(filee,"pscdoc:matmul.exp");
#elif ((MACHINE == CRAY) || (MACHINE == DEC_ULTRIX))
   strcpy(filee,"/usr/local/doc/matmul.exp");
#else
   strcpy(filee,"matmul.exp");
#endif

   ifiled=ifilee=ifileh=ifilei=ifileo=NULL;
   iplot=0;
   lda=LENA;
   n=16;
   strcpy(order,"IJK");
   memset(command,'\0',30);
   sec1=sec2=micro1=micro2=0;

   for(i=0;i < LENA ;i++)
   {
     for(j=0;j < LENA ;j++)
     {
       b[i][j]=1.0;
       c[i][j]=1.0;
     }
   }

   Zero(LENA);
  return;
}


void Shoord ( )
/******************************************************************************
  SHOORD prints out the legal choices for ORDER
******************************************************************************/
{

  printf ( "Valid choices for the order are:\n" );
  printf ( "  ALL R8_IJK IIJK IUJK UIJK IJUK\n");
  printf ( "  IJK IKJ JIK JKI KIJ KJI PIJKA PIJKP TAXPYC TAXPYR TDOT\n");

  return;
}


void taxpy(int n,float *sa,float *sx,int  incx,float *sy,int incy)
/******************************************************************************
   the C code for the TAXPY routine
******************************************************************************/
/*
  PURPOSE
    Vector times a scalar plus a vector.  sy = sy + sa*sx.

  INPUT
    n         Number of elements to multiply.
    sa        Scalar to multiply by.
    sx        Pointer to float vector to scale.
    incx      Storage incrament for sx.
    sy        Pointer to float vector to add.
    incy      Storage incrament for sy.

  OUTPUT
    sy        sy = sy + sa*sx
*/
{
  int i;

  if( n<=0 || sa==0 )
    return;

  if( incx == incy )
  {
    if( incx == 1 )
    {
      /* Both increments = 1 */
      for( i=0; i<n; i++,sy++,sx++ )
        (*sy) += (*sa)*(*sx);
      return;
    }
    if( incx>0 )
    {
      /* Equal, positive, non-unit increments. */
      for(i=0; i<n; i++, sx+=incx, sy+=incx)
        (*sy) += (*sa)*(*sx);
      return;
    }
  }
  /* Unequal or negative increments. */
  if( incx < 0 ) sx += ((-n+1)*incx + 1);
  if( incy < 0 ) sy += ((-n+1)*incy + 1);
  for( i=0; i<n; i++,sx+=incx,sy+=incy )
    (*sy) += (*sa)*(*sx);

  return;
}

#if MACHINE == CRAY

void TMSTART()
/******************************************************************************
  TMSTART is called to record the time just before a Multitasked multiplication
  is carried out.
******************************************************************************/
{
  sec1=IRTC();
  return;
}
/******************************************************************************/

void TMSTOP()

/******************************************************************************/
/*
  TMSTOP is called to record the time just after a Multitasked multiplication
  is carried out.
*/
{
  sec2=IRTC();

  return;
}
#endif

/******************************************************************************/

void Zero ( int len )

/******************************************************************************/
/*
  Purpose:

    ZERO zeroes out a real vector.
*/
{
  short i,j;

  for (i=0; i<len; i++)
    for (j=0; j<len; j++)
     a[i][j]=0.0;

  return;
}
