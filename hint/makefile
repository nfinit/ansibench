###########################################################################
# STANDARD COMPILER CONFIGURATION *****************************************
# By default, this makefile produces an unoptimized executable with GCC.
# It's recommended to choose or build a proper compiler configuration for
# your system in the "override" directory, specify these overrides with
# the argument "occ=[file without extension]" when making the executables.
###########################################################################
CC = gcc
CFLAGS = -ansi
###########################################################################
# ADVANCED COMPILER CONFIGURATION *****************************************
# Configures standard libraries and compiler flags to ensure portability
# It's recommended to override these with a separate file as well.
###########################################################################
DFLAG  = -D
IFLAG  = -I
OFLAG  = -o
LFLAG  = -l
###########################################################################
# PATH CONFIGURATION ******************************************************
# Default paths for storage and searching.
###########################################################################
OVERRIDE   = ../override
OVERRIDECC = $(OVERRIDE)/cc
OVERRIDEHT = $(OVERRIDE)/hint
SDIR       = ./src
BDIR       = ./bin
DDIR       = ./data
IDIR	   = ./include
###########################################################################
# FILE AND EXECUTABLE CONFIGURATION ***************************************
# Change these only if you'd like different names for the executables or
# have renamed the input source files.
###########################################################################
INPUT = $(SDIR)/hint.c $(SDIR)/hkernel.c
OUT =   $(BDIR)/hint
###########################################################################
# OVERRIDE INCLUDES // DO NOT MODIFY BEYOND THIS POINT ********************
###########################################################################
-include $(OVERRIDECC)/$(occ).mk
-include $(OVERRIDEHT)/$(ov).mk
###########################################################################
# BUILD/RUN OPERATIONS // DO NOT MODIFY BEYOND THIS POINT *****************
###########################################################################
all: char short int float double ldouble 
run: $(dtype)
	@$(OUT)-$(dtype)
dirs:
	@mkdir -p $(BDIR)
	@mkdir -p $(DDIR)
###########################################################################
# EXECUTABLE BUILD/RUN OPTIONS // DO NOT MODIFY BEYOND THIS POINT *********
###########################################################################
char: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(LFLAG)m $(IFLAG)$(IDIR) $(DFLAG)unix $(DFLAG)CHAR $(DFLAG)IINT $(INPUT) $(OFLAG) $(OUT)-char
short: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(LFLAG)m $(IFLAG)$(IDIR) $(DFLAG)unix $(DFLAG)SHORT $(DFLAG)IINT $(INPUT) $(OFLAG) $(OUT)-short
int: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(LFLAG)m $(IFLAG)$(IDIR) $(DFLAG)unix $(DFLAG)INT $(DFLAG)IINT $(INPUT) $(OFLAG) $(OUT)-int
float: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(LFLAG)m $(IFLAG)$(IDIR) $(DFLAG)unix $(DFLAG)FLOAT $(DFLAG)IINT $(INPUT) $(OFLAG) $(OUT)-float
double: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(LFLAG)m $(IFLAG)$(IDIR) $(DFLAG)unix $(DFLAG)DOUBLE $(DFLAG)ILONG $(INPUT) $(OFLAG) $(OUT)-double
ldouble: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(LFLAG)m $(IFLAG)$(IDIR) $(DFLAG)unix $(DFLAG)LDOUBLE $(DFLAG)ILONG $(INPUT) $(OFLAG) $(OUT)-ldouble
###########################################################################
# FILESYSTEM CLEANUP OPERATIONS // DO NOT MODIFY BEYOND THIS POINT ********
###########################################################################
clean:
	@-rm -f $(OUT) core a.out *.o
	@-rm -f $(BDIR)/*
	@-rmdir $(BDIR)
	@-rm -f $(DDIR)/*
	@-rmdir $(DDIR)
###########################################################################
# END OF MAKEFILE *********************************************************
###########################################################################
