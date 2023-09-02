#include <string.h>

#include "inc/tetris.h"
#include "inc/main.h"
#include "inc/display.h"
#include "inc/timer.h"

const int *figs[NUM_SHAPES] = {square, t, z, s, j, l};

int curBoard[BOARDSIZE];
int curPiece[PIECE_LEN];
int curPieceX = SPAWN_X;
int curPieceY = SPAWN_Y;

void displayPlayerPiece(int *board, int *playerPiece, int pieceX, int pieceY){
    int renderedBoard[BOARDSIZE];
    renderBoard(renderedBoard, board, playerPiece, pieceX, pieceY);
    drawBoard(renderedBoard);
}

int main(){
    WINDOW *wnd = initCurses();
    clear();
    refresh();

    initBoard(curBoard);
    saveTickTime();

    timeout(TICK_MS);

    memcpy(curPiece, figs[1], PIECE_LEN * sizeof(int));

    int drop = 0;

    while(1){
        // main game loop

        if(checkMoveFinished(curBoard, curPiece, curPieceX, curPieceY)){
            // spawn new piece
            memcpy(curPiece, figs[1], PIECE_LEN * sizeof(int));

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

            if(ret == dropOne){
                break;
            }

            displayPlayerPiece(curBoard, curPiece, curPieceX, curPieceY);

            int remainingTime = checkTick();
            timeout(remainingTime);

        }

        if(drop){
            drop = 0;
            napms(100);
        }

        displayPlayerPiece(curBoard, curPiece, curPieceX, curPieceY);
        curPieceY++;

    }

    napms(5000);
    endwin();

    return 0;
}