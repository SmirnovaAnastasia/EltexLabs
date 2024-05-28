CC = gcc
#CFLAGS = -c -Wall
BIN = main3 main2 main1 
OBJ = main3.o main2.o main1.o
SRC = main3.c main2.c main1.c 
#OBJECTS = $(SOURCES:.c=.o)
#EXECUTABLE = main

.PHONY : clean
all: main1 main2 main3

main1: main1.o
	$(CC) main1.o -o main1 -lpthread

main2: main2.o
	$(CC) main2.o -o main2 -lpthread

main3: main3.o
	$(CC) main3.o -o main3 -lpthread

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ) 
