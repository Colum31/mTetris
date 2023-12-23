#include <string.h>
#include <stdlib.h>
#include "settings.h"

#include "snek.h"

void initSnek(uint8_t *curSnek){

    memset(curSnek, 0, BOARDSIZE * sizeof(uint8_t));

    for(int i = 0; i < SNEK_SPAWN_LEN; i++){

        int pos = SPAWN_Y * BOARD_X + SPAWN_X + i;
        curSnek[SNEK_SPAWN_LEN - 1 - i] = pos;
    }
}

int initFood(uint8_t *curSnek, int curSnekLen){
    
    int foodPos;
    int foundPos;

    while(1){
        foundPos = 1;
        int rng = rand();
        foodPos = rng % BOARDSIZE;

        for(int i = 0; i < curSnekLen; i++){
            if(curSnek[i] == foodPos){
                foundPos = 0;
                break;
            }
        }

        if(foundPos){
            return foodPos;
        }
    }
}

int getRow(int pos){
    return pos / BOARD_X;
}

int nextPosUp(int curPos){
    int simpleUp = curPos - BOARD_X;

    if(simpleUp >= 0){
        return simpleUp;
    }
    return BOARD_X * (BOARD_Y - 1) + curPos;
}

int nextPosDown(int curPos){
    int simpleDown = curPos + BOARD_X;

    if(simpleDown < BOARD_X *BOARD_Y){
        return simpleDown;
    }

    return curPos - (BOARD_X * (BOARD_Y - 1));
}

int nextPosRight(int curPos){
    int simpleRight = curPos + 1;

    if(getRow(curPos) == getRow(simpleRight)){
        return simpleRight;
    }

    return getRow(curPos) * BOARD_X;
}

int nextPosLeft(int curPos){
    int simpleLeft = curPos - 1;

    if(getRow(curPos) == getRow(simpleLeft) && simpleLeft >= 0){
        return simpleLeft;
    }

    return getRow(curPos) * BOARD_X + BOARD_X - 1;
}

int nextPos(int curPos, enum snekDirection dir){

    switch (dir)
    {
    case snekUp:
        return nextPosUp(curPos);
    case snekDown:
        return nextPosDown(curPos);
    case snekRight:
        return nextPosRight(curPos);
    case snekLeft:
        return nextPosLeft(curPos);
    default:
        return -1;
    }
}

enum snekDirection oppositeDirection(enum snekDirection dir){
    switch(dir){
        case snekDown:
            return snekUp;
        case snekUp:
            return snekDown;
        case snekLeft:
            return snekRight;
        case snekRight:
            return snekLeft;
        default:
            return snekUp;
    }
}

bool snekMove(uint8_t *curSnek, int *curSnekLen, enum snekDirection dir, int *foodPos){

    int curSnekHeadPos = curSnek[0];
    int nextSnekHeadPos = nextPos(curSnekHeadPos, dir);
    int snekTailPos = curSnek[*curSnekLen - 1];

    // Schlange kann nicht durch sich selbst durch
    if(nextSnekHeadPos == curSnek[1]){
        return true;
    }

    memmove(curSnek + 1, curSnek, (*curSnekLen - 1) * sizeof(uint8_t));
    curSnek[0] = nextSnekHeadPos;

    if(curSnek[0] == *foodPos){
        curSnek[*curSnekLen] = snekTailPos;
        *curSnekLen = *curSnekLen + 1;
        *foodPos = initFood(curSnek, *curSnekLen);
    }

    for(int i = 4; i < *curSnekLen; i++){
        if(curSnek[i] == nextSnekHeadPos){
            // Game Over, Schlange beisst sich selbst
            return false;
        }
    }

    return true;
}

void renderSnekBoard(uint8_t *board, uint8_t *snek, int snekLen, int foodPos){
    memset(board, 0, sizeof(uint8_t) * BOARDSIZE);

    for(int i = 0; i < snekLen; i++){
        int pos = snek[i];
        board[pos] = 1;
    }

    board[foodPos] = 1;
}
