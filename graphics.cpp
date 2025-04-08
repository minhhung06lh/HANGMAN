#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "defs.h"
#include "graphics.h"

void Graphics::logErrorAndExit(const char* msg, const char* error){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::init(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
        logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (TTF_Init() == -1){
        logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError());
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
}

void Graphics::prepareScene(SDL_Texture * background){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
}

void Graphics::presentScene(){
    SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::loadTexture(const char *filename){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
    return texture;
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

TTF_Font* Graphics::loadFont(const char* path, int size){
    TTF_Font* gFont = TTF_OpenFont(path, size);
    if (gFont == nullptr){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }
}

SDL_Texture* Graphics::renderText(const char* text, TTF_Font* font, SDL_Color textColor){
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );
    if( textSurface == nullptr ){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if( texture == nullptr ){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
    }
    SDL_FreeSurface( textSurface );
    return texture;
}

Mix_Music* Graphics::loadMusic(const char* path){
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }
void Graphics::play(Mix_Music *gMusic){
    if (gMusic == nullptr) return;
    if (Mix_PlayingMusic() == 0){
        Mix_PlayMusic(gMusic, -1);
    }
    else if( Mix_PausedMusic() == 1 ){
        Mix_ResumeMusic();
    }
}
Mix_Chunk* Graphics::loadSound(const char* path){
    Mix_Chunk* gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
    }
}
void Graphics::play(Mix_Chunk* gChunk){
    if (gChunk != nullptr){
        Mix_PlayChannel(-1, gChunk, 0);
    }
}

void Graphics::quit(){
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::loadGraphic(){
    init();

    mainBackground = loadTexture(MAIN_BACKGROUND);
    winBackground = loadTexture(WIN_BACKGROUND);
    loseBackground = loadTexture(LOSE_BACKGROUND);

    startButton = loadTexture(START_BUTTON);
    backButton = loadTexture(BACK_BUTTON);

    easy = loadTexture(EASY_BUTTON);
    medium = loadTexture(MEDIUM_BUTTON);
    hard = loadTexture(HARD_BUTTON);

    titleFont = loadFont(FONT, TITLE_SIZE);
    SDL_Color titleColor = {255, 255, 0, 255};
    title = renderText(GAME_TITLE, titleFont, titleColor);

    wordFont = loadFont(HANGMAN_FONT, WORD_SIZE);
    wordColor = {255, 255, 255, 255};

    correctWordText = renderText("Correct word is:", wordFont, wordColor);

    resultFont = loadFont(FONT, RESULT_SIZE);
    SDL_Color winColor = {0, 255, 0, 255};
    winText = renderText(WIN_TEXT, resultFont, winColor);
    SDL_Color loseColor = {255, 0, 0, 255};
    loseText = renderText(LOSE_TEXT, resultFont, loseColor);

    gallow = loadTexture(GALLOW);
    body[0] = loadTexture(BODY1);
    body[1] = loadTexture(BODY2);
    body[2] = loadTexture(BODY3);
    body[3] = loadTexture(BODY4);
    body[4] = loadTexture(BODY5);
    body[5] = loadTexture(BODY6);

    gameMusic = loadMusic(MUSIC);
    correctSound = loadSound(CORRCECT_SOUND);
    incorrectSound = loadSound(INCORRCECT_SOUND);
    winSound = loadSound(WIN_SOUND);
    loseSound = loadSound(LOSE_SOUND);
}

void Graphics::drawMain(){
    prepareScene(mainBackground);
    renderTexture(title, TITLE_X, TITLE_Y);
    renderTexture(startButton, START_X, START_Y);

    presentScene();
}
void Graphics::drawMenu(){
    prepareScene(mainBackground);
    renderTexture(title, TITLE_X, TITLE_Y);

    renderTexture(easy, LEVEL_BUTTON_X, EASY_Y);
    renderTexture(medium, LEVEL_BUTTON_X, MED_Y);
    renderTexture(hard, LEVEL_BUTTON_X, HARD_Y);

    presentScene();
}

void Graphics::drawWord(const char* word){
    wordText = renderText(word, wordFont, wordColor);
    renderTexture(wordText, WORD_X, WORD_Y);
    presentScene();
}

void Graphics::drawPlaying(const int wrongGuesses,const char* guessedWord){
    prepareScene(mainBackground);

    drawWord(guessedWord);

    renderTexture(gallow, GALLOW_X, GALLOW_Y);
    if(wrongGuesses > 0){
        for(int i = 0; i < wrongGuesses; i++){
            renderTexture(body[i], BODY_X[i], BODY_Y[i]);
        }
    }
    presentScene();
}
void Graphics::drawWinScreen(){
    play(winSound);

    prepareScene(winBackground);
    renderTexture(title, TITLE_X, TITLE_Y);
    renderTexture(winText, WIN_X, RESULT_Y);
    presentScene();
}

void Graphics::drawLoseScreen(){
    play(loseSound);

    prepareScene(loseBackground);
    renderTexture(title, TITLE_X, TITLE_Y);
    renderTexture(loseText, LOSE_X, RESULT_Y);

    presentScene();
}

void Graphics::free(){
    Mix_FreeMusic(gameMusic);
    Mix_FreeChunk(correctSound);
    Mix_FreeChunk(incorrectSound);
    Mix_FreeChunk(winSound);
    Mix_FreeChunk(loseSound);

    SDL_DestroyTexture(gallow);
    gallow = NULL;
    SDL_DestroyTexture(body[1]);
    body[1] = NULL;
    SDL_DestroyTexture(body[2]);
    body[2] = NULL;
    SDL_DestroyTexture(body[3]);
    body[3] = NULL;
    SDL_DestroyTexture(body[4]);
    body[4] = NULL;
    SDL_DestroyTexture(body[5]);
    body[5] = NULL;
    SDL_DestroyTexture(body[6]);
    body[6] = NULL;

    SDL_DestroyTexture(wordText);
    wordText = NULL;
    SDL_DestroyTexture(correctWordText);
    correctWordText = NULL;
    SDL_DestroyTexture(title);
    title = NULL;
    SDL_DestroyTexture(winText);
    winText = NULL;
    SDL_DestroyTexture(loseText);
    loseText = NULL;

    TTF_CloseFont(titleFont);
    TTF_CloseFont(wordFont);
    TTF_CloseFont(resultFont);

    SDL_DestroyTexture(mainBackground);
    mainBackground = NULL;
    SDL_DestroyTexture(winBackground);
    winBackground = NULL;
    SDL_DestroyTexture(loseBackground);
    loseBackground = NULL;

    SDL_DestroyTexture(startButton);
    startButton = NULL;
    SDL_DestroyTexture(backButton);
    backButton = NULL;

    SDL_DestroyTexture(easy);
    easy = NULL;
    SDL_DestroyTexture(medium);
    medium = NULL;
    SDL_DestroyTexture(hard);
    hard = NULL;
}
