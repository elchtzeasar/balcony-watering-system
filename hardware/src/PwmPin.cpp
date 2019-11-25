/*
 *  Created on: Nov 25, 2019
 *      Author: peter
 */

#include "PwmPin.h"

#include <cassert>
#include <pigpio.h>
#include <cmath>

namespace balcony_watering_system {
namespace hardware {

PwmPin::PwmPin(int pin) : pin(pin) {}

void PwmPin::setup() {
  assert(gpioSetMode(pin, PI_ALT2) == 0);
  gpioSetPWMrange(pin, 100);
}

void PwmPin::setValue(float percentage) const {
  gpioPWM(pin, std::round<int>(percentage));
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
