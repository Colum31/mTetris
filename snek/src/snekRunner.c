#include <string.h>

#include "snek.h"
#include "snekRunner.h"

int (*curRenderedSnekBoard)[BOARDSIZE];
int curSnek[BOARDSIZE];
int snekLen;

int foodPos;
enum snekDirection curDir;
enum snekDirection nextDir;


void initSnekGame(int (*boardPtr)[BOARDSIZE]){

    initSnek(curSnek);
    curRenderedSnekBoard = boardPtr;
    memset(*curRenderedSnekBoard, 0, BOARDSIZE * sizeof(int));

    snekLen = SNEK_SPAWN_LEN;
    foodPos = initFood(curSnek, snekLen);
    curDir = snekRight;
    nextDir = snekRight;

    renderSnekBoard(*curRenderedSnekBoard, curSnek, snekLen, foodPos);
}

enum gameSignal handleUserSnek(char c){
    if(c < 91){
        c = c + 32;
    }

    enum snekDirection dir = curDir;

    switch (c){
        case BINDING_UP:
            dir = snekUp;
            break;
        case BINDING_LEFT:
            dir = snekLeft;
            break;
        case BINDING_RIGHT:
            dir = snekRight;
            break;
        case BINDING_DOWN:
            dir = snekDown;
            break;
    }

    if(dir != oppositeDirection(curDir)){
        nextDir = dir;
    }

    return continueTimer;
}

enum gameSignal handleSnekTick(){

    bool movePossible = snekMove(curSnek, &snekLen, nextDir, &foodPos);
    curDir = nextDir;
    renderSnekBoard(*curRenderedSnekBoard, curSnek, snekLen, foodPos);

    if(movePossible){
        return gameContinues;
    }

    return gameOver;
}

bool gameOverAnimationSnek(){
    return true;
}
