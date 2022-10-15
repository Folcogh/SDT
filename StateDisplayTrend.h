#ifndef STATE_DISPLAY_TREND_H
#define STATE_DISPLAY_TREND_H

#include "State.h"

extern STATE StateDisplayTrend;

// Constants
#define TREND_FILE_EXTENSION     ".txt"          // Only TXT files are allowed to be dropped
#define DATA_COUNT               ((1 << 13) - 1) // Number of values in a TMCC dump
#define DATA_COUNT_STR           "8191"          // *** TO BE UPDATED WHEN CHANGING DATA_COUNT ***
#define VALUE_MAX                1000            // Max value recorded by the TMCC
#define DYNAMIC_THRESHOLD_OFFSET 150             // Threshold of a splice detection

#endif // STATE_DISPLAY_TREND_H
