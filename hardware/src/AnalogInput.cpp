#include "AnalogInput.h"

#include <iostream>

namespace balcony_watering_system {
namespace hardware {

using ::std::string;

AnalogInput::AnalogInput(const string& name, float min, float max) :
    name(name),
    min(min),
    max(max),
    currentVoltage(min) {
}

const std::string& AnalogInput::getName() const {
  return name;
}

float AnalogInput::getMin() const {
  return min;
}

float AnalogInput::getMax() const {
  return max;
}

void AnalogInput::setCurrentVoltage(float voltage) {
  currentVoltage = voltage;
}

float AnalogInput::getCurrentVoltage() const {
  return currentVoltage;
}


} /* namespace hardware */
} /* namespace balcony_watering_system */
