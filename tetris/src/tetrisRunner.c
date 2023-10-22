#include <string.h>

#include "tetris.h"
#include "tetrisRunner.h"

struct pieceInfo piece;

int curTetrisBoard[BOARDSIZE];
int (*curRenderedTetrisBoard)[BOARDSIZE];

int gameOverRow = 0;

void initTetrisGame(int (*boardPtr)[BOARDSIZE]){
    initBoard(curTetrisBoard);

    curRenderedTetrisBoard = boardPtr;
    initRandomPiece(&piece);
    renderBoard(*curRenderedTetrisBoard, curTetrisBoard, &piece);
}

void displayPlayerPiece(){
    renderBoard(*curRenderedTetrisBoard, curTetrisBoard, &piece);
}

enum gameSignal handleTetrisTick(){

    if(checkMove(piece.piece, piece.pieceX, piece.pieceY + 1, piece.pieceShape, curTetrisBoard)){
        piece.pieceY++;
        displayPlayerPiece();
        return gameContinues;
    }

    updateBoard(curTetrisBoard, &piece);
    clearRows(curTetrisBoard, piece.pieceY);

    initRandomPiece(&piece);

    if(!checkSpawnPiece(piece.piece, curTetrisBoard, piece.pieceShape)){
        displayPlayerPiece();
        return gameOver;
    }

    displayPlayerPiece();
    return gameContinues;
}


enum gameSignal handleTetrisUserEvent(char c){

    if(c < 91){
        c = c + 32;
    }

    enum userRequest req;

    switch (c){
        case BINDING_DOWN:
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
            return continueTimer;
    }

    enum boardAction ret = handleUserInput(req, curTetrisBoard, &piece);

    switch(ret){

        case moveRight:
            piece.pieceX++;
            displayPlayerPiece();
            return continueTimer;
        case moveLeft:
            piece.pieceX--;
            displayPlayerPiece();
            return continueTimer;
        case dropOne:
            displayPlayerPiece();
            return skipTimer;
        default:
            displayPlayerPiece();
            return continueTimer;
    }  

}

bool gameOverTetrisAnimation(){

    if(gameOverRow == BOARD_Y){
        gameOverRow = 0;
        return true;
    }

    memset( &(*curRenderedTetrisBoard)[BOARD_X * (BOARD_Y - gameOverRow - 1)], 0, BOARD_X * sizeof(int));
    gameOverRow++;
    return false;
}
