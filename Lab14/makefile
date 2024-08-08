CC = gcc
POSFL = -lrt
NCURSFL = -lncurses
BIN = client1 server1 client2 server2 server_chat client_chat
OBJ = client1.o server1.o
SRC = client1.c server1.c 

.PHONY : clean touch
all: server1 client1 server2 client2 server_chat client_chat

client_chat: client3.c Function/init1.c Function/init2.c Function/create1.c Function/create2.c Function/delete.c Function/refresh1.c Function/refresh2.c
	$(CC) client_new.c Function/init1.c Function/init2.c Function/create1.c Function/create2.c Function/delete.c Function/refresh1.c Function/refresh2.c -o client_chat $(NCURSFL) $(PTHFL)

server_chat: server3.c
	$(CC) server_new.c -o server_chat $(PTHFL)

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

touch:
	touch mshmem.txt
	touch msemmem.txt

	touch mshmem2.txt
	touch msemmem2.txt

	touch mshmem3.txt
	touch msemmem3.txt

delete:
	rm mshmem.txt
	rm msemmem.txt

	rm mshmem2.txt
	rm msemmem2.txt

	rm mshmem3.txt
	rm msemmem3.txt

clean:
	rm -rf $(BIN) $(OBJ)
