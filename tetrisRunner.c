#include <string.h>

#include "tetris.h"
#include "tetrisRunner.h"

int curBoard[BOARDSIZE];
int curPiece[PIECE_LEN];
int curPieceX = SPAWN_X;
int curPieceY = SPAWN_Y;

int gameOverRow = 0;

int curRenderedBoard[BOARDSIZE];


void initNewPiece(){
    getRandomPiece(curPiece);
    curPieceY = SPAWN_Y;
    curPieceX = SPAWN_X;
}

void initGame(){
    initBoard(curBoard);
    initBoard(curRenderedBoard);
    initNewPiece();
}

void displayPlayerPiece(){
    renderBoard(curRenderedBoard, curBoard, curPiece, curPieceX, curPieceY);
}

bool handleTick(){

    if(checkMove(curPiece, curPieceX, curPieceY + 1, curBoard)){
        curPieceY++;
        displayPlayerPiece();
        return true;
    }

    updateBoard(curBoard, curPiece, curPieceX, curPieceY);
    clearRows(curBoard, curPieceY);


    if(!checkSpawnPiece(curPiece, curBoard)){
        displayPlayerPiece();
        return false;
    }

    initNewPiece();
    displayPlayerPiece();
    return true;
}


enum gameEvent handleUserEvent(char c){

    if(c < 91){
        c = c + 32;
    }

    enum userRequest req;

    switch (c){
        case BINDING_DROP:
            req = requestDrop;
            break;
        case BINDING_LEFT:
            req = requestLeft;
            break;
        case BINDING_RIGHT:
            req = requestRight;
            break;
        case BINDING_ROATATE_LEFT:
            req = requestRotateLeft;
            break;
        case BINDING_ROTATE_RIGHT:
            req = requestRotateRight;
            break;
        default:
            return continueRound;
    }

    enum boardAction ret = handleUserInput(req, curBoard, curPiece, curPieceX, curPieceY);

    switch(ret){

        case moveRight:
            curPieceX++;
             displayPlayerPiece();
            return continueRound;
        case moveLeft:
            curPieceX--;
             displayPlayerPiece();
            return continueRound;
        case dropOne:
            displayPlayerPiece();
            return skipRound;
        default:
            displayPlayerPiece();
            return continueRound;
    }  

}

bool gameOverAnimation(){

    if(gameOverRow == BOARD_Y){
        gameOverRow = 0;
        return true;
    }

    memset(&curRenderedBoard[BOARD_X * (15 - gameOverRow)], 0, BOARD_X * sizeof(int));
    gameOverRow++;
    return false;

}
