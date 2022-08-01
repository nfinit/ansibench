# DEFAULT BENCHMARK CONFIGURATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc          = gcc
n           = 20000
threads     = 1 
multithread = USE_PTHREAD -pthread
# multithread = USE_FORK
# multithread = DUMMY_NO_MULTITHREAD
pointer     = USE_UINTPTR
# pointer    = DUMMY_NO_PTR
memory      = "\"Heap\""

##############################################################################
# DO NOT MODIFY BEYOND THIS POINT                                            #
##############################################################################
-include ../mk/$(cc)/stdflags.mk
-include ../mk/$(cc)/opt/$(opt).mk
-include ../mk/$(cc)/xflags/$(xflags).mk
-include ../mk/$(cc)/coremark/stdflags.mk
# ----------------------------------------------------------------------------
BINDIR = ./bin
OUT    = $(BINDIR)/coremark
INPUT  = ./src/core_main.c ./src/core_matrix.c ./src/core_list_join.c
INPUT += ./src/core_state.c ./src/core_util.c ./src/core_portme.c
# ----------------------------------------------------------------------------
CARGS  += -DCOMPILER_FLAGS="\"$(OPTLEVEL)\"" -DMEM_LOCATION=$(memory)
CARGS  += -o$(OUT) $(OPTLEVEL) $(CFLAGS) $(XCFLAGS) $(INPUT)
# ----------------------------------------------------------------------------
all: bin 
run: all
	@date
	@echo "Running CoreMark..." 
	@$(OUT) 0x0 0x0 0x66 $(n) 7 1 2000
dirs:
	@mkdir -p $(BINDIR)
bin: dirs
	$(CC) $(CARGS) 
clean:
	@-rm -f $(OUT) core a.out *.o
	@-rm -f $(BINDIR)/*
	@-rmdir $(BINDIR)
