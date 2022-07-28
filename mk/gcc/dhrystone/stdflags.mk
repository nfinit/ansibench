# Standard flags for Dhrystone with GCC
# - Set up timing parameters
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
REGFLAG = -DREG=register
CFLAGS += -D$(time) -DDHRY_HZ=$(hz)
