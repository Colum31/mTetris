#ifndef TETRIS_RUNNER
#define TETRIS_RUNNER

#include "tetris.h"

void initTetrisGame(uint8_t (*boardPtr)[BOARDSIZE]);
enum gameSignal handleTetrisTick();
enum gameSignal handleTetrisUserEvent(char c);
bool gameOverTetrisAnimation();
#endif