#include "Graphlib.h"
#include "Error.h"
#include <SDL_ttf.h>
#include <stdbool.h>

static bool          GraphlibInitialized = false;
static bool          TTFinitialized      = false;
static SDL_Window*   Window              = NULL;
static SDL_Renderer* Renderer            = NULL;
static TTF_Font*     FontData            = NULL;

TTF_Font* Font(void)
{
    return FontData;
}

SDL_Window* MainWindow(void)
{
    return Window;
}

SDL_Renderer* MainRenderer(void)
{
    return Renderer;
}

int InitGraphlib(void)
{
    //
    // SDL
    //
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        return ERROR_SDL_INIT;
    }
    GraphlibInitialized = true;

    // Create window
    Window = SDL_CreateWindow("Splice Detector Trend", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (Window == NULL) {
        return ERROR_SDL_CREATE_WINDOW;
    }

    // Create renderer
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if (Renderer == NULL) {
        return ERROR_SDL_CREATE_RENDERER;
    }

    //
    // TTF. It must be loaded after SDL
    //
    if (TTF_Init() != 0) {
        return ERROR_TTF_INIT;
    }
    TTFinitialized = true;

    // Load font
    FontData = TTF_OpenFont(FONT_NAME, 32);
    if (FontData == NULL) {
        return ERROR_TTF_OPEN_FONT;
    }

    return ERROR_NO_ERROR;
}

void ExitGraphlib(void)
{
    //
    // TTF
    //
    if (FontData != NULL) {
        TTF_CloseFont(FontData);
        FontData = NULL;
    }

    if (TTFinitialized) {
        TTF_Quit();
        TTFinitialized = false;
    }

    //
    // SDL
    //
    if (Renderer != NULL) {
        SDL_DestroyRenderer(Renderer);
        Renderer = NULL;
    }

    if (Window != NULL) {
        SDL_DestroyWindow(Window);
        Window = NULL;
    }

    if (GraphlibInitialized) {
        SDL_Quit();
        GraphlibInitialized = false;
    }
}

int CreateText(SDL_Texture** texture, SDL_Rect* rect, char* text, SDL_Color* color)
{
    SDL_Surface* surface = TTF_RenderText_Blended(FontData, text, *color);
    if (surface == NULL) {
        return ERROR_SDL_CREATE_SURFACE;
    }

    *texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_FreeSurface(surface);
    if (*texture == NULL) {
        return ERROR_SDL_CREATE_TEXTURE;
    }

    if (SDL_QueryTexture(*texture, NULL, NULL, &(rect->w), &(rect->h)) != 0) {
        SDL_DestroyTexture(*texture);
        return ERROR_SDL_QUERY_TEXTURE;
    }

    return ERROR_NO_ERROR;
}
