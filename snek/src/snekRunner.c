#include <string.h>

#include "snek.h"
#include "snekRunner.h"

int curRenderedSnekBoard[BOARDSIZE];
int curSnek[BOARDSIZE];
int snekLen;

int foodPos;
enum snekDirection lastSnekDir;


void initSnekGame(){

    initSnek(curSnek);
    memset(curRenderedSnekBoard, 0, BOARDSIZE * sizeof(int));

    snekLen = SNEK_SPAWN_LEN;
    foodPos = initFood(curSnek, snekLen);
    lastSnekDir = snekRight;

    renderSnekBoard(curRenderedSnekBoard, curSnek, snekLen, foodPos);
}

enum gameSignal handleUserSnek(char c){
    if(c < 91){
        c = c + 32;
    }

    switch (c){
        case BINDING_UP:
            lastSnekDir = snekUp;
            return continueTimer;
        case BINDING_LEFT:
            lastSnekDir = snekLeft;
            return continueTimer;
        case BINDING_RIGHT:
            lastSnekDir = snekRight;
            return continueTimer;
        case BINDING_DOWN:
            lastSnekDir =snekDown;
            return continueTimer;
        default:
            return continueTimer;
    }
}

enum gameSignal handleSnekTick(){

    if(snekMove(curSnek, snekLen, lastSnekDir)){
        return gameContinues;
    }
    return gameOver;
}
