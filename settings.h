#ifndef SETTINGS_MTETRIS
#define SETTINGS_MTETRIS

#define BOARD_X 8
#define BOARD_Y 16
#define BOARDSIZE (BOARD_X * BOARD_Y)

#define TETRIS_TICK_MS 750
#define SNEK_TICK_MS 200

#ifdef TETRIS
    #define TICK_MS TETRIS_TICK_MS
#else
   #define TICK_MS SNEK_TICK_MS 
#endif

#define GAME_OVER_MS 100

#define DEFAULT_BOX_SIDE 3
#define I_PIECE_BOX_SIDE 4

#define DEFAULT_PIECE_LEN (DEFAULT_BOX_SIDE * DEFAULT_BOX_SIDE)
#define I_PIECE_LEN (I_PIECE_BOX_SIDE * I_PIECE_BOX_SIDE)

#define MAX_PIECE_LEN I_PIECE_LEN
#define MAX_BOX_SIDE I_PIECE_BOX_SIDE

#define SPAWN_X (BOARD_X / 2) - 1
#define SPAWN_Y 0

#define BINDING_UP 'w'
#define BINDING_LEFT 'a'
#define BINDING_RIGHT 'd'
#define BINDING_DOWN 's'
#define BINDING_ROATATE_LEFT 'q'
#define BINDING_ROTATE_RIGHT 'e'

#define BINDING_LOAD_NEW_GAME 'k'

enum gameSignal{continueTimer, skipTimer, gameOver, gameContinues};

#endif
