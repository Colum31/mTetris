INC_DIR=inc/
CFLAGS=-c -Wall -g -I $(INC_DIR)

tetris: main.o tetris.o display.o timer.o tetrisRunner.o
	cc -lncurses -o tetris main.o tetris.o display.o timer.o tetrisRunner.o

debug: main.o tetris.o display.o tetrisRunner.o timer.o
	cc -lncurses -o tetris main.o tetris.o display.o timer.o tetrisRunner.o
	gdb tetris

main.o: main.c 
	cc $(CFLAGS) main.c


tetrisRunner.o: tetrisRunner.c
	cc $(CFLAGS) tetrisRunner.c

tetris.o: tetris.c
	cc $(CFLAGS) tetris.c

display.o: display.c
	cc $(CFLAGS) display.c

timer.o: timer.c
	cc $(CFLAGS) timer.c

clean:
	rm *.o
	rm tetris