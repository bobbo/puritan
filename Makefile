.DEFAULT_GOAL = cmd

CC = clang
CFLAGS = -Wall -fpic

LIB_DIR = src/lib
LIB_SRCS = $(wildcard $(LIB_DIR)/*.c)
LIB_OBJS = $(LIB_SRCS:.c=.o)
LIB_INCLUDES = $(LIB_DIR)/include
LIB_FILE = $(LIB_DIR)/libpuritan.so

CMD_DIR = src/cmd
CMD_SRCS = $(wildcard $(CMD_DIR)/*.c)
CMD_OBJS = $(CMD_SRCS:.c=.o)
CMD_FILE = puritanvm

.c.o:
	$(CC) $(CFLAGS) -I $(LIB_INCLUDES) -c $< -o $@

lib: $(LIB_OBJS)
	$(CC) $(CFLAGS) -shared -o $(LIB_FILE) $(LIB_OBJS)

cmd: $(CMD_OBJS) lib
	$(CC) $(CFLAGS) -I $(LIB_INCLUDES) $(CMD_OBJS) $(LIB_FILE) -o $(CMD_FILE)


.PHONY: clean
clean:
	rm -f $(LIB_OBJS) $(CMD_OBJS) $(LIB_FILE) $(CMD_FILE)
