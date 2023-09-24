INC_DIR=inc/
CC=gcc
CFLAGS=-c -Wall -g -I $(INC_DIR)
BIN=tetris

$(BIN): main.o tetris.o display.o timer.o tetrisRunner.o
	$(CC) -lncurses  $^ -o $@

debug: main.o tetris.o display.o tetrisRunner.o timer.o
	$(CC) -lncurses  $^ -o tetris
	gdb tetris

%.o: %.c 
	$(CC) $(CFLAGS) $^

clean:
	rm *.o $(BIN)