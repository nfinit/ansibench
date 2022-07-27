# DEFAULT BENCHMARK CONFIGURATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc          = gcc
n           = 20000
threads     = 1 
multithread = USE_PTHREAD -pthread
# multithread = USE_FORK -D_POSIX_C_SOURCE=199309L
memory      = "\"Heap\""
pointer     = uintptr_t

##############################################################################
# DO NOT MODIFY BEYOND THIS POINT                                            #
##############################################################################
-include ../mk/$(cc)/stdflags.mk
-include ../mk/$(cc)/opt/$(opt).mk
-include ../mk/$(cc)/xflags/$(xflags).mk
-include ../mk/$(cc)/coremark/stdflags.mk
-include ../mk/$(cc)/coremark/$(platform).mk
# ----------------------------------------------------------------------------
BINDIR = ./bin
OUT    = $(BINDIR)/coremark
INPUT  = ./src/core_main.c ./src/core_matrix.c ./src/core_list_join.c
INPUT += ./src/core_state.c ./src/core_util.c ./src/core_portme.c
# ----------------------------------------------------------------------------
CARGS  += -DCOMPILER_FLAGS="\"$(OPTLEVEL)\"" -DMEM_LOCATION=$(memory)
CARGS  += -o$(OUT) $(OPTLEVEL) $(CFLAGS) $(XCFLAGS) $(INPUT)
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
	@echo "Running CoreMark..." 
	@$(OUT) 0x0 0x0 0x66 $(n) 7 1 2000 2>&1 | tee -a $(RUNLOG)
dirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(LOGDIR)
bin: dirs
	$(CC) $(CARGS) 
clean:
	@-rm -f $(OUT) core a.out *.o
	@-rm -f $(BINDIR)/*
	@-rmdir $(BINDIR)
clean-log:
	@-rm -f $(LOGDIR)/*
	@-rmdir $(LOGDIR)
