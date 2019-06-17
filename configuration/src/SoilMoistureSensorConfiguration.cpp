#include "SoilMoistureSensorConfiguration.h"

namespace balcony_watering_system {
namespace configuration {

SoilMoistureSensorConfiguration::SoilMoistureSensorConfiguration() {
}

SoilMoistureSensorConfiguration::~SoilMoistureSensorConfiguration() {
}

IConfiguration::Type SoilMoistureSensorConfiguration::getType() const {
  return IConfiguration::Type::SOIL_MOISTURE_SENSOR;
}

void SoilMoistureSensorConfiguration::setField(
    const std::string& fieldName, const std::string& value) {
  if (fieldName == "name") {
    name = value;
  }
}

const std::string& SoilMoistureSensorConfiguration::getName() const {
  return name;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
