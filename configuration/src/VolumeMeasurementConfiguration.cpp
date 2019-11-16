#include "VolumeMeasurementConfiguration.h"

#include <cassert>
#include <cmath>
#include <sstream>

namespace balcony_watering_system {
namespace configuration {

using ::std::istringstream;
using ::std::string;
using ::std::vector;

VolumeMeasurementConfiguration::VolumeMeasurementConfiguration() :
  name(),
  sensor(),
  areaInSquareMeters(0),
  logger("logic.volume-measurement.configuration") {
}

VolumeMeasurementConfiguration::~VolumeMeasurementConfiguration() {
}

void VolumeMeasurementConfiguration::setField(
    const string& fieldName, const string& value) {
  if (fieldName == "name") {
    name = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => name=" << name);
  }
  else if(fieldName == "sensor") {
    sensor = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => sensor=" << sensor);
  }
  else if(fieldName == "area-in-m2") {
    istringstream stream;
    stream.str(value);
    stream >> areaInSquareMeters;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => areaInSquareMeters=" << areaInSquareMeters);
  }
  else {
    assert(false && "unknown field");
  }
}

const string& VolumeMeasurementConfiguration::getName() const {
  assert(name != "" && "name must be set");
  return name;
}

const string& VolumeMeasurementConfiguration::getSensor() const {
  assert(sensor != "" && "sensor must be set");
  return sensor;
}

double VolumeMeasurementConfiguration::getAreaInSquareMeters() const {
  assert(areaInSquareMeters > 0.1&& "areaInSquareMeters must be set");
  return areaInSquareMeters;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
