# DEFAULT BENCHMARK CONFIGURATION:
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc       = gcc
runtime  = 1.0
dtype    = double

##############################################################################
# DO NOT MODIFY BEYOND THIS POINT                                            #
##############################################################################
-include ../mk/$(cc)/stdflags.mk
-include ../mk/$(cc)/opt/$(opt).mk
-include ../mk/$(cc)/xflags/$(xflags).mk
-include ../mk/$(cc)/hint/stdflags.mk
-include ../mk/$(cc)/hint/platforms/$(platform).mk
# ----------------------------------------------------------------------------
BINDIR     = ./bin
OUT        = $(BINDIR)/hint
INPUT      = ./src/hint.c ./src/hkernel.c
# ----------------------------------------------------------------------------
CARGS = $(OPTLEVEL) $(CFLAGS) $(XCFLAGS) $(INPUT) 
# ----------------------------------------------------------------------------
DATADIR = ./data
# ----------------------------------------------------------------------------
all: char short int float double ldouble 
run: $(dtype)
	@$(OUT)-$(dtype) 
dirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(DATADIR)
char: dirs $(INPUT) 
	$(CC) -DCHAR -DIINT $(CARGS) -o$(OUT)-char
short: dirs $(INPUT) 
	$(CC) -DSHORT -DIINT $(CARGS) -o$(OUT)-short
int: dirs $(INPUT) 
	$(CC) -DINT -DIINT $(CARGS) -o$(OUT)-int
float: dirs $(INPUT) 
	$(CC) -DFLOAT -DIINT $(CARGS) -o$(OUT)-float
double: dirs $(INPUT) 
	$(CC) -DDOUBLE -DILONG $(CARGS) -o$(OUT)-double
ldouble: dirs $(INPUT) 
	$(CC) -DLDOUBLE -DILONG $(CARGS) -o$(OUT)-ldouble
clean:
	@-rm -f $(OUT) core a.out *.o
	@-rm -f $(BINDIR)/*
	@-rmdir $(BINDIR)
	@-rm -f $(DATADIR)/*
	@-rmdir $(DATADIR)
