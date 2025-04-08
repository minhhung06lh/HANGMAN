#ifndef DEFS__H
#define DEFS__H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
#define WINDOW_TITLE "HANGMAN"

const int START_GUESS = 0;
const int MAX_BAD_GUESSES = 6;

#define MAIN_BACKGROUND "image\\background.png"
#define WIN_BACKGROUND "image\\background2.png"
#define LOSE_BACKGROUND "image\\background3.png"

#define START_BUTTON "image\\startButton.png"
#define BACK_BUTTON "image\\backButton.png"
#define EASY_BUTTON "image\\easyButton.png"
#define MEDIUM_BUTTON "image\\medButton.png"
#define HARD_BUTTON "image\\hardButton.png"

#define FONT "font\\Minecraft.ttf"
#define HANGMAN_FONT "font\\PressStart2P-Regular.ttf"

#define EASY_LIST "Vocabulary\\Easy.txt"
#define MEDIUM_LIST "Vocabulary\\Medium.txt";
#define HARD_LIST "Vocabulary\\Hard.txt";

#define GAME_TITLE "HANGMAN"
#define WIN_TEXT "CONGRATULATION!!"
#define LOSE_TEXT "YOU LOSE!"

#define GALLOW "image\\gallow.png"

#define BODY1 "image\\body1.png"
#define BODY2 "image\\body2.png"
#define BODY3 "image\\body3.png"
#define BODY4 "image\\body4.png"
#define BODY5 "image\\body5.png"
#define BODY6 "image\\body6.png"

#define MUSIC "SFX\\HangmanMusic.wav"
#define CORRCECT_SOUND "SFX\\Correct.mp3"
#define INCORRCECT_SOUND "SFX\\Incorrect.mp3"
#define WIN_SOUND "SFX\\Win.mp3"
#define LOSE_SOUND "SFX\\Lose.mp3"

const int START_X = 310;
const int START_Y = 300;

const int BACK_X = 365;
const int BACK_Y = 500;

const int LEVEL_BUTTON_X = 342;
const int EASY_Y = 250;
const int MED_Y = 335;
const int HARD_Y = 420;

const int TITLE_X = 215;
const int TITLE_Y = 100;

const int START_W = 180;
const int START_H = 70;

const int BACK_W = 70;
const int BACK_H = 70;

const int BUTTON_W = 115;
const int BUTTON_H = 69;

const int WORD_X = 50;
const int WORD_Y = 400;

const int WIN_X = 50;
const int LOSE_X = 215;
const int RESULT_Y = 220;

const int GALLOW_X = 550;
const int GALLOW_Y = 252;

const int BODY_X[6] = {511, 558, 511, 614, 534, 582};
const int BODY_Y[6] = {300, 369, 368, 371, 431, 434};

const int TITLE_SIZE = 80;
const int WORD_SIZE = 40;
const int RESULT_SIZE = 70;
#endif //DEFS_H
