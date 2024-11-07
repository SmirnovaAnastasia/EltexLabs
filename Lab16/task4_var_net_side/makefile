CC = gcc
BIN = mainser1 client1 client2 client3 multiclientTCP multiclientUDP
OBJ = mainser1.o client1.o client2.o client3.o multiclientTCP.o multiclientUDP.o
SRC = var1/mainser1.c var1/client1.c var2/client2.c var3/client3.c multiprot/multiclientTCP.c multiprot/multiclientUDP.c

.PHONY : clean
all: mainser1 client1 client2 mainser2 client3 mainser3 multiprotbin multiclientTCP multiclientUDP


### Var1 ###
mainser1: mainser1.o
	$(CC) mainser1.o -o mainser1

client1: client1.o
	$(CC) client1.o -o client1

### Var2 ###

mainser2: var2/mainser2.c var2/Function/queuefun.c var2/Function/serverfun.c
	$(CC) var2/mainser2.c var2/Function/queuefun.c var2/Function/serverfun.c -g -o mainser2

client2: client2.o
	$(CC) client2.o -o client2

### Var3 ###

mainser3: var3/mainser3.c var3/Function/queuefun.c var3/Function/serverfun.c
	$(CC) var3/mainser3.c  var3/Function/queuefun.c var3/Function/serverfun.c -g -o mainser3 -lpthread

client3: client3.o
	$(CC) client3.o -o client3

### MULTIPROT ###

multiprotbin: multiprot/multiprot.c
	$(CC) multiprot/multiprot.c -g -o multiprotbin

multiclientTCP: multiclientTCP.o
	$(CC) multiclientTCP.o -o multiclientTCP

multiclientUDP: multiclientUDP.o
	$(CC) multiclientUDP.o -o multiclientUDP

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ) mainser2 mainser3 multiprotbin
