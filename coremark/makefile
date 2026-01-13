# DEFAULT BENCHMARK CONFIGURATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc          = gcc
n           = 20000
threads     = 1 
multithread = USE_FORK
# multithread = USE_PTHREAD -pthread
# multithread = DUMMY_NO_MULTITHREAD # if neither fork nor pthread is supported
pointer     = UINTPTR_TYPE
# pointer    = DUMMY_NO_PTR # to just use the default
memory      = "\"Main memory (heap)\""
# XCFLAGS += -lrt # for older versions of libc
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
CARGS  += -o $(OUT) $(OPTLEVEL) $(INPUT) $(CFLAGS) $(XCFLAGS)
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
