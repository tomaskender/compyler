CC=gcc
CFLAGS= -std=c99 -Wextra -Wall -pedantic -g

EXEC = compyler

.PHONY: all clean dir

BLD_DIR = ../build
EXEC = compyler
OBJS = compyler.o token.o

all: dir $(BLD_DIR)/$(EXEC)

clean:
	rm -f $(BLD_DIR)/*.o $(BLD_DIR)/$(EXEC)

dir:
	mkdir -p $(BLD_DIR)

#-----------------------------------------#

$(BLD_DIR)/$(EXEC): $(BLD_DIR)/$(OBJS)
	$(CC) $(OBJS) -o $(BLD_DIR)/$(EXEC)

$(BLD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
