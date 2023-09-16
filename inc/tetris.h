#ifndef TETRIS
#define TETRIS

#include <stdbool.h>
#include "settings.h"

enum shape{SquareShape, TShape, ZShape, SShape, JShape, LShape, IShape};

enum userRequest{requestLeft, requestRight, requestDrop, requestRotateRight, requestRotateLeft};
enum boardAction{none, redraw, moveRight, moveLeft, dropOne, instantDrop};


void rotateRight(int *dest, enum shape curShape);
void rotateLeft(int *dest,  enum shape curShape);


void initBoard(int *boardToInit);
enum shape getRandomPiece(int *dest);

void updateBoard(int *board, int *playerPiece, int pieceX, int pieceY);
void clearRows(int *boardToClear, int pieceY);

enum boardAction handleUserInput(enum userRequest r, int *board, int *playerPiece, int pieceX, int pieceY, enum shape pieceShape);

bool checkSpawnPiece(int *pieceToSpawn, int *boardToSpawnIn);
void renderBoard(int *renderedBoard, int *boardToRender, int *pieceToRender, int piecePosX, int piecePosY);
bool checkMove(int *piece, int piecePosX, int piecePosY, int sideLen, int *boardToCheck);


#endif