# ESP32 Morse Code Web Server

This project implements a web server on an ESP32 microcontroller that allows users to input text and play it as Morse code. The speed of the Morse code playback is configurable via the web interface.

Diagram from [SunFounders bluetooth audio player guide](https://docs.sunfounder.com/projects/esp32-starter-kit/en/latest/arduino/basic_projects/ar_bluetooth_audio_player.html)
<img width="1177" height="1295" alt="diagram from sunfounders ESP32 Starter kit" src="https://github.com/user-attachments/assets/37559bda-f5ae-4e2c-af4b-3239f7f489c1" />


## Features

*   **Web Interface:** Control the Morse code playback and configuration through a simple web page.
*   **Configurable Speed:** Adjust the WPM (words per minute) for Morse code playback.
*   **Text to Morse:** Converts user-provided text into Morse code signals.

## Getting Started

### Prerequisites

*   [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/index.html) (Espressif IoT Development Framework) installed and configured.
*   An ESP32 development board.

### Building and Flashing

1.  Clone this repository:
    ```bash
    git clone https://github.com/cateperson/morse-code-esp32
    cd morse_code
    ```
2.  Set up ESP-IDF environment variables.
3.  Build the project:
    ```bash
    idf.py build
    ```
4.  Flash the project to your ESP32 board:
    ```bash
    idf.py flash
    ```
5.  Monitor serial output (optional):
    ```bash
    idf.py monitor
    ```

### Usage

1.  After flashing, the ESP32 will attempt to connect to the Wi-Fi network configured in the .env
2.  Once connected, navigate to the IP address displayed on the serial monitor in your web browser.
3.  Use the web interface to input text and adjust the Morse code playback speed.

## Project Structure

*   `main/`: Contains the main application source code.
    *   `main.c`: Main entry point and application logic.
    *   `web_server.c`, `web_server.h`: Web server implementation.
    *   `morse_control.c`, `morse_control.h`: Morse code generation and playback logic.
    *   `wifi_station.c`, `wifi_station.h`: Wi-Fi station mode connectivity.
    *   `config_manager.c`, `config_manager.h`: Handles saving and loading configuration.
    *   `audio_control.c`, `audio_control.h`: Handles audio output for Morse code.

## Configuration

### Wi-Fi Credentials (.env)

This project uses a `.env` file in the project root to configure Wi-Fi credentials.

1.  Copy the example file:
    ```bash
    cp .env.example .env
    ```
2.  Edit `.env` and add your Wi-Fi credentials:
    ```
    WIFI_SSID="your_ssid"
    WIFI_PASS="your_password"
    ```
