###########################################################################
# STANDARD COMPILER CONFIGURATION *****************************************
# By default, this makefile produces an unoptimized executable with GCC.
# It's recommended to choose or build a proper compiler configuration for
# your system in the "override" directory, specify these overrides with
# the argument "occ=[file without extension]" when making the executables.
###########################################################################
CC     = gcc
CFLAGS = -Wall -ansi 
###########################################################################
# ADVANCED COMPILER CONFIGURATION *****************************************
# Configures standard libraries and compiler flags to ensure portability
# It's recommended to override these with a separate file as well.
###########################################################################
DFLAG = -D
IFLAG = -I
OFLAG = -o
###########################################################################
# PATH CONFIGURATION ******************************************************
# Default paths for storage and searching.
###########################################################################
OVERRIDE   = ../override
OVERRIDECC = $(OVERRIDE)/cc
OVERRIDEDS = $(OVERRIDE)/dhrystone
OVERRIDEGL = $(OVERRIDE)/global
SDIR       = ./src
IDIR	   = ./include
BDIR       = ./bin
###########################################################################
# FILE AND EXECUTABLE CONFIGURATION ***************************************
# Change these only if you'd like different names for the executables or
# have renamed the input source file.
###########################################################################
INPUT  = $(SDIR)/dhry_1.c $(SDIR)/dhry_2.c
OUT    = $(BDIR)/dhry
REGOUT = $(BDIR)/dhryreg
###########################################################################
# MISCELLANEOUS OPTIONS ***************************************************
###########################################################################
n    = 10000000
time = TIME
hz   = 100
###########################################################################
# OVERRIDE INCLUDES // DO NOT MODIFY BEYOND THIS POINT ********************
###########################################################################
-include $(OVERRIDECC)/$(occ).mk
-include $(OVERRIDEDS)/$(ov).mk
-include $(OVERRIDEGL)/hz.mk
###########################################################################
# BUILD/RUN OPERATIONS // DO NOT MODIFY BEYOND THIS POINT *****************
###########################################################################
all: reg unreg 
run: all 
	@$(OUT) $(n)
	@$(REGOUT) $(n)
dirs:
	@mkdir -p $(BDIR)
###########################################################################
# EXECUTABLE BUILD/RUN OPTIONS // DO NOT MODIFY BEYOND THIS POINT *********
###########################################################################
unreg: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(IFLAG)$(IDIR) $(DFLAG)HZ=$(hz) $(DFLAG)$(time) $(INPUT) $(OFLAG) $(OUT)
reg: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(IFLAG)$(IDIR) $(DFLAG)HZ=$(hz) $(DFLAG)$(time) $(DFLAG)REG=register $(INPUT) $(OFLAG) $(REGOUT) 
###########################################################################
# FILESYSTEM CLEANUP OPERATIONS // DO NOT MODIFY BEYOND THIS POINT ********
###########################################################################
clean:
	@-rm -f $(OUT) $(REGOUT) core a.out *.o
	@-rm -f $(BDIR)/*
	@-rmdir $(BDIR)
###########################################################################
# END OF MAKEFILE *********************************************************
###########################################################################
