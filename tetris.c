#include <string.h> 
#include <stdlib.h>

#include "tetris.h"

#define NUM_SHAPES 7

const int square[]= {0,1,1,0,1,1,0,0,0};
const int t[] = {1,1,1,0,1,0,0,0,0};
const int z[] = {1,1,0,0,1,1,0,0,0};
const int s[] = {0,1,1,1,1,0,0,0,0};
const int j[] = {1,1,1,0,0,1,0,0,0};
const int l[] = {1,1,1,1,0,0,0,0,0};
const int i[] = {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0};

const int *figs[NUM_SHAPES] = {square, t, z, s, j, l, i};

void initBoard(int *boardToInit){
    memset(boardToInit, 0, sizeof(int) * BOARDSIZE);
}

int pieceLenByShape(enum shape pieceShape){
    if(pieceShape == IShape){
        return I_PIECE_LEN;
    }
    return DEFAULT_PIECE_LEN;   
}

int sideLenByShape(enum shape pieceShape){
        if(pieceShape == IShape){
        return I_PIECE_BOX_SIDE;
    }
    return DEFAULT_BOX_SIDE;   
}

enum shape getRandomPiece(int *dest){
    int shapeNum = rand() % NUM_SHAPES;
    enum shape shapeType = shapeNum;

    memcpy(dest, figs[shapeNum], pieceLenByShape(shapeType) * sizeof(int));

    return shapeType;
}

void updateBoard(int *board, int *playerPiece, int pieceX, int pieceY, enum shape pieceShape){
    int renderedBoard[BOARDSIZE];
    renderBoard(renderedBoard, board, playerPiece, pieceX, pieceY, pieceShape);
    memcpy(board, renderedBoard, sizeof(int) * BOARDSIZE);
}

bool checkSpawnPiece(int *pieceToSpawn, int *boardToSpawnIn, enum shape pieceShape){
    return checkMove(pieceToSpawn, SPAWN_X, SPAWN_Y, pieceShape, boardToSpawnIn);
}

void renderBoard(int *renderedBoard, int *boardToRender, int *pieceToRender, int piecePosX, int piecePosY, enum shape pieceShape){

    int sideLen = sideLenByShape(pieceShape);
    int pieceLen = pieceLenByShape(pieceShape);

    memcpy(renderedBoard, boardToRender, sizeof(int) * BOARDSIZE);

        for(int i = 0; i < pieceLen; i++){
        if(!pieceToRender[i]){
            continue;
        }

        int blockX = i % sideLen + piecePosX;
        int blockY = i / sideLen + piecePosY;
        int boardPos = blockY * BOARD_X + blockX;

        renderedBoard[boardPos] = 1;
    }
}

enum boardAction handleUserInput(enum userRequest r, int *board, int *playerPiece, int pieceX, int pieceY, enum shape pieceShape){
    
    int pieceLen = pieceLenByShape(pieceShape);
    int modifiedPiece[MAX_PIECE_LEN];

    memcpy(modifiedPiece, playerPiece, sizeof(int) * pieceLen);

    switch (r)
    {
    case requestRotateRight:
        rotateRight(modifiedPiece, pieceShape);
        if(checkMove(modifiedPiece, pieceX, pieceY, pieceShape, board)){
            memcpy(playerPiece, modifiedPiece, sizeof(int) * pieceLen);
        }
        return redraw;

    case requestRotateLeft:
        rotateLeft(modifiedPiece, pieceShape);
        if(checkMove(modifiedPiece, pieceX, pieceY, pieceShape, board)){
            memcpy(playerPiece, modifiedPiece, sizeof(int) * pieceLen);
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

    int sideLen = sideLenByShape(pieceShape);

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

    int tmpShapeCopy[MAX_PIECE_LEN];
    int pos = 0;
    int sideLen = sideLenByShape(curShape);

    memcpy(tmpShapeCopy, dest, sideLen * sideLen * sizeof(int));

    for(int x = 0; x < sideLen; x++){
    	for(int y = sideLen - 1; y >= 0; y--){
    		dest[pos] = tmpShapeCopy[sideLen * y + x];
            pos++;
    	}
    }
}

void rotateLeft(int *dest, enum shape curShape){

    int tmpShapeCopy[MAX_PIECE_LEN];
    int pos = 0;
    int sideLen = sideLenByShape(curShape);

    memcpy(tmpShapeCopy, dest, sideLen * sideLen * sizeof(int));

    for(int x = sideLen - 1; x >= 0; x--){
        for (int y = 0; y < sideLen; y++){
            dest[pos] = tmpShapeCopy[sideLen * y + x];
            pos++;
        }
    }
}

void clearRows(int *boardToClear, int pieceY){

    for(int y = pieceY; y < pieceY + MAX_BOX_SIDE + 1 && y < BOARD_Y; y++){

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
