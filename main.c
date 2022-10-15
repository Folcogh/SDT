#include "Error.h"
#include "Graphlib.h"
#include "Quit.h"
#include "State.h"
#include "StateWelcome.h"
#include <stdbool.h>
#include <stdio.h>

// Macro printing an error message on exit
#define MSG(err, msg) \
  case err:           \
    message = msg;    \
    break;

int main(int argc, char** argv)
{
    (void)argc, (void)argv;
    int       Error;
    SDL_Event event;

    // Init & main loop
    Error = InitGraphlib();
    if (Error == ERROR_NO_ERROR) {
        Error = PushState(&StateWelcome);
        if (Error == ERROR_NO_ERROR) {
            // Main loop
            while (!QuitRequested()) {
                SDL_WaitEvent(&event);
                CurrentState()->Run(&event);
            }
        }
    }

    // Exit message
    if (Error == ERROR_NO_ERROR) {
        printf("SDT exiting succesfully\n");
    }
    else {
        // Print the error message (program side)
        fprintf(stderr, "*** ERROR ***\n");
        fprintf(stderr, "%s\n", ErrorMessage(Error));

        // Print lib error message if relevant
        if ((Error >= SDL_ERROR) && (Error < TTF_ERROR)) {
            fprintf(stderr, "%s\n", SDL_GetError());
        }
        else if ((Error >= TTF_ERROR) && (Error < OTHER_ERROR)) {
            fprintf(stderr, "%s\n", TTF_GetError());
        }

        // Print exit code
        fprintf(stderr, "\nSDT exiting with code %i\n", Error);
    }

    // Cleanup
    ClearStates();
    ExitGraphlib();
    return Error;
}
