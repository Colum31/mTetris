#include <string.h> 
#include <stdlib.h>

#include "tetris.h"

#define NUM_SHAPES 7

const uint8_t square[]= {0,1,1,0,1,1,0,0,0};
const uint8_t t[] = {1,1,1,0,1,0,0,0,0};
const uint8_t z[] = {1,1,0,0,1,1,0,0,0};
const uint8_t s[] = {0,1,1,1,1,0,0,0,0};
const uint8_t j[] = {1,1,1,0,0,1,0,0,0};
const uint8_t l[] = {1,1,1,1,0,0,0,0,0};
const uint8_t i[] = {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0};

const uint8_t *figs[NUM_SHAPES] = {square, t, z, s, j, l, i};

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


void initBoard(int *boardToInit){
    memset(boardToInit, 0, sizeof(int) * BOARDSIZE);
}

void initRandomPiece(struct pieceInfo *pieceToInit){
    int shapeNum = rand() % NUM_SHAPES;
    enum shape shapeType = shapeNum;

    memcpy(pieceToInit->piece, figs[shapeNum], pieceLenByShape(shapeType) * sizeof(uint8_t));
    pieceToInit->pieceShape = shapeType;

    pieceToInit->pieceX = SPAWN_X;
    pieceToInit->pieceY = SPAWN_Y;
}

void updateBoard(int *board, struct pieceInfo *playerPiece){
    int renderedBoard[BOARDSIZE];
    renderBoard(renderedBoard, board, playerPiece, false);
    memcpy(board, renderedBoard, sizeof(int) * BOARDSIZE);
}

bool checkSpawnPiece(uint8_t *pieceToSpawn, int *boardToSpawnIn, enum shape pieceShape){
    return checkMove(pieceToSpawn, SPAWN_X, SPAWN_Y, pieceShape, boardToSpawnIn);
}

void renderBoard(int *renderedBoard, int *boardToRender, struct pieceInfo *pieceToRender, bool substract){

    int sideLen = sideLenByShape(pieceToRender->pieceShape);
    int pieceLen = pieceLenByShape(pieceToRender->pieceShape);

    memcpy(renderedBoard, boardToRender, sizeof(int) * BOARDSIZE);

        for(int i = 0; i < pieceLen; i++){
        if(!(pieceToRender->piece[i])){
            continue;
        }

        int blockX = i % sideLen + pieceToRender->pieceX;
        int blockY = i / sideLen + pieceToRender->pieceY;
        int boardPos = blockY * BOARD_X + blockX;

        if(substract){
            renderedBoard[boardPos] = 0;
        }else{
            renderedBoard[boardPos] = 1;
        }
    }
}

enum boardAction handleUserInput(enum userRequest r, int *board, struct pieceInfo *playerPiece){
    
    int pieceLen = pieceLenByShape(playerPiece->pieceShape);
    uint8_t modifiedPiece[MAX_PIECE_LEN];

    int pieceX = playerPiece->pieceX;
    int pieceY = playerPiece->pieceY;
    enum shape pieceShape = playerPiece->pieceShape;

    int yOffset = 0;

    memcpy(modifiedPiece, playerPiece->piece, sizeof(uint8_t) * pieceLen);

    switch (r)
    {
    case requestRotateRight:
        rotateRight(modifiedPiece, pieceShape);
        if(checkMove(modifiedPiece, pieceX, pieceY, pieceShape, board)){
            memcpy(playerPiece->piece, modifiedPiece, sizeof(uint8_t) * pieceLen);
        }
        return redraw;

    case requestRotateLeft:
        rotateLeft(modifiedPiece, pieceShape);
        if(checkMove(modifiedPiece, pieceX, pieceY, pieceShape, board)){
            memcpy(playerPiece->piece, modifiedPiece, sizeof(uint8_t) * pieceLen);
        }
        return redraw;

    case requestRight:
        if(checkMove(playerPiece->piece, pieceX + 1, pieceY, pieceShape, board)){
            return moveRight;
        }
        return none;
    case requestLeft:
        if(checkMove(playerPiece->piece, pieceX - 1, pieceY, pieceShape, board)){
            return moveLeft;
        }
        return none;

    case requestDrop:
        return dropOne;
    
    case requestInstantDrop:
        while(1){
            if(!checkMove(playerPiece->piece, pieceX, pieceY + yOffset + 1, pieceShape, board)){
                playerPiece->pieceY += yOffset;
                break;
            }

            yOffset++;
        }
        return instantDrop;

    default:
        break;
    }

    return none;
}

bool checkMove(uint8_t *piece, uint8_t piecePosX, uint8_t piecePosY, enum shape pieceShape, int *boardToCheck){

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

void rotateRight(uint8_t *dest, enum shape curShape){

    if(curShape == SquareShape){
        return;
    }

    uint8_t tmpShapeCopy[MAX_PIECE_LEN];
    int pos = 0;
    int sideLen = sideLenByShape(curShape);

    memcpy(tmpShapeCopy, dest, pieceLenByShape(curShape) * sizeof(uint8_t));

    for(int x = 0; x < sideLen; x++){
    	for(int y = sideLen - 1; y >= 0; y--){
    		dest[pos] = tmpShapeCopy[sideLen * y + x];
            pos++;
    	}
    }
}

void rotateLeft(uint8_t *dest, enum shape curShape){

    uint8_t tmpShapeCopy[MAX_PIECE_LEN];
    int pos = 0;
    int sideLen = sideLenByShape(curShape);

    memcpy(tmpShapeCopy, dest, pieceLenByShape(curShape) * sizeof(uint8_t));

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
