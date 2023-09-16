#ifndef SETTINGS_MTETRIS
#define SETTINGS_MTETRIS

#define BOARD_X 8
#define BOARD_Y 16
#define BOARDSIZE BOARD_X * BOARD_Y

#define TICK_MS 750
#define DROP_MS 100

#define PIECE_BOX_SIDE 3
#define PIECE_LEN (PIECE_BOX_SIDE * PIECE_BOX_SIDE)

#define SPAWN_X (BOARD_X / 2) - 1
#define SPAWN_Y 0

#define BINDING_LEFT 'a'
#define BINDING_RIGHT 'd'
#define BINDING_DROP 'f'
#define BINDING_ROATATE_LEFT 'q'
#define BINDING_ROTATE_RIGHT 'e'

#endif