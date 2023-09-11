tetris: main.o tetris.o display.o timer.o tetrisRunner.o
	cc -lncurses -o tetris main.o tetris.o display.o timer.o tetrisRunner.o

debug: main.o tetris.o display.o tetrisRunner.o timer.o
	cc -lncurses -o tetris main.o tetris.o display.o timer.o tetrisRunner.o
	gdb tetris

main.o: main.c 
	cc -c -Wall -g main.c


tetrisRunner.o: tetrisRunner.c
	cc -c -Wall -g tetrisRunner.c

tetris.o: tetris.c
	cc -c -Wall -g tetris.c

display.o: display.c
	cc -c -Wall -g display.c

timer.o: timer.c
	cc -c -Wall -g timer.c

clean:
	rm *.o
	rm tetris