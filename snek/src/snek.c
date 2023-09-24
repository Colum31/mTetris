#include "snek.h"
#include <string.h>
#include "settings.h"

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

void renderSnekBoard(int *board, int *snek, int snekLen, int foodPos){
    memset(board, 0, sizeof(int) * BOARDSIZE);

    for(int i = 0; i < snekLen; i++){
        board[i] = 1;
    }

    board[foodPos] = 1;
}
