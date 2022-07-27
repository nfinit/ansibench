# Standard flags for GCC
# These flags are intended to generate the maximum number of warnings possible
# to aid in making benchmarks more portable and demonstrate compliance. Certain
# warnings are omitted, such as those regarding pragmas of which many platform
# specific examples may be used that the compiler will simply ignore.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CC        = gcc
OPTLEVEL  = -O2
CFLAGS   += -I./include
CFLAGS   += -g -ansi -Wall -Wextra -pedantic
CFLAGS   += -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
CFLAGS   += -Wno-unknown-pragmas
