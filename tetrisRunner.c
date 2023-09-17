#include <string.h>

#include "tetris.h"
#include "tetrisRunner.h"

struct pieceInfo piece;

int curBoard[BOARDSIZE];
int curRenderedBoard[BOARDSIZE];

int gameOverRow = 0;

void initGame(){
    initBoard(curBoard);
    initBoard(curRenderedBoard);
    initRandomPiece(&piece);
    
    renderBoard(curRenderedBoard, curBoard, &piece);
}

void displayPlayerPiece(){
    renderBoard(curRenderedBoard, curBoard, &piece);
}

bool handleTick(){

    if(checkMove(piece.piece, piece.pieceX, piece.pieceY + 1, piece.pieceShape, curBoard)){
        piece.pieceY++;
        displayPlayerPiece();
        return true;
    }

    updateBoard(curBoard, &piece);
    clearRows(curBoard, piece.pieceY);

    initRandomPiece(&piece);

    if(!checkSpawnPiece(piece.piece, curBoard, piece.pieceShape)){
        displayPlayerPiece();
        return false;
    }

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

    enum boardAction ret = handleUserInput(req, curBoard, &piece);

    switch(ret){

        case moveRight:
            piece.pieceX++;
            displayPlayerPiece();
            return continueRound;
        case moveLeft:
            piece.pieceX--;
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

    memset(&curRenderedBoard[BOARD_X * (BOARD_Y - gameOverRow - 1)], 0, BOARD_X * sizeof(int));
    gameOverRow++;
    return false;
}
