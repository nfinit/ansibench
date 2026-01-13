# DEFAULT BENCHMARK CONFIGURATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc          = gcc

##############################################################################
# DO NOT MODIFY BEYOND THIS POINT                                            #
##############################################################################
-include ../mk/$(cc)/stdflags.mk
-include ../mk/$(cc)/opt/$(opt).mk
-include ../mk/$(cc)/xflags/$(xflags).mk
-include ../mk/$(cc)/nbench/stdflags.mk
# ----------------------------------------------------------------------------
BINDIR = ./bin
OUT    = $(BINDIR)/nbench
INPUT  = ./src/nbench0.c ./src/nbench1.c
INPUT += ./src/hardware.c ./src/emfloat.c ./src/sysspec.c ./src/misc.c
# ----------------------------------------------------------------------------
CARGS  += -o$(OUT) $(OPTLEVEL) $(INPUT) $(CFLAGS) $(XCFLAGS)
# ----------------------------------------------------------------------------
all: bin 
run: all
	@date
	@echo "Running NBench..." 
	@$(OUT) 2>&1
dirs:
	@mkdir -p $(BINDIR)
bin: dirs
	$(CC) $(CARGS) 
clean:
	@-rm -f $(OUT) core a.out *.o
	@-rm -f $(BINDIR)/*
	@-rmdir $(BINDIR)
