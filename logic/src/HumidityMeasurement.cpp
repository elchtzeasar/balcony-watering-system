#include "HumidityMeasurement.h"

#include "IHumiditySensor.h"
#include "IHumidityMeasurementConfiguration.h"

#include <algorithm>

namespace balcony_watering_system {
namespace logic {

using ::balcony_watering_system::configuration::IHumidityMeasurementConfiguration;
using ::balcony_watering_system::hardware::IHumiditySensor;
using ::std::max;
using ::std::string;
using ::std::vector;

HumidityMeasurement::HumidityMeasurement(
    const IHumidityMeasurementConfiguration& configuration,
    const vector<IHumiditySensor*>& sensors) :
  name(configuration.getName()),
  sensors(sensors) {
}

HumidityMeasurement::~HumidityMeasurement() {
}

const string& HumidityMeasurement::getName() const {
  return name;
}

int HumidityMeasurement::getHumidityInPercent() const {
  int percentage = 0;
  for (const auto& sensor : sensors) {
    percentage = max(percentage, sensor->getHumidityInPercent());
  }
  return percentage;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
