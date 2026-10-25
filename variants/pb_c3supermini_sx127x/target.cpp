#include <Arduino.h>
#include "target.h"
#ifdef PIN_ONE_WIRE
  #include <OneWire.h>
  #include <DallasTemperature.h>
#endif

PB_C3SuperMiniSX127xBoard board;

#if defined(P_LORA_SCLK)
  static SPIClass spi(0);
  RADIO_CLASS radio = new Module(P_LORA_NSS, P_LORA_DIO_0, P_LORA_RESET, P_LORA_DIO_1, spi);
#else
  RADIO_CLASS radio = new Module(P_LORA_NSS, P_LORA_DIO_0, P_LORA_RESET, P_LORA_DIO_1);
#endif

WRAPPER_CLASS radio_driver(radio, board);

ESP32RTCClock fallback_clock;
AutoDiscoverRTCClock rtc_clock(fallback_clock);

#ifdef PIN_ONE_WIRE
  OneWire oneWire(PIN_ONE_WIRE);
  DallasTemperature oneWireSensors(&oneWire);
#endif

#ifdef PIN_ONE_WIRE
  bool MySensorManager::querySensors(uint8_t requester_permissions, CayenneLPP& telemetry)
  {
    /* Examples
    telemetry.addTemperature(2, 12.3f); // C
    telemetry.addDistance(2, 12.34f); // m
    telemetry.addGenericSensor(2, 128);
    */

    // read 1Wire thermometers:
    oneWireSensorsNumber = oneWireSensors.getDeviceCount();
    telemetry.addGenericSensor(TELEM_CHANNEL_SELF, oneWireSensorsNumber);

    oneWireSensors.setResolution(12);
    oneWireSensors.requestTemperatures();
    delay(750);

    for (int i = 0; i < oneWireSensorsNumber; i++)
    {
      float tempC = oneWireSensors.getTempCByIndex(0);
      telemetry.addTemperature(TELEM_CHANNEL_SELF + 1 + i, tempC);
    }

    return false; // do not care
  }

  MySensorManager sensors;
#else
  SensorManager sensors;
#endif

#ifdef DISPLAY_CLASS
  DISPLAY_CLASS display;
  MomentaryButton user_btn(PIN_USER_BTN, 1000, true);
#endif

bool radio_init() {
  fallback_clock.begin();
  rtc_clock.begin(Wire);

#ifdef PIN_ONE_WIRE
  oneWireSensors.begin();
#endif

#ifdef P_LORA_TX_LED
  pinMode(P_LORA_TX_LED, OUTPUT);
  digitalWrite(P_LORA_TX_LED, HIGH);
#endif

#if defined(P_LORA_SCLK)
  spi.begin(P_LORA_SCLK, P_LORA_MISO, P_LORA_MOSI);
  return radio.std_init(&spi);
#else
  return radio.std_init();
#endif
}

mesh::LocalIdentity radio_new_identity() {
  RadioNoiseListener rng(radio);
  return mesh::LocalIdentity(&rng);  // create new random identity
}
