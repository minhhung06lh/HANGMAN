#ifndef HANGMAN_H
#define HANGMAN_H

#include <iostream>
#include "graphics.h"
using namespace std;


struct Hangman{
    string secretWord;
    char* guessedWord;
    int wrongGuesses;
    char check;

    SDL_Event event;
    int x, y;

    string chooseWord();
    void checkGuess(char letter);
    void result();
    void render();

    void startPage();
    void gameStart();
    void playGame();
    void gameOver();

    bool returnToMenu();
};
#endif // HANGMAN_H
