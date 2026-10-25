# MeshCore applications for ESP32-C3 SuperMini & SX127x

Created from template: [MCAppTemplate](https://github.com/fdlamotte/MCAppTemplate).

The applications use [MeshCore](https://github.com/meshcore-dev/MeshCore) as a lib.

## PB_C3SuperMini_SX127x_repeater
It is a 'simple_repeater' application for ESP32-C3 SuperMini board and SX127x radio chip.

## PB_C3SuperMini_SX127x_sensor_1w
It is extended version of 'simple_sensor' application for ESP32-C3 SuperMini board and SX127x radio chip.
It uses 1-Wire bus and DallasTemperature lib for reading temperature sensors.

Channel #1 (```TELEM_CHANNEL_SELF```) is: Built-in MCU Temperature, battery measurements and number of detected 1-Wire sensors (as generic sensor).

Channels #2+ are 1-Wire sensors temperature readings.

## Pin connections

Refer to platformio.ini file section 'PB_C3SuperMini_SX127x'.

| code define | ESP32-C3 SuperMini board | device pin |
|- | - | - |
| P_LORA_DIO_0 | 3 | SX127x - DIO0 |
| P_LORA_DIO_1 | - | unused |
| P_LORA_NSS | 0 | SX127x - NSS |
| P_LORA_RESET | 10 | SX127x - RST |
| P_LORA_SCLK | 4 | SX127x - SCK |
| P_LORA_MISO | 5 | SX127x - MISO |
| P_LORA_MOSI | 6 | SX127x - MOSI |
| P_LORA_TX_LED | 8 | LED on the board; lights up during radio transmission |
| PIN_ONE_WIRE | 1 | 1-Wire / 18B20 Data (PB_C3SuperMini_SX127x_sensor_1w only)|
