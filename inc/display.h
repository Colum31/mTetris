#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include "settings.h"

void initCurses();
void drawBoard(int *boardToDraw);

#endif