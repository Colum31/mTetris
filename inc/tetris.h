#ifndef TETRIS
#define TETRIS

#include <stdbool.h>
#include "settings.h"

enum shape{SquareShape, TShape, ZShape, SShape, JShape, LShape};
enum boardAction{none, redraw, moveRight, moveLeft, dropOne, instantDrop};


void rotateRight(int *dest, int len, enum shape curShape);
void rotateLeft(int *dest, int len, enum shape curShape);


void initBoard(int *boardToInit);
void getRandomPiece(int *dest);

void updateBoard(int *board, int *playerPiece, int pieceX, int pieceY);

enum boardAction handleUserInput(char input, int *board, int *playerPiece, int pieceX, int pieceY);

bool checkSpawnPiece(int *pieceToSpawn, int *boardToSpawnIn);
void renderBoard(int *renderedBoard, int *boardToRender, int *pieceToRender, int piecePosX, int piecePosY);
bool checkMove(int *piece, int piecePosX, int piecePosY, int *boardToCheck);


#endif