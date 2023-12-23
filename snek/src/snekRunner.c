#include <string.h>

#include "snek.h"
#include "snekRunner.h"

uint8_t (*curRenderedSnekBoard)[BOARDSIZE];
uint8_t (*curSnek)[BOARDSIZE];

int snekLen;

int foodPos;
enum snekDirection curDir;
enum snekDirection nextDir;


int gameOverBlinkCnt;
int gameOverSnekPosCnt;

void initSnekGame(uint8_t (*boardPtr)[BOARDSIZE], uint8_t (*bufferPtr)[BOARDSIZE]){
    
    curRenderedSnekBoard = boardPtr;
    curSnek = bufferPtr;

    memset(*curRenderedSnekBoard, 0, BOARDSIZE * sizeof(uint8_t));
    memset(*curSnek, 0, BOARDSIZE * sizeof(uint8_t));

    initSnek(*curSnek);

    snekLen = SNEK_SPAWN_LEN;
    foodPos = initFood(*curSnek, snekLen);
    curDir = snekRight;
    nextDir = snekRight;

    gameOverBlinkCnt = 20;
    gameOverSnekPosCnt = 0;

    renderSnekBoard(*curRenderedSnekBoard, *curSnek, snekLen, foodPos);
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

    bool movePossible = snekMove(*curSnek, &snekLen, nextDir, &foodPos);
    curDir = nextDir;
    renderSnekBoard(*curRenderedSnekBoard, *curSnek, snekLen, foodPos);

    if(movePossible){
        return gameContinues;
    }

    return gameOver;
}

bool gameOverAnimationSnek(){

    // blink, where snek bit itself
    if(gameOverBlinkCnt){

        int snekHead = (*curSnek)[0];

        if(gameOverBlinkCnt % 2){
            (*curRenderedSnekBoard)[snekHead] = 0;
        }else{
            (*curRenderedSnekBoard)[snekHead] = 1;
        }

        gameOverBlinkCnt--;
        return false;
    }

    // degenerate snake
    if(gameOverSnekPosCnt <= snekLen){
        int curPos = (*curSnek)[gameOverSnekPosCnt];
        (*curRenderedSnekBoard)[curPos] = 0;
        gameOverSnekPosCnt++;
        return false;
    }

    // remove food
    if(foodPos != -1){
        (*curRenderedSnekBoard)[foodPos] = 0;
        foodPos = -1;
        return false;
    }

    return true;
}
