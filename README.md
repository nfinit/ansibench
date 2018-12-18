# ANSI C Benchmarks for Unix and Unix-like systems

_Jump to: [LINPACK](http://github.com/nfinit/ansibench#linpack), 
          [STREAM](http://github.com/nfinit/ansibench#stream),
          [Whetstone](http://github.com/nfinit/ansibench#whetstone),
          [Dhrystone](http://github.com/nfinit/ansibench#dhrystone)_

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

Some benchmarks also may require special accomodations to build on certain
operating systems and compiler configurations, these overrides can be
specified by setting the `ov` parameter to the name of a valid override
file in the `overrides/[program]` directory without extension. For example,
building the STREAM benchmark under HP-UX requires appending `ov=hpux` or
`ov=hpux-mp` to the `make` command, these correspond to `hpux.mk` and
`hpux-mp.mk` in the `overrides/stream` directory, respectively.

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

While a fully optimized GCC build with `gcc-ofast.mk` may use:

`make occ=gcc-ofast`

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
double-precision versions of the benchmark.

##### [LINPACK results](http://github.com/nfinit/ansibench/wiki/LINPACK-results) 
---------------------------------------------------------------------------
#### STREAM

STREAM is a synthetic memory benchmark first developed in 1991 by 
Dr. John McCalpin at the University of Delaware's College of Marine Studies.
It is described by McCalpin as "an extremely simplified representation of the
low-compute-intensity, long-vector operations characteristic of ocean
circulation models" and has since become a standard for measuring
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

##### [STREAM results](http://github.com/nfinit/ansibench/wiki/STREAM-results)
---------------------------------------------------------------------------
#### Whetstone

The Whetstone benchmark is a synthetic benchmark that primarily measures 
a computer's floating-point performance. Originally written in ALGOL 60 in 1972 
by Harold Curnow of the Technical Support Unit of the United Kingdom's 
Department of Trade and Industry, it was one of the first general-prupose
benchmarks to set industry standards for evaluating computing performance.

The Whetstone benchmark is based on prior work by Brian Wichmann of the UK's
National Physical Laboratory (NPL) who collected statistics from a modified
version of the "Whetstone" ALGOL compiler running on an [English Electric KDF9
computer](https://en.wikipedia.org/wiki/English_Electric_KDF9) at the NPL 
and used the data to build a set of 42 simple statements that could be used 
to evaluate the efficiency of other compilers and processor performance. 

Whetstone speed ratings are measured in Whetstone Instructions Per Second 
(WIPS), and most early versions of the benchmark output ratings in KWIPS, 
while most newer versions (including this one) produce ratings in MWIPS. 
Although Whetstone performs a general mix of calculations, most of them 
are still overwhelmingly floating-point heavy, and because only a small 
amount of data is referenced, architectural factors such as the performance 
of the memory subsystem are barely if at all evaluated, especially if the 
processor being evaluated has large enough caches.

The Whetstone version included in this package is the "updated" C translation
found on the [Netlib repository](http://www.netlib.org/benchmark/whetstone.c)
with minimal modification, mostly just to printed output. This version was
translated directly from the original ALGOL 60 version of the benchmark, and
has output similar to the [FORTRAN version](http://www.netlib.org/benchmark/whetstoned).

##### Running Whetstone

Whetstone can be built and run immediately by issuing the command 
`make run` along with any overrides specified by the `occ` and `ov` 
parameters.

By default, the Whetstone benchmark loops 1,000,000 times. This can be 
increased or decreased to better evaluate a given system by setting the 
`loops` parameter when running the benchmark through the makefile, or 
by specifying the number of loops when running the executable directly. 
The executable also has an optional `-c` flag for continuous looping 
operation, which is not used by the makefile.

It's always recommended to build Whetstone with `PRINTOUT` defined for proper
output, this ensures that optimizing compilers do not over-optimize the
benchmark by omitting computations whose end result are never shown to the
user.

##### [Whetstone results](http://github.com/nfinit/ansibench/wiki/Whetstone-results)
---------------------------------------------------------------------------
#### Dhrystone

A pun on the name of the floating-point focused "Whetstone" benchmark, the
Dhrystone benchmark is, like Whetstone, a synthetic benchmark derived from
statistical analysis with the goal of representing an "average" program.
Dhrystone is unlike Whetstone in that it focuses more on integer arithmetic,
making it more relevant to small systems and typical computing use cases 
in general than the more scientific and technically-oriented Whetstone.

Dhrystone was originally written in the Ada programming language by Reinhold P. 
Weicker of Siemens Nixdorf Information Systems in 1984, based on analysis of a
number of programs in numerous languages. Weicker characterized these programs
based on common constructs such as procedure calls and variable assignments, and
used this data to write a benchmark corresponding to a "representative mix" of
these features, similar to the design process of the Whetstone benchmark over 
a decade earlier.

Dhrystone was first ported to C by Rick Richardson of PC Research, Inc. and 
distributed via Usenet. Richardson and Weicker later collaborated on subsequent
versions of the benchmark, their work mostly centered around standardizing the
Ada, C and Pascal versions as well as out-smarting increasingly intelligent
optimizing compilers.

Dhrystone speed ratings are measured in Dhrystones Per Second, corresponding to
the number of times the main Dhrystone loop iterates in a single second. This
quantity is often further refined into "VAX MIPS," corresponding to a multiple
of the [DEC VAX-11/780 superminicomputer](http://en.wikipedia.org/wiki/VAX-11)'s
reported score of 1,757 Dhrystones per second.

While Dhrystone attempts to emulate the "typical" program, it is nonetheless
unsuitable for use as a sole means of benchmarking a system for a number of
reasons, many cited by the authors themselves:
* Dhrystone only evaluates processor integer performance, it does not evaluate other
  significant architectural components such as memory/disk subsystems, or perform any
  I/O operations. Dhrystone also makes limited use of operating system calls.
* Dhrystone is an extremely small benchmark operating on an extremely small data set,
  both of which can easily fit completely into extremely fast modern processor caches.
  Most "typical" programs are too large to completely fit in cache, and often operate
  on data stored in memory or on disk as well as cached, frequently accessed data.
* Dhrystone's integer/system focus may paint a skewed picture of systems designed with
  an emphasis on scientific and technical computing where floating-point math is more
  prevalent.
* The C version of Dhrystone places increased emphasis on string operations compared to
  the reference benchmarks, due to C's lack of a built-in string data type.

With this in mind, it's important to treat Dhrystone results as only a rough overview
of a system processor's integer performance under very ideal conditions, and combine it
with other benchmarks when evaluating a system as a whole. Dhrystone nonetheless is
still widely used in the industry, especially in embedded systems where VAX MIPS is
still often cited in marketing literature.

The Dhrystone version included in this package is the 
[most widely used version (2.1)](http://www.netlib.org/benchmark/dhry-c) 
with some modifications mostly to make it acceptable to ANSI-compliant C compilers 
as well as automation improvements such as the ability to take in the number of 
iterations as an argument at execution time. It has also been modified to compute
and report the VAX MIPS rating from the benchmark result and display it after the
Dhrystones per second rating.

Because the C Dhrystone translation is still mostly written in K&R-style C, it might
still not be acceptable to some stricter compilers and may need to be revised further
in the future.

##### Running Dhrystone

Dhrystone can be built and run immediately by issuing the command 
`make run` along with any overrides specified by the `occ` and `ov` 
parameters, however the default parameters likely will not be suitable
for your system.

By default, the Dhrystone benchmark loops 10,000,000 times. This can be 
increased or decreased to better evaluate a given system by setting the 
`n` parameter when running the benchmark through the makefile, or 
by specifying the number of loops when running the executable directly. 

Dhrystone requires the parameter `HZ` to be defined at compile time, which
corresponds to the granularity of the timing function. This is typically 100
on most newer systems and is the default value, however it can still vary and
should be confirmed before running the benchmark. If your system can execute
POSIX shell scripts, the script `gethz.sh` will compile and run a simple program
that determines the value of the `_SC_CLK_TCK` parameter which corresponds to the
number of clock "ticks" per second as configured in the kernel. This information
can also be retrieved by issuing `getconf _SC_CLK_TCK` (or `getconf CLK_TCK` if
`_SC_CLK_TCK` is unsupported) and passing the value into make using the `hz`
parameter. An example build and run operation might be:
`make run n=50000000 hz=120 occ=gcc-ofast` to build and run Dhrystone on a GNU/Linux
system with maximal optimization and a kernel configured for 120 clock "ticks" per
second.

The timing function to use can also be passed at compile time, by default Dhrystone
will be built to use wall clock time with `time()` specified by the `-DTIME` flag, 
but it can also be configured to use `times()` for process time with `-DTIMES`. 
You can configure Dhrystone to be built with the `times()` function for timing by
including `time=TIMES` in your `make` command.

The makefile is configured to build and run Dhrystone both with and without register 
variables, meaning that Dhrystone will assign some variables to dedicated processor
registers when possible for faster access than from cache or memory.

##### [Dhrystone results](http://github.com/nfinit/ansibench/wiki/Dhrystone-results)
