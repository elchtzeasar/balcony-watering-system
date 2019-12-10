#include "TemperatureMeasurement.h"

#include "ITemperatureSensor.h"
#include "ITemperatureMeasurementConfiguration.h"

#include <algorithm>

namespace balcony_watering_system {
namespace logic {

using ::balcony_watering_system::configuration::ITemperatureMeasurementConfiguration;
using ::balcony_watering_system::hardware::ITemperatureSensor;
using ::std::max;
using ::std::min;
using ::std::string;
using ::std::vector;

TemperatureMeasurement::TemperatureMeasurement(
    const ITemperatureMeasurementConfiguration& configuration,
    const vector<ITemperatureSensor*>& sensors) :
  name(configuration.getName()),
  threshold(configuration.getThreshold()),
  sensors(sensors),
  logger("logic.temperature", name) {
}

TemperatureMeasurement::~TemperatureMeasurement() {
}

const string& TemperatureMeasurement::getName() const {
  return name;
}

float TemperatureMeasurement::getMin() const {
  return 0;
}

float TemperatureMeasurement::getMax() const {
  return 40;
}

float TemperatureMeasurement::getTemperatureInDegrees() const {
  float temperature = 0;
  for (const auto& sensor : sensors) {
    temperature = max(temperature, sensor->getTemperatureInDegrees());
  }

  temperature = min(temperature, getMax());
  temperature = max(temperature, getMin());

  return temperature;
}

bool TemperatureMeasurement::readyToWater() const {
  const auto currentTemperature = getTemperatureInDegrees();

  const bool result = threshold > 0 && 0 < currentTemperature && currentTemperature < threshold;
  LOG_DEBUG(logger, "readyToWater - threshold=" << threshold << ", currentTemperature=" << currentTemperature << " => return " << result);

  return result;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
