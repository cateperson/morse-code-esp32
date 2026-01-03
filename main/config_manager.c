#include "config_manager.h"
#include "cJSON.h"
#include "esp_log.h"
#include "morse_control.h"
#include <stdio.h>

static const char *TAG = "config_manager";

void config_load(void) {
    FILE *f = fopen("/fs/config.json", "r");
    if (f == NULL) {
        ESP_LOGI(TAG, "No config file found, using defaults");
        return;
    }
    char buf[1024];
    size_t len = fread(buf, 1, sizeof(buf) - 1, f);
    fclose(f);
    buf[len] = 0;

    cJSON *json = cJSON_Parse(buf);
    if (json) {
        cJSON *speed = cJSON_GetObjectItem(json, "speed");
        if (cJSON_IsNumber(speed)) {
            set_morse_speed(speed->valueint);
            ESP_LOGI(TAG, "Loaded speed: %d", speed->valueint);
        }
        cJSON_Delete(json);
    } else {
        ESP_LOGI(TAG, "Failed to parse config.json");
    }
}

bool config_save_and_apply(const char *json_str) {
    FILE *f = fopen("/fs/config.json", "w");
    if (f) {
        fprintf(f, "%s", json_str);
        fclose(f);
        ESP_LOGI(TAG, "Saved config: %s", json_str);
    } else {
        ESP_LOGE(TAG, "Failed to open config.json for writing");
        return false;
    }

    cJSON *json = cJSON_Parse(json_str);
    if (json) {
        cJSON *speed = cJSON_GetObjectItem(json, "speed");
        if (cJSON_IsNumber(speed)) {
            set_morse_speed(speed->valueint);
        }
        cJSON_Delete(json);
        return true;
    }
    return false;
}
