CC = gcc
#CFLAGS = -c -Wall
BIN = main
OBJ = main.o add.o print.o remove.o search.o
SRC = main.c Function/add.c Function/print.c Function/remove.c Function/search.c
#OBJECTS = $(SOURCES:.c=.o)
#EXECUTABLE = main

.PHONY : clean

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ) 
