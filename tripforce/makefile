# DEFAULT BENCHMARK CONFIGURATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc      = gcc
search  = 'ansi' 
mp      = -fopenmp 
 
##############################################################################
# DO NOT MODIFY BEYOND THIS POINT                                            #
##############################################################################
-include ../mk/$(cc)/stdflags.mk
-include ../mk/$(cc)/opt/$(opt).mk
-include ../mk/$(cc)/xflags/$(xflags).mk
-include ../mk/$(cc)/tripforce/stdflags.mk
-include ../mk/$(cc)/tripforce/platforms/$(platform).mk
# ----------------------------------------------------------------------------
BINDIR = ./bin
OUT    = $(BINDIR)/tripforce
INPUT  = ./src/tripforce.c
# ----------------------------------------------------------------------------
CARGS  += $(INPUT) -o$(OUT) $(OPTLEVEL) $(CFLAGS) $(XCFLAGS)
# ----------------------------------------------------------------------------
all: bin 
run: all
	@date
	@echo "Running tripforce..." 
	@$(OUT) $(search)
dirs:
	@mkdir -p $(BINDIR)
bin: dirs
	$(CC) $(CARGS) 
clean:
	@-rm -f $(OUT) core a.out *.o
	@-rm -f $(BINDIR)/*
	@-rmdir $(BINDIR)
