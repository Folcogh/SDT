#ifndef STATE_H
#define STATE_H

#include "SdlWrapper.h"
#include <stdbool.h>

// Constants
#define STATE_LIST_INC 10 // Number of state locations created when the stack is full

// States ID
#define STATE_UNDEFINED     0
#define STATE_WELCOME       1
#define STATE_DISPLAY_TREND 2

// STATE structure prototypes
typedef int (*constructor_t)(void);
typedef void (*destructor_t)(void);
typedef int (*run_t)(SDL_Event* event);
typedef int (*pause_t)(void);
typedef int (*resume_t)(void);

typedef struct STATE {
    int           StateID;     // Probably useless, debugging purpose
    constructor_t Constructor; // Called when the state is created
    destructor_t  Destructor;  // Called when the state is destroyed
    run_t         Run;         // Called once at every loop of the event loop
    pause_t       Pause;       // Called when a new state is pushed
    resume_t      Resume;      // Called when the state has ben paused and becomes the new current state
} STATE;

//
// Functions
//
int    PushState(STATE* state); // Create and push a new state on the stack. Pause the current one
void   ClearStates(void);       // Pop and delete all states
STATE* CurrentState(void);      // Return a pointer to the current state

//
// Dummy functions which implement the STATE interface, allowing a state to partially implement the interface
//
int  DummyConstructor(void);
void DummyDestructor(void);
int  DummyRun(SDL_Event* event);
int  DummyPause(void);
int  DummyResume(void);

#endif // STATE_H
