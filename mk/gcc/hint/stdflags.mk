# Standard flags for HINT on GCC
# - Define RUNTM variable
# - Include math library 
# - Supress warnings regarding type limits that are triggered with char data
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CFLAGS += -DRUNTM=$(runtime)
CFLAGS += -lm
CFLAGS += -Wno-type-limits
