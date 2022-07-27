# DEFAULT BENCHMARK CONFIGURATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc = gcc
n  = 10000000
mp = -fopenmp 
 
##############################################################################
# DO NOT MODIFY BEYOND THIS POINT                                            #
##############################################################################
-include ../mk/$(cc)/stdflags.mk
-include ../mk/$(cc)/opt/$(opt).mk
-include ../mk/$(cc)/xflags/$(xflags).mk
-include ../mk/$(cc)/stream/stdflags.mk
-include ../mk/$(cc)/stream/platforms/$(platform).mk
# ----------------------------------------------------------------------------
BINDIR = ./bin
OUT    = $(BINDIR)/stream
INPUT  = ./src/stream.c
# ----------------------------------------------------------------------------
CARGS  += -o$(OUT) $(OPTLEVEL) $(CFLAGS) $(XCFLAGS) $(INPUT)
# ----------------------------------------------------------------------------
all: bin 
run: all
	@date
	@echo "Running STREAM..." 
	@$(OUT)
dirs:
	@mkdir -p $(BINDIR)
bin: dirs
	$(CC) $(CARGS) 
clean:
	@-rm -f $(OUT) core a.out *.o
	@-rm -f $(BINDIR)/*
	@-rmdir $(BINDIR)
