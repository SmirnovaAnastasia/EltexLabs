CC = gcc
#CFLAGS = -c -Wall
BIN = main
OBJ = main.o 
SRC = main.c 
#OBJECTS = $(SOURCES:.c=.o)
#EXECUTABLE = main

.PHONY : clean

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) -lpthread

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ) 
