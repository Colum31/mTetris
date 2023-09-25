#include <string.h>
#include "settings.h"

#include "snek.h"

void initSnek(int *curSnek){

    memset(curSnek, 0, BOARDSIZE * sizeof(int));

    for(int i = 0; i < SNEK_SPAWN_LEN; i++){

        int pos = SPAWN_Y * BOARD_X + SPAWN_X + i;
        curSnek[pos] = 1;
    }
}

int initFood(int *curSnek, int curSnekLen){
    
    int foodPos;

    while(1){
        foodPos = rand() % BOARDSIZE;

        for(int i = 0; i < curSnekLen; i++){
            if(curSnek[i] == foodPos){
                continue;
            }
        }
        break;

    }
    return foodPos;
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
    int simpleRight = curPos++;

    if(getRow(curPos) == getRow(simpleRight)){
        return simpleRight;
    }

    return getRow(curPos) * BOARD_X;
}

int nextPosLeft(int curPos){
    int simpleLeft = curPos--;

    if(getRow(curPos) == getRow(simpleLeft)){
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

bool snekMove(int *curSnek, int curSnekLen, enum snekDirection dir){

    int curSnekHeadPos = curSnek[0];
    int nextSnekHeadPos = nextPos(curSnekHeadPos, dir);

    // Schlange kann nicht durch sich selbst durch
    if(nextSnekHeadPos == curSnek[1]){
        return true;
    }

    memmove(++curSnek, curSnek, --curSnekLen);
    curSnek[0] = nextSnekHeadPos;

    for(int i = 4; i < curSnekLen; i++){
        if(curSnek[i] == curSnek[0]){
            // Game Over, Schlange beisst sich selbst
            return false;
        }
    }

    return true;
   
}

void renderSnekBoard(int *board, int *snek, int snekLen, int foodPos){
    memset(board, 0, sizeof(int) * BOARDSIZE);

    for(int i = 0; i < snekLen; i++){
        board[i] = 1;
    }

    board[foodPos] = 1;
}
