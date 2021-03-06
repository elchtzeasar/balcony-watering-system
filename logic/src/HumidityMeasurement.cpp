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
  threshold(configuration.getThreshold()),
  sensors(sensors),
  logger("logic.humidity", name) {
}

HumidityMeasurement::~HumidityMeasurement() {
}

const string& HumidityMeasurement::getName() const {
  return name;
}

float HumidityMeasurement::getHumidityInPercent() const {
  float percentage = 0;
  for (const auto& sensor : sensors) {
    percentage = max(percentage, sensor->getHumidityInPercent());
  }
  return percentage;
}

bool HumidityMeasurement::readyToWater() const {
  const auto humidity = getHumidityInPercent();

  const bool result = threshold > 0 && humidity > threshold;
  LOG_DEBUG(logger, "readyToWater - threshold=" << threshold << ", humidity=" << humidity << " => return " << result);

  return result;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
