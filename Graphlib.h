#ifndef GRAPHLIB_H
#define GRAPHLIB_H

#include "SdlWrapper.h"

// Default size for the main window
#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 768

// Font name
#define FONT_NAME "FantasqueSansMono-Regular.ttf"

// Shortcuts for standard colors
#define COLOR_BLACK      0, 0, 0
#define COLOR_DARK_GREY  85, 85, 85
#define COLOR_LIGHT_GREY 170, 170, 170
#define COLOR_WHITE      255, 255, 255

// Pixel format used by the program
#define PIXEL_FORMAT SDL_PIXELFORMAT_RGBA8888

//
// Functions
//
int           InitGraphlib(void);                                                              // Initialize SDL
void          ExitGraphlib(void);                                                              // Initialize SDL_ttf
TTF_Font*     Font(void);                                                                      // Return the font file (for SDL_ttf functions)
SDL_Renderer* MainRenderer(void);                                                              // Return a pointer to the renderer of the main window
SDL_Window*   MainWindow(void);                                                                // Return a pointer to the main window
int           CreateText(SDL_Texture** texture, SDL_Rect* rect, char* text, SDL_Color* color); // Create a texture containing a text with a given color

#endif // GRAPHLIB_H
