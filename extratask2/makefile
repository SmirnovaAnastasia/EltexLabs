CC = gcc
BIN = main
OBJ = main.o taxifun.o fun.o
SRC = main.c taxifun.c fun.c

.PHONY : clean
all: main


main: main.o taxifun.o
	$(CC) main.o taxifun.o fun.c -o main

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ) 