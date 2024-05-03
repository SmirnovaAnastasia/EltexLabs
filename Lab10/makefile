CC = gcc
BIN = main1 main2 main3
OBJ = task1.o task2.o task3.o
SRC = task1.c task2.c task3.c

.PHONY : clean 
all: main1 main2 main3

main1: task1.o
	$(CC) task1.o -o main1

main2: task2.o	
	$(CC) task2.o -o main2

main3: task3.o	
	$(CC) task3.o -o main3

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ) 
