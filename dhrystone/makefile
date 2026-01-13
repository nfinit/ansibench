# DEFAULT BENCHMARK CONFIGURATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc          = gcc
n           = 10000000
time        = TIME
hz          = 100

##############################################################################
# DO NOT MODIFY BEYOND THIS POINT                                            #
##############################################################################
-include ../mk/$(cc)/stdflags.mk
-include ../mk/$(cc)/opt/$(opt).mk
-include ../mk/$(cc)/xflags/$(xflags).mk
-include ../mk/$(cc)/dhrystone/stdflags.mk
# ----------------------------------------------------------------------------
BINDIR = ./bin
OUT    = $(BINDIR)/dhrystone
INPUT  = ./src/dhry_1.c ./src/dhry_2.c
# ----------------------------------------------------------------------------
CARGS  += $(OPTLEVEL) $(INPUT) $(CFLAGS) $(XCFLAGS)
# ----------------------------------------------------------------------------
LOGDIR = ./log
RUNLOG = "$(LOGDIR)/run-$(cc).txt"
# ----------------------------------------------------------------------------
all: bin 
run: all
	@date
	@echo "" >> $(RUNLOG)
	@echo -n ">>> " >> $(RUNLOG)
	@date >> $(RUNLOG)
	@echo "Running Dhrystone..." 
	@$(OUT) $(n) 2>&1 | tee -a $(RUNLOG)
	@$(OUT)-reg $(n) 2>&1 | tee -a $(RUNLOG)
dirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(LOGDIR)
bin: reg unreg
reg: dirs
	$(CC) $(CARGS) $(REGFLAG) -o$(OUT)-reg 
unreg: dirs
	$(CC) $(CARGS) -o$(OUT) 
clean:
	@-rm -f $(OUT) core a.out *.o
	@-rm -f $(BINDIR)/*
	@-rmdir $(BINDIR)
clean-log:
	@-rm -f $(LOGDIR)/*
	@-rmdir $(LOGDIR)
