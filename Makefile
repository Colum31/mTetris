INC_DIRS=./display/include ./tetris/include ./timer/include ./snek/include ./gameWrapper/include .
SRC_DIRS= ./display/src ./tetris/src ./timer/src  ./snek/src ./gameWrapper/src .

CC=gcc
DEPFLAGS=-MP -MD
CFLAGS= -Wall -lncurses -ggdb3 $(foreach D, $(INC_DIRS), -I$(D)) $(DEPFLAGS)

CFILES=$(foreach C, $(SRC_DIRS), $(wildcard $(C)/*.c))

OBJECTS=$(patsubst %.c, %.o, $(CFILES))
DEPFILES=$(patsubst %.c, %.d, $(CFILES))

BIN=games

all:$(OBJECTS)
	$(CC) -lncurses -o $(BIN) $^

%.o:%.c 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJECTS) $(BIN)
	rm $(DEPFILES)

-include $(DEPFILES)