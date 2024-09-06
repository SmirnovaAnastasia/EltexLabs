CC = gcc
BIN = main1 main2
OBJ = main1.o main2.o
SRC = main1.c main2.c

.PHONY : clean
all: main1 main2 

main1: main1.o
	$(CC) main1.o -o main1

main2: main2.o
	$(CC) main2.o -o main2

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ)
