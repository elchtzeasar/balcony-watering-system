#include "PumpConfiguration.h"

namespace balcony_watering_system {
namespace configuration {

PumpConfiguration::PumpConfiguration() {
}

PumpConfiguration::~PumpConfiguration() {
}

IConfiguration::Type PumpConfiguration::getType() const {
  return IConfiguration::Type::SOIL_MOISTURE_SENSOR;
}

void PumpConfiguration::setField(
    const std::string& fieldName, const std::string& value) {
  if (fieldName == "name") {
    name = value;
  }
}

const std::string& PumpConfiguration::getName() const {
  return name;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
