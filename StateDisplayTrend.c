#include "StateDisplayTrend.h"
#include "Button.h"
#include "Error.h"
#include "Graphlib.h"
#include "MinMax.h"
#include "Quit.h"
#include "StateWelcome.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// StateDisplayTrend object
static int  Constructor(void);
static void Destructor(void);
static int  Run(SDL_Event* event);
STATE       StateDisplayTrend = {STATE_DISPLAY_TREND, Constructor, Destructor, Run, DummyPause, DummyResume};

// Log file parsing
static bool ReadInteger(char** buffer, int* integer);

// Data tables
static SDL_Point RawPoint[DATA_COUNT];
static SDL_Point FilteredPoint[DATA_COUNT];
static SDL_Point ThresholdPoint[DATA_COUNT];

// Rendering
static SDL_Texture* Trend = NULL;
static int          RefreshTrend(void);

// Zoom
#define ZOOM_IN_FACTOR  0.8
#define ZOOM_OUT_FACTOR 1.2

static bool     Panoramic;
static SDL_Rect ViewWindow = {0, 0, DATA_COUNT, VALUE_MAX};
static void     WheelZoom(int factor);

// Functions
int Constructor(void)
{
    char* Filename = GetDroppedFile();

    // Check filename size (just to safely check the extension
    size_t Length = strlen(Filename);
    if (Length <= 4) {
        return ERROR_INVALID_FILENAME;
    }

    // Check extension
    char* End       = Filename + Length - strlen(TREND_FILE_EXTENSION);
    char* Extension = TREND_FILE_EXTENSION;
    for (int i = 0; i < 4; i++, End++) {
        if (tolower(*End) != Extension[i]) {
            return ERROR_INVALID_EXTENSION;
        }
    }

    // Open the file
    FILE* File = fopen(Filename, "r");
    if (File == NULL) {
        return ERROR_OPEN_FILE;
    }

    if (fseek(File, 0, SEEK_END) != 0) {
        fclose(File);
        return ERROR_FSEEK;
    }

    long Size = ftell(File);
    if (Size == -1) {
        fclose(File);
        return ERROR_FTELL;
    }
    rewind(File);

    // Alloc a buffer (Size + 1 to ensure a terminal 0)
    char* Buffer = malloc(Size + 1);
    if (Buffer == NULL) {
        fclose(File);
        return ERROR_MEMORY;
    }

    // Read file content. Size will be modified, because CR/LF will be replaced by LF (Unix EOL)
    Size = fread(Buffer, sizeof(char), Size, File);
    if ((feof(File) == 0) || (ferror(File) != 0)) {
        fclose(File);
        free(Buffer);
        return ERROR_FREAD;
    }
    Buffer[Size] = 0;
    fclose(File);

    // Parse the file
    // Format:
    // - some spaces
    // - integer
    // - SPACE COMMA SPACE
    // - some spaces
    // - integer
    // - anything else
    //
    // It allows notes to be taken anywhere in the file
    // Invalid lines are ignored
    int   TableIndex = 0;     // Index in the integer tables
    int   Integer1;           // Raw data
    int   Integer2;           // Filtered data
    char* OrgBuffer = Buffer; // For free()

    while (*Buffer != 0) {
        // Some spaces
        while (*Buffer == ' ') {
            Buffer++;
        }

        // Integer
        if (ReadInteger(&Buffer, &Integer1)) {
            // SPACE COMMA SPACE
            if (strncmp(Buffer, " , ", 3) == 0) {
                Buffer += 3;

                // Some spaces
                while (*Buffer == ' ') {
                    Buffer++;
                }

                // Integer
                if (ReadInteger(&Buffer, &Integer2)) {
                    if (TableIndex == DATA_COUNT) {
                        fclose(File);
                        return ERROR_DATA_COUNT;
                    }

                    RawPoint[TableIndex].x = TableIndex;
                    RawPoint[TableIndex].y = VALUE_MAX - Integer1;

                    FilteredPoint[TableIndex].x = TableIndex;
                    FilteredPoint[TableIndex].y = VALUE_MAX - Integer2;

                    ThresholdPoint[TableIndex].x = TableIndex;
                    ThresholdPoint[TableIndex].y = VALUE_MAX - (Integer2 + DYNAMIC_THRESHOLD_OFFSET);

                    TableIndex++;
                }
            }
        }

        // Skip line
        while ((*Buffer != 0) && (*Buffer++ != '\n'))
            ;
    }
    free(OrgBuffer);

    // Create trend texture
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    Trend = SDL_CreateTexture(MainRenderer(), PIXEL_FORMAT, SDL_TEXTUREACCESS_TARGET, DATA_COUNT, VALUE_MAX);
    if (Trend == NULL) {
        return ERROR_SDL_CREATE_TEXTURE;
    }

    // Draw in the trend texture
    int Error = RefreshTrend();
    if (Error != ERROR_NO_ERROR) {
        SDL_DestroyTexture(Trend);
        return Error;
    }

    return RefreshTrend();
}

// Read an integer pointed to by buffer
// Return false if there was no integer to read
bool ReadInteger(char** buffer, int* integer)
{
    *integer = 0;
    for (int i = 0;; i++) {
        char Chr = **buffer;
        if ((Chr >= '0') && (Chr <= '9')) {
            *integer = *integer * 10 + (Chr - '0');
            if (*integer > VALUE_MAX) {
                return false;
            }
            (*buffer)++;
        }
        else {
            return i != 0;
        }
    }
}

