<<<<<<< HEAD
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
=======
| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C5 | ESP32-C6 | ESP32-C61 | ESP32-H2 | ESP32-H21 | ESP32-H4 | ESP32-P4 | ESP32-S2 | ESP32-S3 | ESP32-S31 | Linux |
| ----------------- | ----- | -------- | -------- | -------- | -------- | --------- | -------- | --------- | -------- | -------- | -------- | -------- | --------- | ----- |

# Hello World Example

Starts a FreeRTOS task to print "Hello World".

(See the README.md file in the upper level 'examples' directory for more information about examples.)

## How to use example

Follow detailed instructions provided specifically for this example.

Select the instructions depending on Espressif chip installed on your development board:

- [ESP32 Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/stable/get-started/index.html)
- [ESP32-S2 Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/get-started/index.html)


## Example folder contents

The project **hello_world** contains one source file in C language [hello_world_main.c](main/hello_world_main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files that provide set of directives and instructions describing the project's source files and targets (executable, library, or both).

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── pytest_hello_world.py      Python script used for automated testing
├── main
│   ├── CMakeLists.txt
│   └── hello_world_main.c
└── README.md                  This is the file you are currently reading
```

For more information on structure and contents of ESP-IDF projects, please refer to Section [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) of the ESP-IDF Programming Guide.

## Troubleshooting

* Program upload failure

    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs.
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.

## Technical support and feedback

Please use the following feedback channels:

* For technical queries, go to the [esp32.com](https://esp32.com/) forum
* For a feature request or bug report, create a [GitHub issue](https://github.com/espressif/esp-idf/issues)

We will get back to you as soon as possible.
>>>>>>> 1125d31 (code)
