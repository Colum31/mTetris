#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include "settings.h"

enum shape{SquareShape, TShape, ZShape, SShape, JShape, LShape, IShape};

struct pieceInfo{
    int piece[MAX_PIECE_LEN];
    int pieceX;
    int pieceY;
    enum shape pieceShape;
};

enum userRequest{requestLeft, requestRight, requestDrop, requestRotateRight, requestRotateLeft, requestInstantDrop};
enum boardAction{none, redraw, moveRight, moveLeft, dropOne, instantDrop};


void rotateRight(int *dest, enum shape curShape);
void rotateLeft(int *dest,  enum shape curShape);


void initBoard(int *boardToInit);
void initRandomPiece(struct pieceInfo *pieceToInit);

void updateBoard(int *board, struct pieceInfo *playerPiece);
void clearRows(int *boardToClear, int pieceY);

enum boardAction handleUserInput(enum userRequest r, int *board, struct pieceInfo *playerPiece);

bool checkSpawnPiece(int *pieceToSpawn, int *boardToSpawnIn, enum shape pieceShape);
void renderBoard(int *renderedBoard, int *boardToRender, struct pieceInfo *pieceToRender);
bool checkMove(int *piece, int piecePosX, int piecePosY, enum shape pieceShape, int *boardToCheck);


#endif