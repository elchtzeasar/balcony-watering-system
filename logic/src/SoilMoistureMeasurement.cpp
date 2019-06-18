#include "SoilMoistureMeasurement.h"

#include "ISoilMoistureSensor.h"
#include "ISoilMoistureMeasurementConfiguration.h"

#include <algorithm>

namespace balcony_watering_system {
namespace logic {

using ::balcony_watering_system::configuration::ISoilMoistureMeasurementConfiguration;
using ::balcony_watering_system::hardware::ISoilMoistureSensor;
using ::std::max;
using ::std::string;
using ::std::vector;

SoilMoistureMeasurement::SoilMoistureMeasurement(
    const ISoilMoistureMeasurementConfiguration& configuration,
    const vector<ISoilMoistureSensor*>& sensors) :
  name(configuration.getName()),
  sensors(sensors) {
}

SoilMoistureMeasurement::~SoilMoistureMeasurement() {
}

const string& SoilMoistureMeasurement::getName() const {
  return name;
}

int SoilMoistureMeasurement::getMoistureInPercent() const {
  int percentage = 0;
  for (const auto& sensor : sensors) {
    percentage = max(percentage, sensor->getMoistureInPercent());
  }
  return percentage;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
