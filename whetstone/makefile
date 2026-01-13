# DEFAULT BENCHMARK CONFIGURATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc = gcc
n  = 1000000
 
##############################################################################
# DO NOT MODIFY BEYOND THIS POINT                                            #
##############################################################################
-include ../mk/$(cc)/stdflags.mk
-include ../mk/$(cc)/opt/$(opt).mk
-include ../mk/$(cc)/xflags/$(xflags).mk
-include ../mk/$(cc)/whetstone/stdflags.mk
# ----------------------------------------------------------------------------
BINDIR = ./bin
OUT    = $(BINDIR)/whetstone
INPUT  = ./src/whetstone.c
# ----------------------------------------------------------------------------
CARGS  += -o$(OUT) $(OPTLEVEL) $(INPUT) $(CFLAGS) $(XCFLAGS)
# ----------------------------------------------------------------------------
all: bin 
run: all
	@date
	@echo "Running Whetstone..." 
	@$(OUT) $(n)
dirs:
	@mkdir -p $(BINDIR)
bin: dirs
	$(CC) $(CARGS) 
clean:
	@-rm -f $(OUT) core a.out *.o
	@-rm -f $(BINDIR)/*
	@-rmdir $(BINDIR)
