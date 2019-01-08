    _    _
    |    |  _ _   _ _____ TM
    |--  |  | |\  | | | |
    |  --|  | | \ |   |
    |    |  | |  \|   |
    ^    ^  ^ ^   ^   ^

*** The  HINT  PERFORMANCE ANALYZER ***

   HINT reveals many aspects of computer performance: operation speed,
precision, memory bandwidth, and usable memory size.  It is completely
unlike conventional computer benchmarks.  HINT measures "QUIPS"
(QUality Improvement Per Second) as a function of time.  "Net QUIPS" is a
single number that summarizes the QUIPS over time.  This file explains how
to run HINT, how parameters may be adjusted, and what may NOT be adjusted.
The faster the computer, the greater the need for high precision, fast access,
and large usable storage at all levels.  Unlike conventional benchmarks,
shortcomings in any of these will be reflected in the figure of merit
(Net QUIPS).


ADJUSTING PRECISION

   The HINT performance analyzer is designed to compile and run with
user-selected data types, via C preprocessor directives and defines.  DSIZE
sets the data type for computation and ISIZE sets the type for the indexing.
The -D option of C compilers performs the substitution.  One method
is to set the data types on the compile line:
        
        cc -DDSIZE=double -DISIZE=int hint.c hkernel.c -o hint
           ^^^^^^^^^^^^^^ ^^^^^^^^^^^
Or, the data types can be set by placing two of the defines found in
typedefs.h on the compile line:

        cc -DDOUBLE -DIINT hint.c hkernel.c -o hint
           ^^^^^^^^ ^^^^^^
Or, insert

        #define DSIZE double
        #define ISIZE int

at the top of the hint.h file.

   These examples cause the computation variables to be the C "double" type,
which typically will give enough precision to exercise workstation-speed
computers.  Integers work as well as floating-point numbers, but unsigned
integers are currently not allowed.  The tradeoff is that low precision
might run faster initially but with lower answer quality.  The Net QUIPS
rating reflects both answer quality and speed, so experiment with different
types to maximize Net QUIPS as reported by the program.  It is useful to
know both the best integer Net QUIPS and the best floating point Net QUIPS.
The examples above also show the indexing variables set to the C "int" type.
HINT will automatically ensure that indexing variables can represent integers
at least as large as the square root of the largest whole number used in a
computational variable.  To make full use of DSIZE precision, the number of
bits in the ISIZE type should be at least half that of the DSIZE variable type.


PORTING THE CODE
    
   HINT is written in ANSI C to provide for easy porting.  HINT is basically
two parts, a driver and a kernel.  The driver performs some self diagnostics
for the data types being used and then runs the loop which calls the kernel.
The running of the kernel is the only part of the code that is timed so 
emphasis on optimization should be placed on the file "hkernel.c".  We 
recommend that porting the code proceed in the following steps.  

   * Modify the source code following the commented locations for vendor
     specific code in "hint.c" and "hkernel.c".
   * Modify the Makefile appropriately as shown in its comments.
   * Make any modifications to the "ADJUSTABLE DEFINES" in "hint.h" that
     you feel are necessary for your machine. Be sure to follow the rules
     when you do these modifications.

We recommend that you first download and port the serial version of the code
and familiarize yourself with its workings on your machine.  The serial version
of HINT should be fairly easy to port.  Most Unix workstations require 
only modifications to the Makefile.  Good Luck! Any questions should be 
directed to hint@scl.ameslab.gov.



GETTING ACCURATE TIMINGS

   The philosophy is as follows:  There is an ultimate QUIPS curve for a
given computer.  Do your best to get close to it, within the limits of your
patience.  By taking many data points and many repetitions per data
point, you might increase Net QUIPS by a few percent but find yourself
running HINT for hours.  We envision a QUIPS curve measurement taking 10 to 20
minutes, usually.  Comments in the hint.h file under "Adjustable Defines"
indicate how to adjust the way the QUIPS curve is sampled.
   HINT is designed to filter out bad results due to spurious interrupts.
The best numbers will be attained, and attained with fewer trials, when 
interrupts can be avoided.


UNDERSTANDING AND VISUALIZING THE OUTPUT

   The results of the benchmark are written to mass storage.  Our makefile
creates an executable program named "hint".  The output data file is named
after the name of the data type being tested like "DOUBLE" or "LONGLONG".
Other diagnostic information is written to the screen.  This information 
includes

   * the number of bits of accuracy of each data type used,
   * the resulting grid size used for HINT,
   * a series of periods (.) indicating that HINT is running, with "#"
     used to indicate a retrial of an apparently inaccurate measurement,
   * the reason for quitting the run, and
   * the Net QUIPS.
  
   The Net QUIPS represents the integral of the Quality step function divided
by time squared.  This is the area under a graph of QUIPS versus the log of 
the time.  This simply means that the QUIPS at a given time is weighted lower 
in proportion to how long it takes to get to that QUIPS rate. For more 
information see "HINT: A New Way To Measure Computer Performance",
Ames Laboratory Technical Report Number IS-5109, Category UC-405.
   The data file is organized in five columns: time, QUIPS, Quality, 
subintervals, and memory use in bytes.  The first two columns are used to 
produce the QUIPS graph.  The third and fourth columns are Quality and 
subintervals.  These columns can be used to check for loss of quality due to
insufficient precision and poor choices of which rectangle to split. The fifth
is useful for finding the sizes of memory regimes, like where primary cache
saturates or where virtual memory is first invoked.
   The file is set up in a format suitable for gnuplot or similar plotting
packages.  QUIPS graphs should be plotted on a semi-log scale with log of
time as the horizontal axis and QUIPS as the vertical axis. The following
gnuplot commands would be suitable to display the QUIPS graph from the file
"DOUBLE":

            > set logscale x
            > plot "DOUBLE"

