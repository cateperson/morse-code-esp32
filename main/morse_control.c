#include "morse_control.h"
#include "freertos/idf_additions.h"
#include <ctype.h>


static int morse_unit_ms = 175;

void set_morse_speed(int speed_ms) {
    morse_unit_ms = speed_ms;
}

int get_morse_speed(void) {
    return morse_unit_ms;
}

void play_morse_text(const char *text, void (*beep_func)(int duration_ms)) {
  printf("Transmitting Morse Code: %s\n", text);

  while (*text) {
    char c = toupper((unsigned char)*text);

    if (c == ' ') {
      vTaskDelay(pdMS_TO_TICKS(morse_unit_ms * 7));
    } else if (c >= 'A' && c <= 'Z') {
      int idx = c - 'A';
      const MorseAction *seq = MORSE_SEQ[idx];

      for (int i = 0; i < MAX_MORSE_LEN; i++) {
        if (seq[i] == ACTION_NONE)
          break;


        if (seq[i] == ACTION_SHORT) {
            if (beep_func) {
                beep_func(morse_unit_ms);
            } else {
                vTaskDelay(pdMS_TO_TICKS(morse_unit_ms));
            }
        } else if (seq[i] == ACTION_LONG) {
            if (beep_func) {
                beep_func(morse_unit_ms * 3);
            } else {
                vTaskDelay(pdMS_TO_TICKS(morse_unit_ms * 3));
            }
        }

        vTaskDelay(pdMS_TO_TICKS(morse_unit_ms)); 
      }
      vTaskDelay(pdMS_TO_TICKS(morse_unit_ms * 2));
    }
    text++;
  }
  printf("Transmission complete.\n");
}
