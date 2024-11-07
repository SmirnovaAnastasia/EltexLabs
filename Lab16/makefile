CC = gcc
BIN = locTCPser locTCPcli locUDPser locUDPcli netTCPser netTCPcli netUDPser netUDPcli broadCli broadSer mulCli mulSer 
OBJ = locTCPser.o locTCPcli.o locUDPser.o locUDPcli.o netTCPser.o netTCPcli.o netUDPser.o netUDPcli.o broadCli.o broadSer.o mulCli.o mulSer.o 
SRC = task1_local/locTCPser.c task1_local/locTCPcli.c task1_local/locUDPser.c task1_local/locUDPcli.c task2_net/netTCPser.c task2_net/netTCPcli.c task2_net/netUDPser.c task2_net/netUDPcli.c task3_data_tran/broadCli.c task3_data_tran/broadSer.c task3_data_tran/mulCli.c task3_data_tran/mulSer.c 

.PHONY : clean
all: locTCPser locTCPcli locUDPser locUDPcli netTCPser netTCPcli netUDPser netUDPcli broadCli broadSer mulCli mulSer

###LOCAL###

locTCPcli: locTCPcli.o
	$(CC) locTCPcli.o -o locTCPcli

locTCPser: locTCPser.o
	$(CC) locTCPser.o -o locTCPser

locUDPcli: locUDPcli.o
	$(CC) locUDPcli.o -o locUDPcli

locUDPser: locUDPser.o
	$(CC) locUDPser.o -o locUDPser


###NET###

netTCPcli: netTCPcli.o
	$(CC) netTCPcli.o -o netTCPcli

netTCPser: netTCPser.o
	$(CC) netTCPser.o -o netTCPser

netUDPcli: netUDPcli.o
	$(CC) netUDPcli.o -o netUDPcli

netUDPser: netUDPser.o
	$(CC) netUDPser.o -o netUDPser


###DATA TRAN###

broadCli: broadCli.o
	$(CC) broadCli.o -o broadCli

broadSer: broadSer.o
	$(CC) broadSer.o -o broadSer

mulCli: mulCli.o
	$(CC) mulCli.o -o mulCli

mulSer: mulSer.o
	$(CC) mulSer.o -o mulSer

###VAR_NET_SIDE###

mainser1: mainser1.o
	$(CC) mainser1.o -o mainser1

client1: client1.o
	$(CC) client1.o -o client1


$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ)
