# DEFAULT BENCHMARK CONFIGURATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc          = gcc
n           = 100 

##############################################################################
# DO NOT MODIFY BEYOND THIS POINT                                            #
##############################################################################
-include ../mk/$(cc)/stdflags.mk
-include ../mk/$(cc)/opt/$(opt).mk
-include ../mk/$(cc)/xflags/$(xflags).mk
-include ../mk/$(cc)/linpack/stdflags.mk
# ----------------------------------------------------------------------------
BINDIR = ./bin
OUT    = $(BINDIR)/linpack
INPUT  = ./src/linpack.c
# ----------------------------------------------------------------------------
CARGS  += $(OPTLEVEL) $(XCFLAGS) $(INPUT) -o$(OUT) $(CFLAGS)
# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------
all: bin 
run: all
	@date
	@echo "Running LINPACK..." 
	@$(OUT)sp $(n) 
	@$(OUT)dp $(n)
dirs:
	@mkdir -p $(BINDIR)
bin: sp dp
sp: dirs
	$(CC) $(CARGS)sp $(SPFLAG) 
dp: dirs
	$(CC) $(CARGS)dp 
clean:
	@-rm -f $(OUT) core a.out *.o
	@-rm -f $(BINDIR)/*
	@-rmdir $(BINDIR)
