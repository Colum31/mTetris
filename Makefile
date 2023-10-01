INC_DIRS=./display/include ./tetris/include ./timer/include ./snek/include .
SRC_DIRS= ./display/src ./tetris/src ./timer/src  ./snek/src .

CC=gcc
DEPFLAGS=-MP -MD
CFLAGS= -Wall -lncurses -g $(foreach D, $(INC_DIRS), -I$(D)) $(DEPFLAGS)

CFILES=$(foreach C, $(SRC_DIRS), $(wildcard $(C)/*.c))

OBJECTS=$(patsubst %.c, %.o, $(CFILES))
DEPFILES=$(patsubst %.c, %.d, $(CFILES))


tetrisOut: CFLAGS += -DTETRIS
tetrisOut: $(OBJECTS)
	$(CC) -lncurses -o $@ $^


snekOut: CFLAGS += -DSNEK
snekOut: $(OBJECTS)
	$(CC) -lncurses -o $@ $^

%.o:%.c 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJECTS) $(BIN)
	rm $(DEPFILES)

-include $(DEPFILES)