#pragma once

#include <helpers/ESP32Board.h>

class PB_C3SuperMiniSX127xBoard : public ESP32Board {
public:
  uint32_t getIRQGpio() override {
    return P_LORA_DIO_0; // default for SX1276
  }

#if defined(P_LORA_TX_LED)
  void onBeforeTransmit() override {
    digitalWrite(P_LORA_TX_LED, LOW);   // turn TX LED on, reversed
  }

  void onAfterTransmit() override {
    digitalWrite(P_LORA_TX_LED, HIGH);   // turn TX LED off, reversed
  }
#endif

  const char* getManufacturerName() const override {
    return "ESP32-C3 SuperMini";
  }
};
