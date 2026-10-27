# Standard flags for STREAM with VisualAge C
# - $(mp) is omitted, as its -fopenmp default is GCC-only
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CFLAGS += -lm
CFLAGS += -DSTREAM_ARRAY_SIZE=$(n)
