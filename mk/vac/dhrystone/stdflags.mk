# Standard flags for Dhrystone with VisualAge C
# - Set up timing parameters
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
REGFLAG = -DREG=register
CFLAGS += -D$(time) -DDHRY_HZ=$(hz)
