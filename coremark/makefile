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
###########################################################################
# PORTING CONFIGURATION ***************************************************
# Override the default porting directory by with "port=[port_dir]"
###########################################################################
port=ansibench
###########################################################################
# PATH CONFIGURATION ******************************************************
# Default paths for storage and searching.
###########################################################################
OVERRIDE   = ../override
OVERRIDECC = $(OVERRIDE)/cc
OVERRIDECM = $(OVERRIDE)/coremark
SDIR       = ./src
BDIR       = ./bin
IDIR	   = ./include
###########################################################################
# FILE AND EXECUTABLE CONFIGURATION ***************************************
# Change these only if you'd like different names for the executables or
# have renamed the input source files.
###########################################################################
INPUT = $(SDIR)/core_main.c $(SDIR)/core_matrix.c $(SDIR)/core_list_join.c $(SDIR)/core_state.c $(SDIR)/core_util.c $(SDIR)/core_portme.c
OUT =   $(BDIR)/coremark
###########################################################################
# MISCELLANEOUS CONFIGURATION *********************************************
###########################################################################
n=20000
###########################################################################
# OVERRIDE INCLUDES // DO NOT MODIFY BEYOND THIS POINT ********************
###########################################################################
-include $(OVERRIDECC)/$(occ).mk
-include $(OVERRIDECM)/$(ov).mk
###########################################################################
# BUILD/RUN OPERATIONS // DO NOT MODIFY BEYOND THIS POINT *****************
###########################################################################
all: bin 
run: all 
	@$(OUT) 0x0 0x0 0x66 $(n) 7 1 2000
dirs:
	@mkdir -p $(BDIR)
###########################################################################
# EXECUTABLE BUILD/RUN OPTIONS // DO NOT MODIFY BEYOND THIS POINT *********
###########################################################################
bin: dirs $(INPUT) 
	$(CC) $(CFLAGS) $(XFLAGS) $(IFLAG)$(IDIR) $(DFLAG)COMPILER_FLAGS=\"$(CFLAGS)\" $(DFLAG)PERFORMANCE_RUN=1 $(DFLAG)ITERATIONS=$(n) $(INPUT) $(OFLAG) $(OUT)
###########################################################################
# FILESYSTEM CLEANUP OPERATIONS // DO NOT MODIFY BEYOND THIS POINT ********
###########################################################################
clean:
	@-rm -f $(OUT) core a.out *.o
	@-rm -f $(BDIR)/*
	@-rmdir $(BDIR)
###########################################################################
# END OF MAKEFILE *********************************************************
###########################################################################
