/*
 *  Created on: Nov 25, 2019
 *      Author: peter
 */

#include "InputPin.h"

#include <cassert>
#include <pigpio.h>

namespace balcony_watering_system {
namespace hardware {

InputPin::InputPin(int pin) : pin(pin) {}

void InputPin::setup() {
  assert(gpioSetMode(pin, PI_INPUT) == 0);
}

bool InputPin::getValue() const {
  return gpioRead(pin);
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
