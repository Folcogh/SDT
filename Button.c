#include "Button.h"
#include "Error.h"
#include "Graphlib.h"
#include "MinMax.h"
#include <stdarg.h>

// Private data type
typedef struct BUTTON {
    SDL_Texture* TextTexture;
    SDL_Rect     ButtonPosition;
    SDL_Rect     TextPosition;
    bool         Visible;
    bool         Enabled;
    OnClick_t    Callback;
    void*        CallbackData;
} BUTTON;

// Cascade offset
#define CASCADE_OFFSET_X 10
#define CASCADE_OFFSET_Y 10

static SDL_Color TextColor = {COLOR_DARK_GREY, 255};

static int CreateButtonFailed(int error, BUTTON* button, SDL_Texture* texture)
{
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
    }

    if (button != NULL) {
        free(button);
    }

    return error;
}

int CreateButton(BUTTON** button, char* text, OnClick_t callback, void* data)
{
    *button                  = NULL; // Make user's life easier
    SDL_Texture* TextTexture = NULL;

    // Allocate the button
    BUTTON* Button = malloc(sizeof(BUTTON));
    if (Button == NULL) {
        return ERROR_MEMORY;
    }

    // Basic initialization
    Button->Callback         = callback;
    Button->CallbackData     = data;
    Button->Visible          = true;
    Button->Enabled          = true;
    Button->ButtonPosition.x = 0;
    Button->ButtonPosition.y = 0;

    // Create the text texture
    int Error = CreateText(&TextTexture, &Button->ButtonPosition, text, &TextColor) != ERROR_NO_ERROR;
    if (Error != ERROR_NO_ERROR) {
        return CreateButtonFailed(Error, Button, TextTexture);
    }

    // Get the size of the text
    int Width;
    int Height;
    if (SDL_QueryTexture(TextTexture, NULL, NULL, &Width, &Height) != 0) {
        return CreateButtonFailed(ERROR_SDL_QUERY_TEXTURE, Button, TextTexture);
    }

    // Set text position in the button texture
    Button->TextPosition.w = Width;
    Button->TextPosition.h = Height;
    Button->TextPosition.x = WIDTH_OVERHEAD / 2;
    Button->TextPosition.y = HEIGHT_OVERHEAD / 2;

    // Update button size
    Width += WIDTH_OVERHEAD;
    Height += HEIGHT_OVERHEAD;
    Button->ButtonPosition.w = Width;
    Button->ButtonPosition.h = Height;

    // Finalize
    Button->TextTexture = TextTexture;
    *button             = Button;

    return ERROR_NO_ERROR;
}

void DestroyButton(BUTTON* button)
{
    if (button != NULL) {
        SDL_DestroyTexture(button->TextTexture);
        free(button);
    }
}

int DrawButton(BUTTON* button)
{
    if (button->Visible) {
        // Background is white
        if (SDL_SetRenderDrawColor(MainRenderer(), COLOR_WHITE, 255) != 0) {
            return ERROR_SDL_SET_RENDER_DRAW_COLOR;
        }

        if (SDL_RenderFillRect(MainRenderer(), &button->ButtonPosition) != 0) {
            return ERROR_SDL_RENDER_FILL_RECT;
        }

        // Draw frame in black
        if (SDL_SetRenderDrawColor(MainRenderer(), COLOR_BLACK, 255) != 0) {
            return ERROR_SDL_SET_RENDER_DRAW_COLOR;
        }

        if (SDL_RenderDrawRect(MainRenderer(), &button->ButtonPosition) != 0) {
            return ERROR_SDL_RENDER_DRAW_RECT;
        }

        // Draw the text
        if (SDL_RenderCopy(MainRenderer(), button->TextTexture, NULL, &button->TextPosition) != 0) {
            return ERROR_SDL_RENDER_COPY;
        }
    }

    return ERROR_NO_ERROR;
}

void SetPosition(BUTTON* button, int x, int y)
{
    button->ButtonPosition.x = x;
    button->ButtonPosition.y = y;
    button->TextPosition.x   = button->ButtonPosition.x + WIDTH_OVERHEAD / 2;
    button->TextPosition.y   = button->ButtonPosition.y + HEIGHT_OVERHEAD / 2;
}

void CascadeButtons(int direction, int x, int y, BUTTON* button, ...)
{
    int WidthMax = 0; // For CASCADE_VERTICAL_ALIGNED
    int i        = 0; // Counter

    do {
        BUTTON* Button = (&button)[i];
        SetPosition(Button, x, y);

        if (direction == CASCADE_HORIZONTAL) {
            x += Button->ButtonPosition.w + CASCADE_OFFSET_X;
        }
        else { // CASCADE_VERTICAL || CASCADE_VERTICAL_ALIGNED
            y += Button->ButtonPosition.h + CASCADE_OFFSET_Y;
        }

        WidthMax = max(Button->ButtonPosition.w, WidthMax);
    } while ((&button)[++i] != NULL);

    // For CASCADE_VERTICAL_ALIGNED
    // Set the same width for all the boxes and center the text
    if (direction == CASCADE_VERTICAL_ALIGNED) {
        do {
            BUTTON* Button = (&button)[--i];
            // Make boxes equal
            Button->ButtonPosition.w = WidthMax;

            // Center text
            Button->TextPosition.x = Button->ButtonPosition.x + (Button->ButtonPosition.w - Button->TextPosition.w) / 2;
        } while (i > 0);
    }
}
