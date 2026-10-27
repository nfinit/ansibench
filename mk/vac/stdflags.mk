# Standard flags for IBM VisualAge C 
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CC        = cc
OPTLEVEL  = -O2
CFLAGS   += -I ./include
ifeq "$(ANSIBENCH_DEBUG)" "1"
CFLAGS   += -g
endif
