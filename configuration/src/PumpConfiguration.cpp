#include "PumpConfiguration.h"

#include <cassert>

namespace balcony_watering_system {
namespace configuration {

PumpConfiguration::PumpConfiguration() : logger("logic.pump.configuration") {
}

PumpConfiguration::~PumpConfiguration() {
}

void PumpConfiguration::setField(
    const std::string& fieldName, const std::string& value) {
  if (fieldName == "name") {
    name = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => name=" << name);
  }
  else if (fieldName == "motor") {
    motor = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => motor=" << motor);
  }
  else {
    assert(false && "unknown field");
  }
}

const std::string& PumpConfiguration::getName() const {
  assert(name != "" && "name must be set");
  return name;
}

const std::string& PumpConfiguration::getMotor() const {
  assert(motor != "" && "motor must be set");
  return motor;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
