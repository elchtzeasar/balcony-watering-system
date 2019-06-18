#include "TemperatureMeasurementConfiguration.h"

#include <cassert>

namespace balcony_watering_system {
namespace configuration {

using ::std::string;
using ::std::vector;

TemperatureMeasurementConfiguration::TemperatureMeasurementConfiguration() {
}

TemperatureMeasurementConfiguration::~TemperatureMeasurementConfiguration() {
}

void TemperatureMeasurementConfiguration::setField(
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

const string& TemperatureMeasurementConfiguration::getName() const {
  assert(name != "" && "name must be set");
  return name;
}

const vector<string>& TemperatureMeasurementConfiguration::getSensors() const {
  return sensors;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
