# Standard flags for GCC
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CC        = gcc
OPTLEVEL  = -O2 
CFLAGS   += -I./include
CFLAGS   += -g -ansi
ifeq "$(ANSIBENCH_DEBUG)" "1"
	-include ../mk/gcc/xflags/debug.mk
endif
