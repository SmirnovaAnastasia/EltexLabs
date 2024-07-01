CC = gcc
BIN = main1 client2 server2 main3
OBJ = main1.o client2.o server2.o main3.o
SRC = main1.c client2.c server2.c main3.c


.PHONY : clean
all: main1 client2 server2 main3

main1: main1.o
	$(CC) main1.o -o main1

client2: client2.o
	$(CC) client2.o -o client2

server2: server2.o
	$(CC) server2.o -o server2

main3: main3.o
	$(CC) main3.o -o main3

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ) 
