#include "SoilMoistureMeasurementConfiguration.h"

#include <cassert>

namespace balcony_watering_system {
namespace configuration {

using ::std::string;
using ::std::vector;

SoilMoistureMeasurementConfiguration::SoilMoistureMeasurementConfiguration() {
}

SoilMoistureMeasurementConfiguration::~SoilMoistureMeasurementConfiguration() {
}

void SoilMoistureMeasurementConfiguration::setField(
    const string& fieldName, const string& value) {
  if (fieldName == "name") {
    name = value;
  }
  else if(fieldName == "sensor") {
    sensors.push_back(value);
  }
  else {
    assert(false && "unknown field");
  }
}

const string& SoilMoistureMeasurementConfiguration::getName() const {
  assert(name != "" && "name must be set");
  return name;
}

const vector<string>& SoilMoistureMeasurementConfiguration::getSensors() const {
  return sensors;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
