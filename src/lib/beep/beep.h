#ifndef BEEP_H
#define BEEP_H
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif
// Setup beeper, returns true on success
bool beepSetup();
// Destoy beeper, returns true on success
bool beepDestroy();
// Play a frequency, returns true on succcess
bool beepStart(float freq);
// Stop beep, returns true on success
bool beepStop();
#ifdef __cplusplus
}
#endif
#endif
