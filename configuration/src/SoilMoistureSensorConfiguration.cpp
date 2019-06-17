#include "SoilMoistureSensorConfiguration.h"

#include <cassert>

namespace balcony_watering_system {
namespace configuration {

SoilMoistureSensorConfiguration::SoilMoistureSensorConfiguration() {
}

SoilMoistureSensorConfiguration::~SoilMoistureSensorConfiguration() {
}

void SoilMoistureSensorConfiguration::setField(
    const std::string& fieldName, const std::string& value) {
  if (fieldName == "name") {
    name = value;
  }
  else if(fieldName == "sensor") {
    sensor = value;
  }
  else {
    assert(false && "unknown field");
  }
}

const std::string& SoilMoistureSensorConfiguration::getName() const {
  assert(name != "" && "name must be set");
  return name;
}

const std::string& SoilMoistureSensorConfiguration::getSensor() const {
  assert(sensor != "" && "sensor must be set");
  return sensor;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
