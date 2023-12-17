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

uint8_t pieceLenByShape(enum shape pieceShape){
    if(pieceShape == IShape){
        return I_PIECE_LEN;
    }
    return DEFAULT_PIECE_LEN;   
}

uint8_t sideLenByShape(enum shape pieceShape){
    if(pieceShape == IShape){
        return I_PIECE_BOX_SIDE;
    }
    return DEFAULT_BOX_SIDE;   
}


void initBoard(uint8_t *boardToInit){
    memset(boardToInit, 0, sizeof(uint8_t) * BOARDSIZE);
}

void initRandomPiece(struct pieceInfo *pieceToInit){
    int shapeNum = rand() % NUM_SHAPES;
    enum shape shapeType = shapeNum;

    memcpy(pieceToInit->piece, figs[shapeNum], pieceLenByShape(shapeType) * sizeof(uint8_t));
    pieceToInit->pieceShape = shapeType;

    pieceToInit->pieceX = SPAWN_X;
    pieceToInit->pieceY = SPAWN_Y;
}

void updateBoard(uint8_t *board, struct pieceInfo *playerPiece){
    uint8_t renderedBoard[BOARDSIZE];
    renderBoard(renderedBoard, board, playerPiece, false);
    memcpy(board, renderedBoard, sizeof(uint8_t) * BOARDSIZE);
}

bool checkSpawnPiece(uint8_t *pieceToSpawn, uint8_t *boardToSpawnIn, enum shape pieceShape){
    return checkMove(pieceToSpawn, SPAWN_X, SPAWN_Y, pieceShape, boardToSpawnIn);
}

void renderBoard(uint8_t *renderedBoard, uint8_t *boardToRender, struct pieceInfo *pieceToRender, bool substract){

    uint8_t sideLen = sideLenByShape(pieceToRender->pieceShape);
    uint8_t pieceLen = pieceLenByShape(pieceToRender->pieceShape);

    memcpy(renderedBoard, boardToRender, sizeof(uint8_t) * BOARDSIZE);

        for(int i = 0; i < pieceLen; i++){
        if(!(pieceToRender->piece[i])){
            continue;
        }

        int8_t blockX = i % sideLen + pieceToRender->pieceX;
        int8_t blockY = i / sideLen + pieceToRender->pieceY;
        int8_t boardPos = blockY * BOARD_X + blockX;

        if(substract){
            renderedBoard[boardPos] = 0;
        }else{
            renderedBoard[boardPos] = 1;
        }
    }
}

enum boardAction handleUserInput(enum userRequest r, uint8_t *board, struct pieceInfo *playerPiece){
    
    uint8_t pieceLen = pieceLenByShape(playerPiece->pieceShape);
    uint8_t modifiedPiece[MAX_PIECE_LEN];

    int8_t pieceX = playerPiece->pieceX;
    int8_t pieceY = playerPiece->pieceY;
    enum shape pieceShape = playerPiece->pieceShape;

    int8_t yOffset = 0;

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

bool checkMove(uint8_t *piece, int8_t piecePosX, int8_t piecePosY, enum shape pieceShape, uint8_t *boardToCheck){

    uint8_t sideLen = sideLenByShape(pieceShape);

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
    int8_t pos = 0;
    uint8_t sideLen = sideLenByShape(curShape);

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
    int8_t pos = 0;
    uint8_t sideLen = sideLenByShape(curShape);

    memcpy(tmpShapeCopy, dest, pieceLenByShape(curShape) * sizeof(uint8_t));

    for(int x = sideLen - 1; x >= 0; x--){
        for (int y = 0; y < sideLen; y++){
            dest[pos] = tmpShapeCopy[sideLen * y + x];
            pos++;
        }
    }
}

void clearRows(uint8_t *boardToClear, int8_t pieceY){

    for(int8_t y = pieceY; y < pieceY + MAX_BOX_SIDE + 1 && y < BOARD_Y; y++){

        bool rowSet = true;
        
        for(int boardPos = y * BOARD_X; boardPos < y * BOARD_X + BOARD_X; boardPos++){
            if(!boardToClear[boardPos]){
                rowSet = false;
                break;
            }
        }

        if(!rowSet){
            continue;
        }
        memset(&boardToClear[y * BOARD_X], 0, BOARD_X * sizeof(uint8_t));

        uint16_t toMove = y * BOARD_X;

        memmove(&boardToClear[BOARD_X], boardToClear, toMove * sizeof(uint8_t));
    }

}
