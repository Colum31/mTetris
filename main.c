#ifdef TETRIS
    #include "tetrisRunner.h"
#else
    #include "snekRunner.h"
#endif

#include "display.h"
#include "timer.h"


#ifdef TETRIS

    #define GAMEBOARD curRenderedBoard
    void (*initGame)(void) = &initTetrisGame;
    enum gameSignal (*handleTick)(void) = &handleTetrisTick;
    enum gameSignal (*handleUserEvent)(char) = &handleTetrisUserEvent;
    bool (*gameOverAnimation)(void) = &gameOverTetrisAnimation;
#else

    #define GAMEBOARD curRenderedSnekBoard
    void (*initGame)(void) = &initSnekGame;
    enum gameSignal (*handleTick)(void) = &handleSnekTick;
    enum gameSignal (*handleUserEvent)(char) = &handleUserSnek; 
    bool (*gameOverAnimation)(void) = &gameOverAnimationSnek;

#endif

int main(){
    initDisplay();
    (*initGame)();
    saveTickTime();
    drawBoard(GAMEBOARD);

    int startedGame = 1;

    timeout(TICK_MS);

    while(1){
        // main game loop

        if(startedGame == 0 && (*handleTick)() == gameOver){
            break;
        }

        drawBoard(GAMEBOARD);

        timeout(TICK_MS);
        saveTickTime();

        while(1){
            char c = getch();

            if(c == ERR){
                saveTickTime();
                break;
            }

            if((*handleUserEvent)(c) == skipTimer){
                drawBoard(GAMEBOARD);
                break;
            }

            drawBoard(GAMEBOARD);

            int remainingTime = checkTick();
            timeout(remainingTime);

        }

        startedGame = 0;
    }

    while(!(*gameOverAnimation)()){
        drawBoard(GAMEBOARD);
        napms(GAME_OVER_MS);
    }

    endwin();

    return 0;
}