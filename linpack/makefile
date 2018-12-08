###########################################################################
# STANDARD COMPILER CONFIGURATION *****************************************
# By default, this makefile produces an unoptimized executable with GCC.
# It's recommended to choose or build a proper compiler configuration for
# your system in the "override" directory, specify these overrides with
# the argument "occ=[file without extension]" when making the executables.
###########################################################################
CC = gcc
CFLAGS = -Wall -ansi 
###########################################################################
# ADVANCED COMPILER CONFIGURATION *****************************************
# Configures standard libraries and compiler flags to ensure portability
# It's recommended to override these with a separate file as well.
###########################################################################
LFLAGS = -lm
DFLAG  = -D
OFLAG  = -o
###########################################################################
# PATH CONFIGURATION ******************************************************
# Default paths for storage and searching.
###########################################################################
OVERRIDE   = ../override
OVERRIDECC = $(OVERRIDE)/cc
OVERRIDELP = $(OVERRIDE)/linpack
SDIR       = ./src
BDIR       = ./bin
###########################################################################
# FILE AND EXECUTABLE CONFIGURATION ***************************************
# Change these only if you'd like different names for the executables or
# have renamed the input source file.
###########################################################################
INPUT = $(SDIR)/linpack.c
SPOUT = $(BDIR)/linpacksp
DPOUT = $(BDIR)/linpackdp
###########################################################################
# MISCELLANEOUS OPTIONS ***************************************************
###########################################################################
n = 1000
###########################################################################
# OVERRIDE INCLUDES // DO NOT MODIFY BEYOND THIS POINT ********************
###########################################################################
-include $(OVERRIDECC)/$(occ).mk
-include $(OVERRIDELP)/$(ov).mk
###########################################################################
# BUILD/RUN OPERATIONS // DO NOT MODIFY BEYOND THIS POINT *****************
###########################################################################
all: sp dp 
run: all 
	@echo "SINGLE PRECISION************************************"
	@$(SPOUT) $(n)
	@echo "DOUBLE PRECISION************************************"
	@$(DPOUT) $(n)
	@echo "****************************************************"
dirs:
	@mkdir -p $(BDIR)
###########################################################################
# EXECUTABLE BUILD/RUN OPTIONS // DO NOT MODIFY BEYOND THIS POINT *********
###########################################################################
sp: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(LFLAGS) $(DFLAG)SP $(INPUT) $(OFLAG) $(SPOUT)
dp: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(LFLAGS) $(DFLAG)DP $(INPUT) $(OFLAG) $(DPOUT) 
###########################################################################
# FILESYSTEM CLEANUP OPERATIONS // DO NOT MODIFY BEYOND THIS POINT ********
###########################################################################
clean:
	@-rm -f $(SPOUT) $(DPOUT) core a.out *.o
	@-rm -f $(BDIR)/*
	@-rmdir $(BDIR)
###########################################################################
# END OF MAKEFILE *********************************************************
###########################################################################
