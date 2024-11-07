CC = gcc
BIN = server1 client1 server2 client2 server3 client3 
OBJ = server1.o client1.o server2.o client2.o server3.o client3.o
SRC = 1tran/server1.c 1tran/client1.c 2ip/server2.c 2ip/client2.c 3ethernet/server3.c 3ethernet/client3.c 3ethernet/clifun.c

.PHONY : clean
all: server1 client1 server2 client2 server3 client3


### Transport level ###
server1: server1.o
	$(CC) server1.o -g -o server1

client1: client1.o
	$(CC) client1.o -o client1

# ### Ip level ###
server2: server2.o
	$(CC) server2.o -o server2

client2: client2.o
	$(CC) client2.o -o client2

# ### Ethernet level ###
server3: server3.o
	$(CC) server3.o  -o server3

client3: client3.o
	$(CC) client3.o clifun.o -o client3

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ) clifun
