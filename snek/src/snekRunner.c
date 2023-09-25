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