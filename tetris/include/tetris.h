#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdint.h>
#include "settings.h"

enum shape{SquareShape, TShape, ZShape, SShape, JShape, LShape, IShape};

struct pieceInfo{
    uint8_t piece[MAX_PIECE_LEN];
    uint8_t pieceX;
    uint8_t pieceY;
    enum shape pieceShape;
};

enum userRequest{requestLeft, requestRight, requestDrop, requestRotateRight, requestRotateLeft, requestInstantDrop};
enum boardAction{none, redraw, moveRight, moveLeft, dropOne, instantDrop};


void rotateRight(uint8_t *dest, enum shape curShape);
void rotateLeft(uint8_t *dest,  enum shape curShape);


void initBoard(uint8_t *boardToInit);
void initRandomPiece(struct pieceInfo *pieceToInit);

void updateBoard(uint8_t *board, struct pieceInfo *playerPiece);
void clearRows(uint8_t *boardToClear, int pieceY);

enum boardAction handleUserInput(enum userRequest r, uint8_t *board, struct pieceInfo *playerPiece);

bool checkSpawnPiece(uint8_t *pieceToSpawn, uint8_t *boardToSpawnIn, enum shape pieceShape);
void renderBoard(uint8_t *renderedBoard, uint8_t *boardToRender, struct pieceInfo *pieceToRender, bool substract);
bool checkMove(uint8_t *piece, uint8_t piecePosX, uint8_t piecePosY, enum shape pieceShape, uint8_t *boardToCheck);


#endif