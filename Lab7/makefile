CC = gcc
STLIB = ar rc
BIN = main
MAIN = main.c
FBIN = -L. -lcalc
OBJ = add.o div.o mul.o sub.o
SRC = Fun/add.c Fun/div.c Fun/mul.c Fun/sub.c
LIBS = libcalc.a

.PHONY : clean binary

binary: $(MAIN) $(LIBS)
	$(CC) $(MAIN) -o $(BIN) $(FBIN)

$(LIBS): $(OBJ)
	$(STLIB) $(LIBS) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(SRC) -c

clean:
	rm -rf $(BIN) $(OBJ) $(LIBS)
