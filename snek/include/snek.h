#ifndef SNEK_H
#define SNEK_H

#include <stdbool.h>
#include <stdint.h>

#define SNEK_SPAWN_LEN 4
#define SNEK_SPAWN_Y (BOARD_Y / 4)
#define SNEK_SPAWN_X ((BOARD_X - SNEK_SPAWN_LEN) / 2)

enum snekDirection{snekUp, snekDown, snekRight, snekLeft};

void initSnek(uint8_t *curSnek);
int initFood(uint8_t *curSnek, int curSnekLen);
void renderSnekBoard(uint8_t *board, uint8_t *snek, int snekLen, int foodPos);
bool snekMove(uint8_t *curSnek, int *curSnekLen, enum snekDirection dir, int *foodPos);
enum snekDirection oppositeDirection(enum snekDirection dir);


#endif