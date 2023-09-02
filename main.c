#include "inc/tetris.h"
#include "inc/display.h"
#include "inc/timer.h"

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
    initCurses();
    clear();
    refresh();

    initBoard(curBoard);
    saveTickTime();

    timeout(TICK_MS);

    int spawnFirstPiece = 1;
    int drop = 0;

    while(1){
        // main game loop

        if(!checkMove(curPiece, curPieceX, curPieceY + 1, curBoard) || spawnFirstPiece){

            spawnFirstPiece = 0;

            // save last piece on board
            updateBoard(curBoard, curPiece, curPieceX, curPieceY);

            clearRows(curBoard, curPieceY);
            // spawn new piece
            getRandomPiece(curPiece);

            curPieceY = SPAWN_Y;
            curPieceX = SPAWN_X;

            if(!checkSpawnPiece(curPiece, curBoard)){
                // Game over
                break;
            }
        }else{
            curPieceY++;
        }

        displayPlayerPiece(curBoard, curPiece, curPieceX, curPieceY);

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
    }

    napms(5000);
    endwin();

    return 0;
}