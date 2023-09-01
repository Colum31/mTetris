tetris: main.o tetris.o
	cc -lncurses -o tetris main.o tetris.o

debug: main.o tetris.o
	cc -lncurses -o tetris main.o tetris.o 
	gdb tetris

main.o: main.c 
	cc -c -Wall -g main.c

tetris.o: tetris.c
	cc -c -Wall -g tetris.c

clean:
	rm tetris main.o tetris.o