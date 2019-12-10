#include "HumidityMeasurementConfiguration.h"

#include "LexicalCast.h"

#include <cassert>

namespace balcony_watering_system {
namespace configuration {

using ::balcony_watering_system::platform::lexical_cast;
using ::std::string;
using ::std::vector;

HumidityMeasurementConfiguration::HumidityMeasurementConfiguration() : threshold(0), logger("logic.humidity.configuration") {
}

HumidityMeasurementConfiguration::~HumidityMeasurementConfiguration() {
}

void HumidityMeasurementConfiguration::setField(
    const string& fieldName, const string& value) {
  if (fieldName == "name") {
    name = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << " , value=" << value << " => name=" << name);
  }
  else if(fieldName == "threshold") {
    threshold = lexical_cast<int>(value);
    LOG_DEBUG(logger, "fieldName=" << fieldName << " , value=" << value << " => threshold=" << threshold);
  }
  else if(fieldName == "sensor") {
    sensors.push_back(value);
    LOG_DEBUG(logger, "fieldName=" << fieldName << " , value=" << value << " => sensor=" << sensors.back());
  }
  else {
    assert(false && "unknown field");
  }
}

const string& HumidityMeasurementConfiguration::getName() const {
  assert(name != "" && "name must be set");
  return name;
}

int HumidityMeasurementConfiguration::getThreshold() const {
  return threshold;
}

const vector<string>& HumidityMeasurementConfiguration::getSensors() const {
  return sensors;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
