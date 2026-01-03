#include "audio_control.h"
#include "driver/dac_continuous.h"
#include "esp_err.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define SAMPLE_RATE 44100
#define PI 3.14159265f

static dac_continuous_handle_t dac_handle;

void dac_init(void) {
    dac_continuous_config_t cont_cfg = {
        .chan_mask = DAC_CHANNEL_MASK_CH0,
        .desc_num = 8,
        .buf_size = 1024,
        .freq_hz = SAMPLE_RATE,
        .offset = 0,
        .clk_src = DAC_DIGI_CLK_SRC_DEFAULT,
        .chan_mode = DAC_CHANNEL_MODE_SIMUL,
    };
    ESP_ERROR_CHECK(dac_continuous_new_channels(&cont_cfg, &dac_handle));
    ESP_ERROR_CHECK(dac_continuous_enable(dac_handle));
}

void play_beep(float freq, int duration_ms) {
    int sample_count = (SAMPLE_RATE * duration_ms) / 1000;
    uint8_t *sample_buf = (uint8_t *)malloc(sample_count);
    if (!sample_buf) {
        printf("Failed to allocate memory for sample buffer\n");
        return;
    }

    for (int i = 0; i < sample_count; i++) {
        float val = sinf(2.0f * PI * freq * i / SAMPLE_RATE);
        sample_buf[i] = (uint8_t)((val + 1.0f) * 127.5f);
    }

    size_t bytes_loaded = 0;
    ESP_ERROR_CHECK(dac_continuous_write(dac_handle, sample_buf, sample_count, &bytes_loaded, -1));
    free(sample_buf);
}

void morse_beep(int duration_ms) {
    play_beep(600.0f, duration_ms);
}

