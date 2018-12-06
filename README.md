# ANSI C Benchmarks for Unix and Unix-like systems

_Jump to: [LINPACK](http://github.com/nfinit/ansibench#linpack), 
          [STREAM](http://github.com/nfinit/ansibench#stream)_

This repository packages a selection of ANSI C program sources useful for 
benchmarking a wide variety of systems and compilers, including a number 
of classic industry standard benchmarks as well as some more practical 
programs that can also be used as benchmarks.

All programs presented in this package are tested with GCC and HP C in 
ANSI mode to ensure they function as expected.

Always remember that a benchmark is really only accurate for evaluating 
a system's performance on that very specific set of operations which don't 
always reflect your system's typical workload, and thus only paints a 
partial picture of your system's overall capabilities. Many of the programs 
included in this package are single-threaded and very CPU-focused, and won't 
tell you as much about your system's memory, disk, or I/O capabilities 
among other critical architectural features that may allow it to pull 
ahead of supposedly faster systems in many use cases.

Nonetheless, these programs are still easy and useful tools for evaluating 
compilers and giving you a *rough* idea of how your system performs and 
how it may compare to others.

## Building, configuring and running benchmarks

Each benchmark in this package resides in its own directory and can be 
quickly built by issuing the `make` command in that directory. By default, 
these benchmarks are built without any optimizations for testing purposes.

Benchmarks can then be run by issuing `make run`, though they may need
parameters passed to them in order to run properly. These parameters are
described in each benchmark's section.

### Optimizing benchmarks

All makefiles in this package by default attempt to build a benchmark with 
the GNU C Compiler and no optimizations. This is for testing purposes, to 
ensure that a benchmark can build and run properly on the system before
further evaluation. However, for actually evaluating the performance of
your system or compiler, this may be unsuitable.

Makefiles can be tweaked to configure the compiler, however they also
can be configured in a more modular manner using **override** files that
allow for more convenient testing at different optimization levels, or
with different compilers.

All C compiler override files reside in the `override/cc` directory in 
the repository root, with the extension `.mk`. Override files are simply
text files with new variable definitions, usually for `CC` and `CFLAGS`,
though other variables used by the makefile such as `XFLAGS` can be
configured here as well. You can either create a new override file or
copy an existing override and modify it.

Compiler overrides are passed to the makefile by setting the `occ`
parameter to a valid override file name (**without** the `.mk`
extension) when issuing the `make` command. For example, overriding
for the HP C compiler on HP UX with `hp-c.mk`  would use this command:

`make occ=hp-c`

While a fully optimized GCC build with `gcc-opt.mk` may use:

`make occ=gcc-opt`

## Packaged benchmarks

### Classic Benchmarks
---------------------------------------------------------------------------
#### LINPACK

First introduced in 1979, the LINPACK benchmark measures a system's 
floating-point math capabilities by solving a dense system of linear 
equations. LINPACK remains an industry standard particularly in
supercomputing, where it is used to build the TOP500 list of the world's
fastest computers. LINPACK measures system performance in terms of Floating
Point Operations per Second, or FLOPS. Most small systems today typically 
operate on the order of megaFLOPS, gigaFLOPS and teraFLOPS, while
supercomputers often operate in the petaFLOPS range.

LINPACK evaluates performance with both single-precision (32-bit) and
double-precision (64-bit) floating-point numbers, usually selectable
at compile time. Single-precision values are most frequently used in 
"everyday" desktop computing applications where precision and 
utmost accuracy are not as necessary, while double-precision values
are more frequently used in scientific and technical applications where
minimal approximation is preferable. Many LINPACK variants default to
double-precision (including the one in this package) because of the
benchmark's significance in high-performance computing.

This version of LINPACK is a C translation of the original FORTRAN version
first written in 1988 by Bonnie Toy and later updated in 1993 by Will 
Menninger, it most notably allows for user-definable matrix sizes and
averages rolled and unrolled performance in its report. The original
source can be found [here](http://www.netlib.org/benchmark/linpackc.new).

This source has been slightly modified in this package to make it easier
to automate and execute from scripts. It can now take the matrix size as
an argument and the output has changed slightly for a cleaner look.

##### Running LINPACK

LINPACK has a single parameter `n` which can be passed to it when running 
with `make run`, this corresponds to the matrix size. Typical matrices 
used with LINPACK are of order 100x100 or 1000x1000, though any value of 
`n` can be passed in, within reason. LINPACK can also be run without the
makefile by simply running the executable, which will then ask for `n` if
it wasn't supplied as the first argument.

The single LINPACK source file is used to build two executables, `linpacksp` 
for evaluating single-precision performance and `linpackdp` for evaluating 
double-precision performance. Both are identical in functionality.

Running LINPACK with `make run` will run both the single-precision and 
double-precision versions of the benchmark, an example session follows:
```
$ make run n=1000 occ=hp-c
        cc -Aa -fast  -lm -DSP ./src/linpack.c -o ./bin/linpacksp
        cc -Aa -fast  -lm -DDP ./src/linpack.c -o ./bin/linpackdp
SINGLE PRECISION************************************
LINPACK benchmark, Single precision.
Machine precision:  6 digits.
Array size 1000 X 1000.
Memory required:  3914K.
Average rolled and unrolled performance:

    Reps Time(s) DGEFA   DGESL  OVERHEAD    KFLOPS
----------------------------------------------------
       2   0.96  86.46%   2.08%  11.46%  394509.750
       4   1.91  87.43%   0.52%  12.04%  399206.438
       8   3.81  88.19%   0.79%  11.02%  395673.656
      16   7.65  88.76%   0.52%  10.72%  392776.938
      32  15.28  88.09%   0.72%  11.19%  395381.938

DOUBLE PRECISION************************************
LINPACK benchmark, Double precision.
Machine precision:  15 digits.
Array size 1000 X 1000.
Memory required:  7824K.
Average rolled and unrolled performance:

    Reps Time(s) DGEFA   DGESL  OVERHEAD    KFLOPS
----------------------------------------------------
       1   1.21  93.39%   0.83%   5.79%  147076.023
       2   2.40  94.17%   0.83%   5.00%  147076.023
       4   4.81  93.97%   1.25%   4.78%  146433.770
       8   9.61  94.28%   0.73%   4.99%  146914.932
      16  19.20  94.27%   0.83%   4.90%  146914.932

****************************************************
```
##### [LINPACK results](https://github.com/nfinit/ansibench/wiki/LINPACK-results) 
---------------------------------------------------------------------------
#### STREAM

STREAM is a synthetic memory benchmark first developed in 1991 by 
Dr. John McCalpin at the University of Delaware's College of Marine Studies.
It is described by McCalpin as "an extremely simplified representation of the
low-compute-intensity, long-vector operations characteristic of ocean
circulation models" and has since become an industry standard for measuring
memory performance on various computer systems.

STREAM measures memory performance using four separately timed kernels 
corresponding to copy, scale, add and "triad" operations, with the latter 
kernel (a combination of the three others) usually cited for in-general 
comparison. STREAM results are often used alongside LINPACK when evaluating
supercomputer performance, as memory bandwidth is often even more important
than raw processor speed when working with the large data sets typical in
supercomputing workloads.

This is the "official" C version of STREAM which can be found on the
[STREAM website](http://www.cs.virginia.edu/stream/). The source has been very
minimally modified for inclusion in this package mostly to make it acceptable
to an ANSI C compiler and easier to automate using a makefile. Only comments,
print statement formatting and some macro definitions have been modified
(to allow the default array size to still be properly set in the event of an 
empty STREAM array size definition argument from a non-GNU makefile) with the
deprecated Time Zone structure removed in the `mysecond()` function.
Because of the minimal nature of these modifications, this version of STREAM
should still be compliant with the official 
[run rules](http://www.cs.virginia.edu/stream/ref.html#runrules).

##### Running STREAM 

STREAM can be built and run immediately by issuing the command `make run` along
with any overrides specified by the `occ` and `ov` parameters.

STREAM by default operates on an array of 10,000,000 elements, which may be
too small or too large for some systems. In a similar manner to LINPACK, the
array size can be configured from the makefile using the parameter `n`. Unlike
LINPACK, this parameter is defined at compile-time, and STREAM will need to be
recompiled to use a different array size.

It is recommended to specify an array size at least 4 times the size of your
system's processor caches in order to ensure that the system memory is
actually what is being benchmarked. The default `n`=10,000,000 parameter
should be acceptable for caches up to 4 MiB, but many modern systems are now
shipping with 8 MiB of cache and beyond, meaning `n` will need to be larger
for a result that properly reflects memory performance.

##### [STREAM results](https://github.com/nfinit/ansibench/wiki/STREAM-results)
---------------------------------------------------------------------------
