
# Compiler flags to enable all warnings & debug info
CFLAGS = -Wall -Werror -g -O0
#CFLAGS += -I$(NANOPB_DIR)
CFLAGS += -I.

# C source code files that are required
CSRC  = simple.c                   # The main program
CSRC += simple.pb.c                # The compiled protocol definition
CSRC += pb_encode.c  # The nanopb encoder
CSRC += pb_decode.c  # The nanopb decoder
CSRC += pb_common.c  # The nanopb common parts

# Build rule for the main program
simple: $(CSRC)
	$(CC) $(CFLAGS) -o simple $(CSRC)

