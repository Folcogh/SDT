#include "StateWelcome.h"
#include "Error.h"
#include "Graphlib.h"
#include "Quit.h"
#include "StateDisplayTrend.h"

// STATE interface
static int  Constructor(void);
static void Destructor(void);
static int  Run(SDL_Event* event);
static int  Resume(void);
STATE       StateWelcome = {STATE_WELCOME, Constructor, Destructor, Run, DummyPause, Resume};

//String containing the full filename of the dropped file
static char* DroppedFile = NULL;

// Title data
static SDL_Texture* TitleTexture = NULL;
static SDL_Rect     TitleRect;
static SDL_Color    TitleColor = {COLOR_LIGHT_GREY, 255};

// Drop text data
static SDL_Texture* DropTexture = NULL;
static SDL_Rect     DropRect;
static SDL_Color    DropColor = {COLOR_LIGHT_GREY, 255};

int Constructor(void)
{
    int Error = CreateText(&TitleTexture, &TitleRect, "SPLICE DETECTOR TREND", &TitleColor);
    if (Error != ERROR_NO_ERROR) {
        return Error;
    }

    Error = CreateText(&DropTexture, &DropRect, "< Drop a log file into this window >", &DropColor);
    return Error;
}

void Destructor(void)
{
    if (TitleTexture != NULL) {
        SDL_DestroyTexture(TitleTexture);
        TitleTexture = NULL;
    }

    if (DropTexture != NULL) {
        SDL_DestroyTexture(DropTexture);
        DropTexture = NULL;
    }

    if (DroppedFile != NULL) {
        SDL_free(DroppedFile);
        DroppedFile = NULL;
    }
}

int Run(SDL_Event* event)
{
    //
    // Events
    //
    switch (event->type) {
        case SDL_QUIT:
            RequestQuit();
            break;

        case SDL_DROPFILE:
            DroppedFile = event->drop.file;
            int error   = PushState(&StateDisplayTrend);
            if (error != ERROR_NO_ERROR) {
                SDL_free(DroppedFile);
                DroppedFile = NULL;
                // TODO: Print error msg in a box!
            }
            break;
    }

    //
    // Rendering
    //
    if (SDL_SetRenderDrawColor(MainRenderer(), COLOR_DARK_GREY, 255) != 0) {
        return ERROR_SDL_SET_RENDER_DRAW_COLOR;
    }

    if (SDL_RenderClear(MainRenderer()) != 0) {
        return ERROR_SDL_RENDER_CLEAR;
    }

    // Get the size of the main window
    int width;
    int height;
    SDL_GetWindowSize(MainWindow(), &width, &height);

    // Center and draw the title text
    TitleRect.x = (width - TitleRect.w) / 2;
    TitleRect.y = -50 + (height - TitleRect.h) / 2;

    if (SDL_RenderCopy(MainRenderer(), TitleTexture, NULL, &TitleRect) != 0) {
        return ERROR_SDL_RENDER_COPY;
    }

    // Center and draw the drop text
    DropRect.x = (width - DropRect.w) / 2;
    DropRect.y = 50 + (height - DropRect.h) / 2;

    if (SDL_RenderCopy(MainRenderer(), DropTexture, NULL, &DropRect) != 0) {
        return ERROR_SDL_RENDER_COPY;
    }

    SDL_RenderPresent(MainRenderer());
    return ERROR_NO_ERROR;
}

int Resume(void)
{
    // Prepare for a new file drop
    if (DroppedFile != NULL) {
        SDL_free(DroppedFile);
        DroppedFile = NULL;
    }

    return ERROR_NO_ERROR;
}

// Return the full filename of the dropped files
char* GetDroppedFile(void)
{
    return DroppedFile;
}
