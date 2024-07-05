CC = gcc
POSFL = -lrt
NCURSFL = -lncurses
PTHFL = -lpthread
BIN = client1 server1 client2 server2 client3 server3 server_chat client_chat #main3 main2  
OBJ = client1.o server1.o
SRC = client1.c server1.c 
#OBJECTS = $(SOURCES:.c=.o)
#EXECUTABLE = main

.PHONY : clean
all: server1 client1 server2 client2 server_chat client_chat

client_chat: client3.c Function/init1.c Function/init2.c Function/create1.c Function/create2.c Function/delete.c Function/refresh1.c Function/refresh2.c
	$(CC) client3.c Function/init1.c Function/init2.c Function/create1.c Function/create2.c Function/delete.c Function/refresh1.c Function/refresh2.c -o client_chat $(NCURSFL) $(PTHFL)

server_chat: server3.c
	$(CC) server3.c -o server_chat $(PTHFL)

client2: client2.c
	$(CC) -o client2 client2.c ${POSFL}

server2: server2.c
	$(CC) -o server2 server2.c ${POSFL}

client1: client1.o
	$(CC) client1.o -o client1

server1: server1.o
	$(CC) server1.o -o server1

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ) 
