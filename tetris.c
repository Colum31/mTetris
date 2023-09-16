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
const int i[] = {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0};

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

bool checkSpawnPiece(int *pieceToSpawn, int *boardToSpawnIn, enum shape pieceShape){
    return checkMove(pieceToSpawn, SPAWN_X, SPAWN_Y, pieceShape, boardToSpawnIn);
}

void renderBoard(int *renderedBoard, int *boardToRender, int *pieceToRender, int piecePosX, int piecePosY){

    memcpy(renderedBoard, boardToRender, sizeof(int) * BOARDSIZE);

    for(int i = 0; i < PIECE_LEN; i++){
        if(!pieceToRender[i]){
            continue;
        }

        int blockX = i % PIECE_BOX_SIDE + piecePosX;
        int blockY = i / PIECE_BOX_SIDE + piecePosY;
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
        rotateRight(modifiedPiece, pieceShape);
        if(checkMove(modifiedPiece, pieceX, pieceY, pieceShape, board)){
            memcpy(playerPiece, modifiedPiece, sizeof(int) * PIECE_LEN);
        }
        return redraw;

    case requestRotateLeft:
        rotateLeft(modifiedPiece, pieceShape);
        if(checkMove(modifiedPiece, pieceX, pieceY, pieceShape, board)){
            memcpy(playerPiece, modifiedPiece, sizeof(int) * PIECE_LEN);
        }
        return redraw;

    case requestRight:
        if(checkMove(modifiedPiece, pieceX + 1, pieceY, pieceShape, board)){
            return moveRight;
        }
        return none;
    case requestLeft:
        if(checkMove(modifiedPiece, pieceX - 1, pieceY, pieceShape, board)){
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

bool checkMove(int *piece, int piecePosX, int piecePosY, enum shape pieceShape, int *boardToCheck){

    int sideLen = 3;

    if(pieceShape == IShape){
        sideLen = 4;
    }


    for(int i = 0; i < sideLen * sideLen; i++){

        int blockX = i % sideLen + piecePosX;
        int blockY = i / sideLen + piecePosY;
        int boardPos = blockY * BOARD_X + blockX;

        if(!piece[i]){
            continue;
        }

        if(blockX < 0 || blockX > BOARD_X - 1){
            return false;
        }

        if(blockY < 0 || blockY > BOARD_Y - 1){
            return false;
        }

        if(boardToCheck[boardPos]){
            return false;
        }
    }
    
    return true;
}

void rotateRight(int *dest, enum shape curShape){

    int tmpShapeCopy[PIECE_LEN];
    int pos = 0;
    int sideLen = 3;

    if(curShape == SquareShape){
        return;
    } else if (curShape == IShape){
        sideLen = 4;
    }

    memcpy(tmpShapeCopy, dest, sideLen * sideLen * sizeof(int));

    for(int x = 0; x < sideLen; x++){
    	for(int y = sideLen - 1; y >= 0; y--){
    		dest[pos] = tmpShapeCopy[sideLen * y + x];
            pos++;
    	}
    }
}

void rotateLeft(int *dest, enum shape curShape){

    int tmpShapeCopy[PIECE_LEN];
    int pos = 0;
    int sideLen = 3;

    if(curShape == SquareShape){
        return;
    } else if(curShape == IShape){
        sideLen = 4;
    }

    memcpy(tmpShapeCopy, dest, sideLen * sideLen * sizeof(int));

    for(int x = sideLen - 1; x >= 0; x--){
        for (int y = 0; y < sideLen; y++){
            dest[pos] = tmpShapeCopy[sideLen * y + x];
            pos++;
        }
    }
}

void clearRows(int *boardToClear, int pieceY){

    for(int y = pieceY; y < pieceY + PIECE_BOX_SIDE + 1 && y < BOARD_Y; y++){

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
