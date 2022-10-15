#ifndef ERROR_H
#define ERROR_H

// Error ranges
// Error can't be negative
#define SDL_ERROR   1
#define TTF_ERROR   1001
#define OTHER_ERROR 2001

// Error codes
typedef enum {
    // No error
    ERROR_NO_ERROR,

    // SDL errors, starting from 1
    ERROR_SDL_INIT = SDL_ERROR,
    ERROR_SDL_CREATE_WINDOW,
    ERROR_SDL_CREATE_RENDERER,
    ERROR_SDL_CREATE_SURFACE,
    ERROR_SDL_CREATE_TEXTURE,
    ERROR_SDL_RENDER_CLEAR,
    ERROR_SDL_RENDER_COPY,
    ERROR_SDL_RENDER_DRAW_LINES,
    ERROR_SDL_QUERY_TEXTURE,
    ERROR_SDL_SET_RENDER_DRAW_COLOR,
    ERROR_SDL_SET_RENDER_TARGET,
    ERROR_SDL_RENDER_DRAW_RECT,
    ERROR_SDL_RENDER_FILL_RECT,

    // SDL TTF errors, starting form TTF_ERROR
    ERROR_TTF_INIT = TTF_ERROR,
    ERROR_TTF_OPEN_FONT,

    // Other errors, starting from OTHER_ERROR
    ERROR_INVALID_EXTENSION = OTHER_ERROR,
    ERROR_INVALID_FILENAME,
    ERROR_MEMORY,
    ERROR_OPEN_FILE,
    ERROR_FSEEK,
    ERROR_FTELL,
    ERROR_FREAD,
    ERROR_DATA_COUNT
} ERROR_NUMBER;

//
// Functions
//
char* ErrorMessage(int error); // Return the error message associated to the code error

#endif // ERROR_H
