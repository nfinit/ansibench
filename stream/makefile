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
OPENMP = -fopenmp
DFLAG  = -D
OFLAG  = -o
###########################################################################
# PATH CONFIGURATION ******************************************************
# Default paths for storage and searching.
###########################################################################
OVERRIDE   = ../override
OVERRIDECC = $(OVERRIDE)/cc
OVERRIDEST = $(OVERRIDE)/stream
SDIR       = ./src
BDIR       = ./bin
###########################################################################
# FILE AND EXECUTABLE CONFIGURATION ***************************************
# Change these only if you'd like different names for the executables or
# have renamed the input source file.
###########################################################################
INPUT = $(SDIR)/stream.c
OUT =   $(BDIR)/stream
###########################################################################
# MISCELLANEOUS CONFIGURATION *********************************************
###########################################################################
DARRS = STREAM_ARRAY_SIZE
n     = 10000000
###########################################################################
# OVERRIDE INCLUDES // DO NOT MODIFY BEYOND THIS POINT ********************
###########################################################################
-include $(OVERRIDECC)/$(occ).mk
-include $(OVERRIDEST)/$(ov).mk
###########################################################################
# BUILD/RUN OPERATIONS // DO NOT MODIFY BEYOND THIS POINT *****************
###########################################################################
all: bin 
run: all 
	@$(OUT)
dirs:
	@mkdir -p $(BDIR)
###########################################################################
# EXECUTABLE BUILD/RUN OPTIONS // DO NOT MODIFY BEYOND THIS POINT *********
###########################################################################
bin: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(OPENMP) $(DFLAG)$(DARRS)=$(n) $(INPUT) $(OFLAG) $(OUT)
###########################################################################
# FILESYSTEM CLEANUP OPERATIONS // DO NOT MODIFY BEYOND THIS POINT ********
###########################################################################
clean:
	@rm -f $(OUT) core a.out *.o
	@rm -f $(BDIR)/*
	@rmdir $(BDIR)
###########################################################################
# END OF MAKEFILE *********************************************************
###########################################################################
