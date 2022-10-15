#ifndef QUIT_H
#define QUIT_H

#include "stdbool.h"

//
// Functions
//
void RequestQuit(void);   // Ask the program to terminate
bool QuitRequested(void); // Return true is program termination has been requested

#endif // QUIT_H
