#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "defs.h"
#include "hangman.h"
#include "graphics.h"

using namespace std;

Graphics graphics;
string Hangman::chooseWord(){
    string path;
    bool quit = false;
    while(!quit){
        SDL_PollEvent(&event);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            SDL_GetMouseState(&x, &y);
            if(x > LEVEL_BUTTON_X && x < LEVEL_BUTTON_X + BUTTON_W && y > EASY_Y && y < EASY_Y + BUTTON_H){
                path = EASY_LIST;
                quit = true;
            }
            else if(x > LEVEL_BUTTON_X && x < LEVEL_BUTTON_X + BUTTON_W && y > MED_Y && y < MED_Y + BUTTON_H){
                path = MEDIUM_LIST;
                quit = true;
            }
            else if(x > LEVEL_BUTTON_X && x < LEVEL_BUTTON_X + BUTTON_W && y > HARD_Y && y < HARD_Y + BUTTON_H){
                path = HARD_LIST;
                quit = true;
            }
        }
        SDL_Delay(10);
    }
    ifstream levelFile(path);
    string tmp;
    vector <string> wordList;
    int listSize = 0;
    while(levelFile >> tmp){
        wordList.push_back(tmp);
        listSize++;
    }
    srand(time(NULL));
    int randomIndex = rand() % listSize;
    return wordList[randomIndex];
}

void Hangman::checkGuess(char letter){
    check = false;
    for(int i = 0; i < secretWord.length(); i++){
        if(secretWord[i] == letter && guessedWord[i] == '_'){
            guessedWord[i] = letter;
            check = true;
        }
    }
    if(!check)
        wrongGuesses++;

}

void Hangman::result(){
    if(guessedWord == secretWord){
        graphics.drawWinScreen();
    }
    else
        graphics.drawLoseScreen();

    graphics.renderTexture(graphics.correctWordText, WORD_X, WORD_Y - 80);
    graphics.presentScene();
    graphics.drawWord(secretWord.c_str());
}

void Hangman::render(){
    if(check)
        graphics.play(graphics.correctSound);
    else
        graphics.play(graphics.incorrectSound);
    graphics.drawPlaying(wrongGuesses, guessedWord);
}

void Hangman::startPage(){
    graphics.loadGraphic();
    graphics.drawMain();
    graphics.play(graphics.gameMusic);
    int x, y;
    bool quit = false;
    while (!quit){
        SDL_PollEvent(&event);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            SDL_GetMouseState(&x, &y);
            if(x > START_X && x < START_X + START_W && y > START_Y && y < START_Y + START_H){
                quit = true;
            }
        }
        SDL_Delay(10);
    }
}

void Hangman::gameStart(){
    graphics.drawMenu();
    secretWord = chooseWord();
    guessedWord = new char[secretWord.length() + 1];
    for (int i = 0; i < secretWord.length(); i++) {
        guessedWord[i] = '_';
    }
    guessedWord[secretWord.length()] = '\0';
    wrongGuesses = START_GUESS;
    graphics.drawPlaying(wrongGuesses,guessedWord);
    cout << endl << secretWord << endl;
}

void Hangman::playGame(){
    do{
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN){
                SDL_Scancode sc = event.key.keysym.scancode;
                if(sc >= SDL_SCANCODE_A && sc <= SDL_SCANCODE_Z){
                    char letter = 'a' + (sc - SDL_SCANCODE_A);
                    checkGuess(letter);
                    if(guessedWord != secretWord){
                        render();
                    }
                }
            }
        }
    }while(guessedWord != secretWord && wrongGuesses < MAX_BAD_GUESSES);
    result();
}

void Hangman::gameOver(){
    graphics.free();
    graphics.quit();
    delete [] guessedWord;
}

bool Hangman::returnToMenu(){
    graphics.renderTexture(graphics.backButton, BACK_X, BACK_Y);
    graphics.presentScene();
    bool quit = false;
    while(!quit){
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT)
            quit = true;
        else if(event.type == SDL_MOUSEBUTTONDOWN){
            SDL_GetMouseState(&x, &y);
            if(x > BACK_X && x < BACK_X + BACK_W && y > BACK_Y && y < BACK_Y + BACK_H){
                return true;
                quit = true;
            }
        }
        SDL_Delay(10);
    }
    return false;
}
