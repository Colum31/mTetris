#include "inc/tetris.h"
#include "inc/tetrisRunner.h"

int curBoard[BOARDSIZE];
int curPiece[PIECE_LEN];
int curPieceX = SPAWN_X;
int curPieceY = SPAWN_Y;

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
    enum boardAction ret = handleUserInput(c, curBoard, curPiece, curPieceX, curPieceY);

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

