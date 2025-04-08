#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
struct Graphics{
    SDL_Renderer *renderer;
	SDL_Window *window;

    SDL_Texture *mainBackground;
    SDL_Texture *winBackground;
    SDL_Texture *loseBackground;

    SDL_Texture *startButton;
    SDL_Texture *backButton;
    SDL_Texture *easy;
    SDL_Texture *medium;
    SDL_Texture *hard;

    TTF_Font* titleFont;
    TTF_Font* wordFont;
    TTF_Font* resultFont;

    SDL_Color wordColor;

    SDL_Texture *title;
    SDL_Texture *winText;
    SDL_Texture *loseText;
    SDL_Texture *wordText;
    SDL_Texture *correctWordText;

    SDL_Texture *gallow;
    SDL_Texture *body[6];

    Mix_Music *gameMusic;
    Mix_Chunk *correctSound;
    Mix_Chunk *incorrectSound;
    Mix_Chunk *winSound;
    Mix_Chunk *loseSound;

	void logErrorAndExit(const char* msg, const char* error);

	void init();
	void prepareScene(SDL_Texture * background);
    void presentScene();
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);

    TTF_Font* loadFont(const char* path, int size);
    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor);

    Mix_Music *loadMusic(const char* path);
    void play(Mix_Music *gMusic);
    Mix_Chunk* loadSound(const char* path);
    void play(Mix_Chunk* gChunk);

    void quit();

    void loadGraphic();
    void drawMain();
    void drawMenu();
    void drawWord(const char* word);
    void drawStart(const char* guessedWord);
    void drawPlaying(const int wrongGuesses,const char* guessedWord);
    void drawWinScreen();
    void drawLoseScreen();
    void free();
};

#endif // GRAPHICS_H