void Destructor(void)
{
    if (Trend != NULL) {
        SDL_DestroyTexture(Trend);
        Trend = NULL;
    }
}

int Run(SDL_Event* event)
{
    switch (event->type) {
        // X clicked, Alt+F4, ...
        case SDL_QUIT:
            RequestQuit();
            break;

        // The trend must be refreshed (drawn again in its texture) if the renderer size changes or if the screen is locked
        case SDL_RENDER_TARGETS_RESET:
            RefreshTrend();
            break;

        // Wheel zoom in/out
        case SDL_MOUSEWHEEL:
            WheelZoom(event->wheel.y);
            break;

        // Panoramic zoom starts
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_MIDDLE) {
                Panoramic = true;
            }
            break;

        // Panoramic zoom ends
        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_MIDDLE) {
                Panoramic = false;
            }
            break;

        // Panoramic zoom
        case SDL_MOUSEMOTION:
            if (Panoramic == true) {
                ViewWindow.x -= event->motion.xrel;
                ViewWindow.y -= event->motion.yrel;
            }
            break;
    }

    // Prevent excessive zoom out
    ViewWindow.x = max(ViewWindow.x, 0);
    ViewWindow.y = max(ViewWindow.y, 0);
    ViewWindow.w = min(ViewWindow.w, DATA_COUNT);
    ViewWindow.h = min(ViewWindow.h, VALUE_MAX);

    // Prevent excessive zoom in
    ViewWindow.w = max(ViewWindow.w, 5);
    ViewWindow.h = max(ViewWindow.h, 5);

    // Rendering
    if (SDL_RenderCopy(MainRenderer(), Trend, &ViewWindow, NULL) != 0) {
        return ERROR_SDL_RENDER_COPY;
    }

    SDL_RenderPresent(MainRenderer());

    return ERROR_NO_ERROR;
}

int RefreshTrend(void)
{
    // Redirect rendering to trend texture
    if (SDL_SetRenderTarget(MainRenderer(), Trend) != 0) {
        return ERROR_SDL_SET_RENDER_TARGET;
    }

    if (SDL_SetRenderDrawColor(MainRenderer(), COLOR_LIGHT_GREY, 255) != 0) {
        return ERROR_SDL_SET_RENDER_DRAW_COLOR;
    }

    if (SDL_RenderClear(MainRenderer()) != 0) {
        return ERROR_SDL_RENDER_CLEAR;
    }

    // Raw data
    if (SDL_SetRenderDrawColor(MainRenderer(), COLOR_DARK_GREY, 255) != 0) {
        return ERROR_SDL_SET_RENDER_DRAW_COLOR;
    }

    if (SDL_RenderDrawLines(MainRenderer(), RawPoint, DATA_COUNT) != 0) {
        return ERROR_SDL_RENDER_DRAW_LINES;
    }

    // Filtered data
    if (SDL_SetRenderDrawColor(MainRenderer(), COLOR_WHITE, 255) != 0) {
        return ERROR_SDL_SET_RENDER_DRAW_COLOR;
    }

    if (SDL_RenderDrawLines(MainRenderer(), FilteredPoint, DATA_COUNT) != 0) {
        return ERROR_SDL_RENDER_DRAW_LINES;
    }

    // Threshold
    if (SDL_SetRenderDrawColor(MainRenderer(), COLOR_BLACK, 255) != 0) {
        return ERROR_SDL_SET_RENDER_DRAW_COLOR;
    }

    if (SDL_RenderDrawLines(MainRenderer(), ThresholdPoint, DATA_COUNT) != 0) {
        return ERROR_SDL_RENDER_DRAW_LINES;
    }

    // Reset redirection
    if (SDL_SetRenderTarget(MainRenderer(), NULL) != 0) {
        return ERROR_SDL_SET_RENDER_TARGET;
    }

    return ERROR_NO_ERROR;
}

int ZoomReset(void* data)
{
    (void)data;
    return ERROR_NO_ERROR;
}

void WheelZoom(int factor)
{
    // The mouse pointer is the center of the zoom
    int MouseX;
    int MouseY;
    SDL_GetMouseState(&MouseX, &MouseY);

    int NewWidth;
    int NewHeight;
    int WindowWidth;
    int WindowHeight;
    SDL_GetWindowSize(MainWindow(), &WindowWidth, &WindowHeight);
    int OldWidth  = ViewWindow.w;
    int OldHeight = ViewWindow.h;

    for (int i = 0; i < abs(factor); i++) {
        // Zoom in
        if (factor > 0) {
            NewWidth  = OldWidth * ZOOM_IN_FACTOR;
            NewHeight = OldHeight * ZOOM_IN_FACTOR;
        }
        // Zoom out
        else {
            NewWidth  = OldWidth * ZOOM_OUT_FACTOR;
            NewHeight = OldHeight * ZOOM_OUT_FACTOR;
        }

        ViewWindow.x += (OldWidth - NewWidth) * (MouseX / (float)WindowWidth);
        ViewWindow.y += (OldHeight - NewHeight) * (MouseY / (float)WindowHeight);
        ViewWindow.w = NewWidth;
        ViewWindow.h = NewHeight;
    }
}
