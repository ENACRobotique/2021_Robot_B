// CLASS DEFINITION
#include "arduino.h"
/*
class FanSpeed {

  public:
    void 
      setup(uint8_t irq_pin, void (*ISR_callback)(void), int value),
      handleInterrupt(void);

  private:
    uint32_t
      _lastMicros = 0UL,
      _interval = 60000000UL;
    void(*ISR_callback)();
};

void FanSpeed::setup(uint8_t irq_pin, void (*ISR_callback)(void), int value)
{
  attachInterrupt(digitalPinToInterrupt(irq_pin), ISR_callback, value);
}

inline void FanSpeed::handleInterrupt(void)
{
  uint32_t nowMicros = micros();
  _interval = nowMicros - _lastMicros;
  _lastMicros = nowMicros;
}



FanSpeed* fan1;
uint8_t fan1pin = 2;


void setup()
{
  fan1 = new FanSpeed();
  fan1->setup(fan1pin, []{fan1->handleInterrupt();}, FALLING);
}

void loop()
{
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 1000UL)
  {
    lastMillis = millis();
  }
}
*/