#ifndef TETRIS
#define TETRIS

#define BOARD_X 8
#define BOARD_Y 16
#define BOARDSIZE BOARD_X * BOARD_Y


#define PIECE_LEN 9

#define SPAWN_X 3
#define SPAWN_Y 0

#include <stdbool.h>

enum shape{SquareShape, TShape, ZShape, SShape, JShape, LShape};
enum boardAction{none, redraw, moveRight, moveLeft, drop, instantDrop};


void rotateRight(int *dest, int len, enum shape curShape);
void rotateLeft(int *dest, int len, enum shape curShape);


void initBoard(int *boardToInit);
void updateBoard(int *board, int *playerPiece, int pieceX, int pieceY);

enum boardAction handleUserInput(char input, int *board, int *playerPiece, int pieceX, int pieceY);

bool checkSpawnPiece(int *pieceToSpawn, int *boardToSpawnIn);
void renderBoard(int *renderedBoard, int *boardToRender, int *pieceToRender, int piecePosX, int piecePosY);
bool checkMove(int *piece, int piecePosX, int piecePosY, int *boardToCheck);


#endif