#pragma once

#define RADIOLIB_STATIC_ONLY 1
#include <RadioLib.h>
#include <helpers/radiolib/RadioLibWrappers.h>
#include <PB_C3SuperMiniSX127xBoard.h>
#include <helpers/radiolib/CustomSX1276Wrapper.h>
#include <helpers/AutoDiscoverRTCClock.h>
#include <helpers/SensorManager.h>
#ifdef DISPLAY_CLASS
  #include <helpers/ui/SSD1306Display.h>
  #include <helpers/ui/MomentaryButton.h>
#endif

#ifdef PIN_ONE_WIRE
  class MySensorManager : public SensorManager
  {
  public:
    virtual bool querySensors(uint8_t requester_permissions, CayenneLPP& telemetry);

  protected:
    int oneWireSensorsNumber = 0;
  };
#endif

extern PB_C3SuperMiniSX127xBoard board;
extern WRAPPER_CLASS radio_driver;
extern AutoDiscoverRTCClock rtc_clock;

#ifdef PIN_ONE_WIRE
  extern MySensorManager sensors;
#else
  extern SensorManager sensors;
#endif

#ifdef DISPLAY_CLASS
  extern DISPLAY_CLASS display;
  extern MomentaryButton user_btn;
#endif

bool radio_init();
mesh::LocalIdentity radio_new_identity();
