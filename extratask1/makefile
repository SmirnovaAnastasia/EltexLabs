CC = gcc
BIN = server client 
OBJ = server.o client.o hashtab.o
SRC = server.c hashtab.c client.c

.PHONY : clean
all: server client

# ### Ethernet level ###

$(OBJ): $(SRC)
	$(CC) $(SRC) -c
	
server: server.o
	$(CC) server.o hashtab.o -o server

client: client.o
	$(CC) client.o -o client


clean:
	rm -rf $(BIN) $(OBJ) hashtab
