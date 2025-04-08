#include <iostream>
#include "defs.h"
#include "hangman.h"
#include "graphics.h"

using namespace std;


int main(int argc, char* argv[])
{
    Hangman game;
    game.startPage();
    bool quitGame = false;
    while(!quitGame){
        game.gameStart();
        game.playGame();
        if(game.returnToMenu()){
            continue;
        }
        game.gameOver();
        quitGame = true;
    }
    return 0;
}

