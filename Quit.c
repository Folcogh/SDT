#include "Quit.h"
#include "stdbool.h"

static bool MustQuit = false;

void RequestQuit(void)
{
    MustQuit = true;
}

bool QuitRequested(void)
{
    return MustQuit;
}
