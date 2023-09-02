#include "inc/display.h"


WINDOW* initCurses(){

    WINDOW *wnd;

    wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();


    return wnd;
}


void drawBoard(int *boardToDraw){

    clear();

    for(int i = 0; i < BOARDSIZE; i++){
        
        int y = i / BOARD_X;
        int x = i - y * BOARD_X;

        move(y, x);
        delch();

        if(boardToDraw[i]){
            insch('x');
        }else{
            insch('.');
        }

    }

    for(int i = 0; i < BOARD_Y; i++){
        move(i, BOARD_X);
        insch('|');
    }

    refresh();
}
