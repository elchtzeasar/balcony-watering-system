#include "GroveSoilMoistureSensorConfiguration.h"

#include <cassert>
#include <sstream>

namespace balcony_watering_system {
namespace configuration {

using ::std::istringstream;

GroveSoilMoistureSensorConfiguration::GroveSoilMoistureSensorConfiguration() :
    name(), inputName(), waterVoltage(-1), dryVoltage(-1), logger("hardware.soil-moisture.grove.configuration") {
}

GroveSoilMoistureSensorConfiguration::~GroveSoilMoistureSensorConfiguration() {
}

void GroveSoilMoistureSensorConfiguration::setField(
    const std::string& fieldName, const std::string& value) {
  if (fieldName == "name") {
    name = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => name=" << name);
  }
  else if (fieldName == "input-name") {
    inputName = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => inputName=" << inputName);
  }
  else if (fieldName == "water-voltage") {
    istringstream stream;
    stream.str(value);
    stream >> waterVoltage;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => waterVoltage=" << waterVoltage);
  }
  else if (fieldName == "dry-voltage") {
    istringstream stream;
    stream.str(value);
    stream >> dryVoltage;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => dryVoltage=" << dryVoltage);
  }
  else {
    assert(false && "unknown field");
  }
}

const std::string& GroveSoilMoistureSensorConfiguration::getName() const {
  assert(name != "" && "name must be set");
  return name;
}

const std::string& GroveSoilMoistureSensorConfiguration::getInputName() const {
  assert(inputName != "" && "inputName must be set");
  return inputName;
}

float GroveSoilMoistureSensorConfiguration::getWaterVoltage() const {
  assert(waterVoltage >= 0.0 && "waterVoltage must be set");
  return waterVoltage;
}

float GroveSoilMoistureSensorConfiguration::getDryVoltage() const {
  assert(dryVoltage >= 0.0 && "dryVoltage must be set");
  return dryVoltage;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
