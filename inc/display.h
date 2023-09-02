#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include "settings.h"

WINDOW* initCurses();
void drawBoard(int *boardToDraw);

#endif