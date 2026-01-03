#include "esp_chip_info.h"
#include "esp_event.h"
#include "esp_flash.h"
#include "esp_littlefs.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "portmacro.h"
#include "sdkconfig.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "audio_control.h"
#include "morse_control.h"
#include "web_server.h"
#include "wifi_station.h"
#include "config_manager.h"

void littlefs_init(void) {
  esp_vfs_littlefs_conf_t conf = {
      .base_path = "/fs",
      .partition_label = "littlefs",
      .format_if_mount_failed = true,
      .dont_mount = false,
  };

  esp_err_t ret = esp_vfs_littlefs_register(&conf);
  if (ret != ESP_OK) {
    printf("Error: couldnt mount file system");
    esp_restart();
  }
}

void app_main(void) {
  nvs_flash_init();
  littlefs_init();
  config_load();
  wifi_init_sta();
  dac_init();
  start_webserver();
}
