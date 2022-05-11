CC=gcc
CFLAGS= -std=c99 -Wextra -Wall -pedantic -DDEBUG -g
EXEC = compyler

.PHONY: all clean dir

BLD_DIR = ../build
INC_DIR = include
EXEC = compyler
OBJS = $(BLD_DIR)/compyler.o $(BLD_DIR)/token_functions.o $(BLD_DIR)/context_functions.o
DEPS = $(INC_DIR)/cleanup.h $(INC_DIR)/context_functions.h $(INC_DIR)/context.h $(INC_DIR)/error.h $(INC_DIR)/token_functions.h $(INC_DIR)/token.h $(INC_DIR)/types.h

all: dir $(BLD_DIR)/$(EXEC)

clean:
	rm -f $(BLD_DIR)/*.o $(BLD_DIR)/$(EXEC)

dir:
	mkdir -p $(BLD_DIR)

#-----------------------------------------#

$(BLD_DIR)/$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(BLD_DIR)/$(EXEC)

$(BLD_DIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<
