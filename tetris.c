#include <string.h> 
#include <stdlib.h>

#include "tetris.h"

#define NUM_SHAPES 6

const int square[]= {0,1,1,0,1,1,0,0,0};
const int t[] = {1,1,1,0,1,0,0,0,0};
const int z[] = {1,1,0,0,1,1,0,0,0};
const int s[] = {0,1,1,1,1,0,0,0,0};
const int j[] = {1,1,1,0,0,1,0,0,0};
const int l[] = {1,1,1,1,0,0,0,0,0};

const int *figs[NUM_SHAPES] = {square, t, z, s, j, l};

void initBoard(int *boardToInit){
    memset(boardToInit, 0, sizeof(int) * BOARDSIZE);
}

enum shape getRandomPiece(int *dest){
    int r = rand() % NUM_SHAPES;
    memcpy(dest, figs[r], PIECE_LEN * sizeof(int));

    return (enum shape) r;
}

void updateBoard(int *board, int *playerPiece, int pieceX, int pieceY){
    int renderedBoard[BOARDSIZE];
    renderBoard(renderedBoard, board, playerPiece, pieceX, pieceY);
    memcpy(board, renderedBoard, sizeof(int) * BOARDSIZE);
}

bool checkSpawnPiece(int *pieceToSpawn, int *boardToSpawnIn){
    return checkMove(pieceToSpawn, SPAWN_X, SPAWN_Y, boardToSpawnIn);
}

void renderBoard(int *renderedBoard, int *boardToRender, int *pieceToRender, int piecePosX, int piecePosY){

    memcpy(renderedBoard, boardToRender, sizeof(int) * BOARDSIZE);

    for(int i = 0; i < PIECE_LEN; i++){
        if(!pieceToRender[i]){
            continue;
        }

        int blockX = i % 3 + piecePosX;
        int blockY = i / 3 + piecePosY;
        int boardPos = blockY * BOARD_X + blockX;

        renderedBoard[boardPos] = 1;
    }
}

enum boardAction handleUserInput(enum userRequest r, int *board, int *playerPiece, int pieceX, int pieceY, enum shape pieceShape){
    
    int modifiedPiece[PIECE_LEN];
    memcpy(modifiedPiece, playerPiece, sizeof(int) * PIECE_LEN);

    switch (r)
    {
    case requestRotateRight:
        rotateRight(modifiedPiece, sizeof(int) * PIECE_LEN, pieceShape);
        if(checkMove(modifiedPiece, pieceX, pieceY, board)){
            memcpy(playerPiece, modifiedPiece, sizeof(int) * PIECE_LEN);
        }
        return redraw;

    case requestRotateLeft:
        rotateLeft(modifiedPiece, sizeof(int) * PIECE_LEN, pieceShape);
        if(checkMove(modifiedPiece, pieceX, pieceY, board)){
            memcpy(playerPiece, modifiedPiece, sizeof(int) * PIECE_LEN);
        }
        return redraw;

    case requestRight:
        if(checkMove(modifiedPiece, pieceX + 1, pieceY, board)){
            return moveRight;
        }
        return none;
    case requestLeft:
        if(checkMove(modifiedPiece, pieceX - 1, pieceY, board)){
            return moveLeft;
        }
        return none;

    case requestDrop:
        return dropOne;

    default:
        break;
    }

    return none;
}

bool checkMove(int *piece, int piecePosX, int piecePosY, int *boardToCheck){

    for(int i = 0; i < PIECE_LEN; i++){

        if(!piece[i]){
            continue;
        }
        
        int blockX = i % 3 + piecePosX;
        int blockY = i / 3 + piecePosY;

        if(blockX < 0 || blockX > BOARD_X - 1){
            return false;
        }

        if(blockY < 0 || blockY > BOARD_Y - 1){
            return false;
        }

        int boardPos = blockY * BOARD_X + blockX;

        if(boardToCheck[boardPos]){
            return false;
        }
    }
    
    return true;
}

void rotateRight(int *dest, int len, enum shape curShape){

    int tmpShapeCopy[9];

    if(curShape == SquareShape){
        return;
    }

    memcpy(tmpShapeCopy, dest, len);

    dest[2] = tmpShapeCopy[0];
    dest[8] = tmpShapeCopy[2];
    dest[6] = tmpShapeCopy[8];
    dest[0] = tmpShapeCopy[6];

    dest[1] = tmpShapeCopy[3];
    dest[5] = tmpShapeCopy[1];
    dest[7] = tmpShapeCopy[5];
    dest[3] = tmpShapeCopy[7];          
}

void rotateLeft(int *dest, int len, enum shape curShape){

    int tmpShapeCopy[9];

    if(curShape == SquareShape){
        return;
    }

    memcpy(tmpShapeCopy, dest, len);

    dest[0] = tmpShapeCopy[2];
    dest[2] = tmpShapeCopy[8];
    dest[8] = tmpShapeCopy[6];
    dest[6] = tmpShapeCopy[0];

    dest[7] = tmpShapeCopy[3];
    dest[3] = tmpShapeCopy[1];
    dest[1] = tmpShapeCopy[5];
    dest[5] = tmpShapeCopy[7];          
}

void clearRows(int *boardToClear, int pieceY){

    for(int y = pieceY; y < pieceY + 4 && y < BOARD_Y; y++){

        int rowSet = 1;
        
        for(int boardPos = y * BOARD_X; boardPos < y * BOARD_X + BOARD_X; boardPos++){
            if(!boardToClear[boardPos]){
                rowSet = 0;
                break;
            }
        }

        if(!rowSet){
            continue;
        }
        memset(&boardToClear[y * BOARD_X], 0, BOARD_X * sizeof(int));

        int toMove = y * BOARD_X;

        memmove(&boardToClear[BOARD_X], boardToClear, toMove * sizeof(int));
    }

}
