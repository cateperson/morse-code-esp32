idf_component_register(SRCS "main.c" "morse_control.c" "audio_control.c" "web_server.c" "wifi_station.c" "config_manager.c"
                       PRIV_REQUIRES spi_flash
                       INCLUDE_DIRS ""
                       PRIV_REQUIRES esp_driver_gpio
                       PRIV_REQUIRES esp_driver_dac
                       PRIV_REQUIRES esp_http_server
                       PRIV_REQUIRES esp_event
                       PRIV_REQUIRES esp_netif
                       PRIV_REQUIRES esp_wifi
                       PRIV_REQUIRES nvs_flash
                       PRIV_REQUIRES littlefs
                       PRIV_REQUIRES cjson)

# Helper to load env vars
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../.env")
    file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/../.env" ConfigContents)
    foreach(line ${ConfigContents})
        if(line MATCHES "^[ \t]*([^#=]+)[ \t]*=[ \t]*(.*)$")
            string(REGEX REPLACE "^[ \t]*([^#=]+)[ \t]*=[ \t]*(.*)$" "\\1" KEY "${line}")
            string(REGEX REPLACE "^[ \t]*([^#=]+)[ \t]*=[ \t]*(.*)$" "\\2" VALUE "${line}")
            
            # Remove surrounding quotes
            string(REGEX REPLACE "^[\"'](.*)[\"']$" "\\1" VALUE "${VALUE}")
            
            # Pass to component, escaping quotes for C string literal
            target_compile_definitions(${COMPONENT_LIB} PRIVATE ${KEY}="${VALUE}")
        endif()
    endforeach()
else()
    message(WARNING ".env file not found in project root")
endif()

