#include "PwmMotorControllerConfiguration.h"

#include "LexicalCast.h"

#include <cassert>

namespace balcony_watering_system {
namespace configuration {

using ::balcony_watering_system::platform::lexical_cast;
using ::std::string;

PwmMotorControllerConfiguration::PwmMotorControllerConfiguration() :
    name(),
    output0Pin(-1),
    output1Pin(-1),
    pwmPin(-1),
    logger("logic.pump.configuration") {
}

PwmMotorControllerConfiguration::~PwmMotorControllerConfiguration() {
}

void PwmMotorControllerConfiguration::setField(
    const string& fieldName, const string& value) {
  if (fieldName == "name") {
    name = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => name=" << name);
  }
  else if (fieldName == "output0") {
    output0Pin = lexical_cast<int>(value);
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => output0Pin=" << output0Pin);
  }
  else if (fieldName == "output1") {
    output1Pin = lexical_cast<int>(value);
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => output1Pin=" << output1Pin);
  }
  else if (fieldName == "pwm") {
    pwmPin = lexical_cast<int>(value);
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => pwmPin=" << pwmPin);
  }
  else {
    assert(false && "unknown field");
  }
}

const std::string& PwmMotorControllerConfiguration::getName() const {
  assert(name != "" && "name must be set");
  return name;
}

int PwmMotorControllerConfiguration::getOutput0Pin() const {
  assert(output0Pin >= 0 && "pin must be set");
  return output0Pin;
}

int PwmMotorControllerConfiguration::getOutput1Pin() const {
  assert(output1Pin >= 0 && "pin must be set");
  return output1Pin;
}

int PwmMotorControllerConfiguration::getPwmPin() const {
  assert(pwmPin >= 0 && "pin must be set");
  return pwmPin;
}


} /* namespace configuration */
} /* namespace balcony_watering_system */
