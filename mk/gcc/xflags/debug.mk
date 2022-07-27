# Extra debug flags for GCC
# These are additional debug flags omitted from the standard set as they are
# not supported in GCC 2.95 prevalent on many legacy systems.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CFLAGS += -Wextra -Wold-style-definition
