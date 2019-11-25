/*
 * OutputPin.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: peter
 */

#include "OutputPin.h"

#include <cassert>
#include <pigpio.h>

namespace balcony_watering_system {
namespace hardware {

OutputPin::OutputPin(int pin) : pin(pin) {}

void OutputPin::setup() {
  assert(gpioSetMode(pin, PI_OUTPUT) == 0);
}

void OutputPin::setValue(bool value) const {
  gpioWrite(pin, value);
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