QUIPS vs. memory use can also be plotted to reveal memory regime sizes,
by using the following gnuplot command:

            > plot "DOUBLE" using 5:2

   Although the human tendency is to try to turn performance into a single
number, our hope is that machines will be compared using the entire QUIPS
curve and not just the Net QUIPS rating.  Just as the evaluation of cars
involves many variables other than 0-60 acceleration time, computers can
never be judged by one number alone.  These QUIPS graphs reveal many
traits of a particular computer, such as
    
   * The "startup time" to the first data point, a measure of nimbleness
   * The cost for a sum collapse for parallel computers
   * The number of distinct memory regimes
   * The "usable" size of each regime
   * The relative speed of access of each regime
   * Tendency to be erratic because of interrupts

Plotting the QUIPS curves of multiple computers on the same graph 
reveals the relative strengths and weaknesses of the machines.  For example,
a computer might be fast only on small problems (like 100 by 100 LINPACK)
but much slower on real applications that do not fit in cache.  Using the
knowledge gained from the QUIPS graph coupled with that of the expected 
workload will help to judge which computer is best suited for the workload.


REPORTING RESULTS

   We are trying to create an atlas of HINT results.  We would appreciate
all information and results sent to us.  Please include the following 
information as well as any output data files generated by HINT.  Also include
the modified code and an explanation of your modifications.  Note that your
name is required as well as the machine statistics.  If there is any information
that you are unable or unwilling to stand behind, please leave the entry blank.
Also, if the information was not personally measured, like power consumption,
please indicate by placing an asterisk (*) at the end of the entry.  Send all
information and data files to:

            hint@ameslab.gov     


REPORT FORM

   Modify one of the following examples to match your computer.
    
Serial Computer: (typical workstation)
  Personal Information
    Name:                             Quinn O. Snell
    Company:                          Ames Laboratory
    Address:                          236 Wilhelm
                                      Iowa State University
                                      Ames, Iowa   50011 - 3020
    Email:                            snell@scl.ameslab.gov
    Date:                             June 20, 1994

  Computer Architecture
    Computer Vendor:                  Silicon Graphics Inc.
    Computer Model name/number:       Indy SC 
    Operating System:                 IRIX 5.2 
    Graphics:                         Indy 24-bit graphics
    Standalone or Multiuser:          Multiuser
    Processor:                        MIPS R4000
    Floating Point Coprocessor:       MIPS R4010
    Clock Rate:                       100 MHZ   *(Not personally measured)
    # of Processors:                  1
    # used:                           1

  Communication Architecture          Not applicable
    Topology:                    
    Interprocessor Latency:
    Interprocessor Bandwidth:
      * Note: If communication time is not equal to 
              latency + bandwidth * size, please explain. 

  Physical Statistics
    Serial Number:                    08006906E67A
    Physical Dimensions:              41cm x 35cm x 8cm
    Weight:
    Power Consumption:
    Purchase Date:                    9/30/93
    List Price at Purchase Date:

  Memory Architecture
    Memory Size:                      48 MB
    Memory Interleave:
    Memory Bandwidth:                 267 MB / sec  *
    Primary Cache Size:               8 KB data / 8 KB instruction  *
    Secondary Cache Size:             1 MB  *
    Cache Associativity:
    Type of Hard Disk(Virtual Mem):   SCSI 2
    Hard Disk brand name:             IBM
    Hard Disk Size:                   1.2 GB  *
    Hard Disk access time:

  HINT Executable Statistics and Results
    HINT version:                     1.0
    Language Used:                    C (ANSI)
    Compiler:                         cc
    Options Used:                     -O3 -non_shared
    Data Type for Computation:        double
    Data Type for Indexing:           int
    Net QUIPS:                        2.32 MQUIPS


Parallel Computer:
  Personal Information
    Name:                             Quinn O. Snell
    Company:                          Ames Laboratory
    Address:                          236 Wilhelm
                                      Iowa State University
                                      Ames, Iowa   50011 - 3020
    Email:                            snell@scl.ameslab.gov
    Date:                             June 20, 1994

  Computer Architecture
    Computer Vendor:                  Intell
    Computer Model name/number:       Paragon
    Operating System:                 OSF/1 Release 1.0.4 Server 1.2 R1.2
    Graphics:
    Standalone or Multiuser:          Standalone
    Processor:                        i860 xp
    Floating Point Coprocessor:       none
    Clock Rate:                       50 MHZ  *
    # of Processors:                  32
    # used:                           32

  Communication Architecture          
    Topology:                         Mesh
    Interprocessor Latency:
    Interprocessor Bandwidth:
      * Note: If communication time is not equal to 
              latency + bandwidth * size, please explain. 

  Physical Statistics
    Serial Number:
    Physical Dimensions:              56cm x 156cm x 107cm  *
    Weight:                           1,000 lbs  *
    Power Consumption:                11,000 Watts  *
    Purchase Date:                    3/93
    List Price at Purchase Date:

  Memory Architecture
    Memory Size:                      32 MB / node  *
    Memory Interleave:
    Memory Bandwidth:                 400 MB / sec  *
    Primary Cache Size:               16 KB data  / 16 KB instruction  *
    Secondary Cache Size:             none
    Cache Associativity:
    Type of Hard Disk(Virtual Mem):   RAID SCSI 2
    Hard Disk brand name:             Maxtor
    Hard Disk Size:                   4 GB  *
    Hard Disk access time:

  HINT Executable Statistics and Results
    HINT version:                     1.0
    Language Used:                    C (ANSI)
    Compiler:                         cc
    Options Used:                     -O3 -Knoieee
    Data Type for Computation:        double
    Data Type for Indexing:           int
    Net QUIPS:

