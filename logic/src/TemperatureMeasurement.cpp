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
  sensors(sensors) {
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

} /* namespace logic */
} /* namespace balcony_watering_system */
