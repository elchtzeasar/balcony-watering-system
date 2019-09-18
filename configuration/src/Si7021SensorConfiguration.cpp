#include "Si7021SensorConfiguration.h"

#include <cassert>

namespace balcony_watering_system {
namespace configuration {

Si7021SensorConfiguration::Si7021SensorConfiguration() {
}

Si7021SensorConfiguration::~Si7021SensorConfiguration() {
}

void Si7021SensorConfiguration::setField(
    const std::string& fieldName, const std::string& value) {
  if (fieldName == "name") {
    name = value;
  }
  else {
    assert(false && "unknown field");
  }
}

const std::string& Si7021SensorConfiguration::getName() const {
  assert(name != "" && "name must be set");
  return name;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
