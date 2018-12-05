# ANSI C Benchmarks for Unix and Unix-like systems

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
