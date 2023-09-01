#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>

#include "inc/tetris.h"
#include "inc/main.h"

#define TICK_MS 750
#define DROP_MS 100

const int *figs[NUM_SHAPES] = {square, t, z, s, j, l};

int curBoard[BOARDSIZE];
int curPiece[PIECE_LEN];
int curPieceX = SPAWN_X;
int curPieceY = SPAWN_Y;

struct timespec lastTick;

WINDOW* initCurses(){

    WINDOW *wnd;

    wnd = initscr();
    cbreak();
    timeout(TICK_MS);
    noecho();
    clear();
    refresh();


    return wnd;
}


long double diff_ms(struct timespec *start, struct timespec *end){
    long double startTimeMs = start->tv_sec * 1000.0 + start->tv_nsec / 1000000.0;
    long double endTimeMs = end->tv_sec * 1000.0 + end->tv_nsec / 1000000.0;

    return endTimeMs - startTimeMs;
}

int checkTick(){

    struct timespec curTick;
    clock_gettime(CLOCK_REALTIME, &curTick);

    int diff = (int) diff_ms(&lastTick, &curTick);

    if(diff >= TICK_MS){
        return 0;
    }else{
        return TICK_MS - diff;
    }
}

void saveTickTime(){
    clock_gettime(CLOCK_REALTIME, &lastTick);
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

void displayPlayerPiece(int *board, int *playerPiece, int pieceX, int pieceY){
    int renderedBoard[BOARDSIZE];
    renderBoard(renderedBoard, board, playerPiece, pieceX, pieceY);
    drawBoard(renderedBoard);
}



bool checkMoveFinished(int *board, int *playerPiece, int pieceX, int pieceY){
    
    if(!checkMove(playerPiece, pieceX, pieceY, board)){
        updateBoard(board, playerPiece, pieceX, pieceY - 1);
        return true;
    }

    return false;

}


int main(){
    WINDOW *wnd = initCurses();
    clear();
    refresh();

    initBoard(curBoard);
    saveTickTime();

    memcpy(curPiece, figs[1], PIECE_LEN);

    while(1){
        // main game loop

        if(checkMoveFinished(curBoard, curPiece, curPieceX, curPieceY)){
            // spawn new piece
            memcpy(curPiece, figs[1], PIECE_LEN);

            curPieceY = SPAWN_Y;
            curPieceX = SPAWN_X;

            displayPlayerPiece(curBoard, curPiece, curPieceX, curPieceY);

            if(!checkSpawnPiece(curPiece, curBoard)){
                // Game over
                break;
            }
        }else{
            displayPlayerPiece(curBoard, curPiece, curPieceX, curPieceY);
        }

        // infra tick

        timeout(TICK_MS);
        saveTickTime();

        while(1){
            char c = getch();

            if(c == ERR){
                saveTickTime();
                break;
            }

            enum boardAction ret = handleUserInput(c, curBoard, curPiece, curPieceX, curPieceY);

            switch(ret){

                case moveRight:
                    curPieceX++;
                    break;
                case moveLeft:
                    curPieceX--;
                    break;

                default:
                    break;
            }

            if(ret == redraw || ret == moveRight || ret == moveLeft){
                displayPlayerPiece(curBoard, curPiece, curPieceX, curPieceY);
            }

            if(ret == drop){
                int remainingTime = checkTick();
                int timePassed = TICK_MS - remainingTime;

                if(timePassed > DROP_MS){
                    break;
                }

                napms(TICK_MS - timePassed);
                break;

            }

            int remainingTime = checkTick();
            timeout(remainingTime);

        }

        displayPlayerPiece(curBoard, curPiece, curPieceX, curPieceY);
        curPieceY++;

    }

    napms(5000);
    endwin();

    return 0;
}