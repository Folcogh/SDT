#include "Error.h"
#include "StateDisplayTrend.h"

// The ERROR structure and table are internal (private)
typedef struct {
    int   number;  // Error code
    char* message; // Error message
} ERROR;

#define UNKNOWN_ERROR -1 // End of table marker

static ERROR Error[] = {
  // No error
  {ERROR_NO_ERROR,                  "No error registered"                                         },

 // SDL
  {ERROR_SDL_INIT,                  "Cannot initialize SDL"                                       },
  {ERROR_SDL_CREATE_WINDOW,         "Cannot create the SDL window"                                },
  {ERROR_SDL_CREATE_RENDERER,       "Cannot create the window renderer"                           },
  {ERROR_SDL_CREATE_SURFACE,        "Cannot create a SDL Surface"                                 },
  {ERROR_SDL_CREATE_TEXTURE,        "Cannot create a SDL Texture"                                 },
  {ERROR_SDL_RENDER_CLEAR,          "Cannot clear the renderer"                                   },
  {ERROR_SDL_RENDER_COPY,           "Cannot copy to the renderer"                                 },
  {ERROR_SDL_RENDER_DRAW_LINES,     "Cannot draw lines on the renderer"                           },
  {ERROR_SDL_QUERY_TEXTURE,         "Cannot quesry a texture"                                     },
  {ERROR_SDL_SET_RENDER_DRAW_COLOR, "Cannot set the renderer color"                               },
  {ERROR_SDL_SET_RENDER_TARGET,     "Cannot set the render target"                                },
  {ERROR_SDL_RENDER_DRAW_RECT,      "Cannot draw a rect on the renderer"                          },
  {ERROR_SDL_RENDER_FILL_RECT,      "Cannot fill a rect on the renderer"                          },

 // TTF
  {ERROR_TTF_INIT,                  "Cannot initialize SDL_ttf"                                   },
  {ERROR_TTF_OPEN_FONT,             "Cannot open the font file"                                   },

 // Other
  {ERROR_INVALID_EXTENSION,         "Invalid file extension (must be '.txt')"                     },
  {ERROR_INVALID_FILENAME,          "Invalid filename"                                            },
  {ERROR_MEMORY,                    "Memory error (re/allocation)"                                },
  {ERROR_OPEN_FILE,                 "Cannot open file"                                            },
  {ERROR_FSEEK,                     "Fseek failed (error when reading file)"                      },
  {ERROR_FTELL,                     "Ftell failed (error when reading file)"                      },
  {ERROR_FREAD,                     "Fread failed (error when reading file)"                      },
  {ERROR_DATA_COUNT,                "Too many entries in the log file (max is " DATA_COUNT_STR ")"},

 // END OF TABLE
  {UNKNOWN_ERROR,                   "Unknown error"                                               }
};

//  ErrorMessage
//
// Return the string associated to the code error
//
char* ErrorMessage(int error)
{
    int i;
    for (i = 0; Error[i].number != UNKNOWN_ERROR; i++) {
        if (Error[i].number == error) {
            return Error[i].message; // Known error
        }
    }
    return Error[i].message; // Unknown error
}
