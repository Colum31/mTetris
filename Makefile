tetris: main.o tetris.o display.o
	cc -lncurses -o tetris main.o tetris.o display.o

debug: main.o tetris.o
	cc -lncurses -o tetris main.o tetris.o 
	gdb tetris

main.o: main.c 
	cc -c -Wall -g main.c

tetris.o: tetris.c
	cc -c -Wall -g tetris.c

display.o: display.c
	cc -c -Wall -g display.c

clean:
	rm tetris main.o tetris.o