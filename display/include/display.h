#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include "settings.h"

void initDisplay();
void drawBoard(uint8_t *boardToDraw);

#endif