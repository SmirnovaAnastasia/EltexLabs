CC = gcc
FL = -lncurses
BIN = main1 main2
OBJ = task1.o task2.o init.c create.o delete.o refresh.o open-close.o
SRC = task1.c task2.c Function/init.c Function/create.c Function/delete.c Function/refresh.c Function/open-close.c

.PHONY: clean
all: main1 main2

main1: task1.o
	$(CC) task1.o -o main1

main2: task2.o Function/init.o Function/create.o Function/delete.o Function/refresh.o Function/open-close.o
	$(CC) task2.o Function/init.o Function/create.o Function/delete.o Function/refresh.o Function/open-close.o -o main2 $(FL)

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ)