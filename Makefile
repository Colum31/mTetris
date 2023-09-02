tetris: main.o tetris.o display.o timer.o
	cc -lncurses -o tetris main.o tetris.o display.o timer.o

debug: main.o tetris.o display.o
	cc -lncurses -o tetris main.o tetris.o display.o timer.o
	gdb tetris

main.o: main.c 
	cc -c -Wall -g main.c

tetris.o: tetris.c
	cc -c -Wall -g tetris.c

display.o: display.c
	cc -c -Wall -g display.c

timer.o: timer.c
	cc -c -Wall -g timer.c

clean:
	rm *.o
	rm tetris