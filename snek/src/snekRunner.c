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

bool handleUserSnek(char c){
    if(c < 91){
        c = c + 32;
    }

    enum snekDirection dir;

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
        default:
            return;
    }

    if(dir == lastSnekDir){
        return false;
    }

    return snekMove(curSnek, snekLen, dir);
}


bool handleSnekTick(){
    return snekMove(curSnek, snekLen, lastSnekDir);
}