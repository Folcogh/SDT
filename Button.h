#ifndef BUTTON_H
#define BUTTON_H

#include "SdlWrapper.h"
#include <stdbool.h>

// Theme data...
#define WIDTH_OVERHEAD  40
#define HEIGHT_OVERHEAD 40

// Directions for buttons cascade
#define CASCADE_HORIZONTAL       0
#define CASCADE_VERTICAL         1
#define CASCADE_VERTICAL_ALIGNED 2

// Callback
typedef int (*OnClick_t)(void* data);

// Opaque type
typedef struct BUTTON BUTTON;

int  CreateButton(BUTTON** button, char* text, OnClick_t callback, void* data);
void DestroyButton(BUTTON* button);
int  DrawButton(BUTTON* button);
void SetPosition(BUTTON* button, int x, int y);
void CascadeButtons(int direction, int x, int y, BUTTON* button, ...);

#endif // BUTTON_H
