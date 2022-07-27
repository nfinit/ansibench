# Standard flags for CoreMark on GCC
# - Set PERFORMANCE_RUN flag and base iterations
# - Configure multithreading
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CFLAGS += -DPERFORMANCE_RUN=1 -DITERATIONS=$(n)
CFLAGS += -DMULTITHREAD=$(threads) -D$(multithread) 
