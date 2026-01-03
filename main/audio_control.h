#ifndef AUDIO_CONTROL_H
#define AUDIO_CONTROL_H

#include <stdint.h>


void dac_init(void);
void play_beep(float freq, int duration_ms);
void morse_beep(int duration_ms);


#endif 
