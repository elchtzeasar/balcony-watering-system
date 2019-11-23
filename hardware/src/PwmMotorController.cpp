/*
 * PwmMotorController.cpp
 *
 *  Created on: Nov 19, 2019
 *      Author: peter
 */

#include "PwmMotorController.h"

#include "Master.h"

#include <cassert>
#include <stdio.h>
#include <cmath>

namespace balcony_watering_system {
namespace hardware {

using ::std::string;

PwmMotorController::PwmMotorController(
    const string& name, int output0Pin, int output1Pin, int pwmPin, Master& master) :
    name(name), output0(output0Pin), output1(output1Pin), pwm(pwmPin), currentSpeedInPercent(0), logger("hardware.pwm-motor", name) {

  master.registerWriteNode(*this);

  LOG_INFO(logger, "setting up gpio");
  pwm.setup();
  output0.setup();
  output1.setup();
}

PwmMotorController::~PwmMotorController() {
}

const std::string& PwmMotorController::getName() const {
  return name;
}

void PwmMotorController::runInPercent(int percentage) {
  currentSpeedInPercent = std::max(0, std::min(100, percentage));
  LOG_DEBUG(logger, __FUNCTION__ << "(" << percentage
      << ") => currentSpeedInPercent=" << currentSpeedInPercent);
}

int PwmMotorController::getCurrentSpeedInPercentage() const {
  return currentSpeedInPercent;
}

void PwmMotorController::doControl() const {
  if (currentSpeedInPercent > 0) {
    LOG_DEBUG(logger, __FUNCTION__
        << " - currentSpeedInPercent=" << currentSpeedInPercent
        << " => move");
    pwm.setValue(currentSpeedInPercent);
    output0.setValue(1);
    output1.setValue(0);
  }
  else {
    LOG_DEBUG(logger, __FUNCTION__
        << " - currentSpeedInPercent=" << currentSpeedInPercent
        << " => stop");
    pwm.setValue(0);
    output0.setValue(0);
    output1.setValue(0);
  }
}

void PwmMotorController::doShutdown() const {
  output0.setValue(0);
  output1.setValue(0);
  pwm.setValue(0);
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
