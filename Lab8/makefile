FSH = -shared
FBIN = -L. -ladd -ldiv -lmul -lsub
FDIN = -fPIC

CC = gcc
BIN = main
MAIN = main.c
OBJ = add.o div.o mul.o sub.o
SRC = Fun/add.c Fun/div.c Fun/mul.c Fun/sub.c
LIBS = libadd.so libdiv.so libmul.so libsub.so

.PHONY : clean binary

binary: $(MAIN) $(LIBS)
	$(CC) $(MAIN) -o $(BIN) $(FBIN)

libadd.so: add.o
	$(CC) $(FSH) add.o -o libadd.so

libdiv.so: div.o
	$(CC) $(FSH) div.o -o libdiv.so

libmul.so: mul.o
	$(CC) $(FSH) mul.o -o libmul.so

libsub.so: sub.o
	$(CC) $(FSH) sub.o -o libsub.so

$(OBJ): $(SRC)
	$(CC) $(SRC) $(FDIN) -c

clean:
	rm -rf $(BIN) $(OBJ) $(LIBS)
