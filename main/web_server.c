#include "web_server.h"
#include "audio_control.h"
#include "config_manager.h"
#include "esp_log.h"
#include "morse_control.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>

static const char *TAG = "web_server";

static esp_err_t root_get_handler(httpd_req_t *req) {
  char *response_buf = malloc(4096);
  if (!response_buf) {
    return ESP_FAIL;
  }

  snprintf(response_buf, 4096,
           "<!DOCTYPE html>"
           "<html>"
           "<head>"
           "<meta name=\"viewport\" content=\"width=device-width, "
           "initial-scale=1\" >"
           "<style>"
           "body { font-family: sans-serif; margin: 20px; }"
           "form { max-width: 400px; padding: 20px; border: 1px solid #ccc; "
           "border-radius: 8px; margin-bottom: 20px; }"
           "input[type=\"text\"], input[type=\"number\"], "
           "input[type=\"submit\"], button {"
           "  width: 100%%;"
           "  padding: 10px;"
           "  margin: 8px 0;"
           "  display: inline-block;"
           "  border: 1px solid #ccc;"
           "  border-radius: 4px;"
           "  box-sizing: border-box;"
           "}"
           "input[type=\"submit\"], button {"
           "  background-color: #4CAF50;"
           "  color: white;"
           "  border: none;"
           "  cursor: pointer;"
           "}"
           "input[type=\"submit\"]:hover, button:hover {"
           "  background-color: #45a049;"
           "}"
           "@media (max-width: 600px) {"
           "  form { width: 90%%; }"
           "}"
           "</style>"
           "</head>"
           "<body>"
           "<h2>Send Morse Code</h2>"
           "<form action=\"/submit\" method=\"GET\">"
           "Input: <input type=\"text\" name=\"text\" pattern=\"[A-Za-z ]*\" "
           "oninput=\"this.value = this.value.replace(/[^A-Za-z ]/g, \'\')\" > "

           "<input type=\"submit\" value=\"Send\" >"
           "</form>"
           "<h2>Settings</h2>"
           "<div style=\"max-width: 400px; padding: 20px; border: 1px solid "
           "#ccc; border-radius: 8px;\">"
           "<label>Speed (ms per unit): <input type=\"number\" "
           "id=\"speedInput\" value=\"%d\"></label>"
           "<button onclick=\"saveConfig()\">Save Settings</button>"
           "</div>"
           "<script>"
           "function saveConfig() {"
           "  var speed = document.getElementById('speedInput').value;"
           "  fetch('/config', {"
           "    method: 'POST',"
           "    headers: {'Content-Type': 'application/json'},"
           "    body: JSON.stringify({speed: parseInt(speed)})"
           "  }).then(resp => { "
           "    if(resp.ok) alert('Saved!');"
           "    else alert('Error');"
           "  });"
           "}"
           "</script>"
           "</body>"
           "</html>",
           get_morse_speed());

  httpd_resp_send(req, response_buf, strlen(response_buf));
  free(response_buf);
  return ESP_OK;
}

static esp_err_t submit_get_handler(httpd_req_t *req) {
  char buf[100];
  size_t buf_len = sizeof(buf);
  char value[50] = "";

  const char *resp = "<!DOCTYPE html>"
                     "<html>"
                     "<head>"
                     "<meta http-equiv=\"refresh\" content=\"5;url=/\" >"
                     "</head>"
                     "<body>"
                     "Text received! Playing as morse code..."
                     "</body>"
                     "</html>";
  httpd_resp_send(req, resp, strlen(resp));
  if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
    if (httpd_query_key_value(buf, "text", value, sizeof(value)) == ESP_OK) {
      ESP_LOGI(TAG, "Received: %s", value);
      play_morse_text(value, morse_beep);
    }
  }
  return ESP_OK;
}

static esp_err_t config_post_handler(httpd_req_t *req) {
  char buf[256];
  int len = httpd_req_recv(req, buf, sizeof(buf) - 1);
  if (len <= 0) {
    if (len == HTTPD_SOCK_ERR_TIMEOUT) {
      httpd_resp_send_408(req);
    }
    return ESP_FAIL;
  }
  buf[len] = 0;

  if (config_save_and_apply(buf)) {
    httpd_resp_sendstr(req, "OK");
    return ESP_OK;
  } else {
    httpd_resp_send_500(req);
    return ESP_FAIL;
  }
}

httpd_handle_t start_webserver(void) {
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  httpd_handle_t server = NULL;

  if (httpd_start(&server, &config) == ESP_OK) {
    httpd_uri_t root = {
        .uri = "/", .method = HTTP_GET, .handler = root_get_handler};
    httpd_register_uri_handler(server, &root);

    httpd_uri_t submit = {
        .uri = "/submit", .method = HTTP_GET, .handler = submit_get_handler};
    httpd_register_uri_handler(server, &submit);

    httpd_uri_t config_post = {
        .uri = "/config", .method = HTTP_POST, .handler = config_post_handler};
    httpd_register_uri_handler(server, &config_post);
  }
  return server;
}
