#include "State.h"
#include "Error.h"
#include <stdlib.h>

static int     StateCount    = 0;
static int     StateMaxCount = 0;
static STATE** StateList     = NULL;

STATE* CurrentState(void)
{
    int CurrentIndex = StateCount - 1;
    return StateList[CurrentIndex];
}

int PushState(STATE* state)
{
    // Shortcut
    int CurrentIndex = StateCount - 1;

    // Realloc if necessary
    if (StateCount == StateMaxCount) {
        STATE** tmp = realloc(StateList, sizeof(STATE*) * (StateCount + STATE_LIST_INC));
        if (tmp == NULL) {
            return ERROR_MEMORY;
        }

        // Realloc successful
        StateList = tmp;
        StateMaxCount += STATE_LIST_INC;
    }

    // Pause current state if one exists
    if (StateCount != 0) {
        StateList[CurrentIndex]->Pause();
    }

    // Try to construct the new state, else resume the current one
    int Error = state->Constructor();
    if (Error == ERROR_NO_ERROR) {
        CurrentIndex++;
        StateCount++;
        StateList[CurrentIndex] = state;
    }
    else {
        StateList[CurrentIndex]->Resume();
    }

    return Error;
}

void ClearStates(void)
{
    while (StateCount != 0) {
        int CurrentIndex = StateCount - 1;
        StateList[CurrentIndex]->Destructor();
        StateCount--;
    }

    free(StateList);
    StateList = NULL;
}

// Dummy methods, used when a State doesn't need to implement the whole STATE interface
int DummyConstructor(void)
{
    return ERROR_NO_ERROR;
}

void DummyDestructor(void)
{
}

int DummyRun(SDL_Event* event)
{
    (void)event;
    return ERROR_NO_ERROR;
}

int DummyPause(void)
{
    return ERROR_NO_ERROR;
}

int DummyResume(void)
{
    return ERROR_NO_ERROR;
}
