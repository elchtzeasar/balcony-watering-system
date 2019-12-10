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
  threshold(configuration.getThreshold()),
  sensors(sensors),
  logger("logic.soil-moisture", name) {
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

bool SoilMoistureMeasurement::readyToWater() const {
  const auto currentMoisture = getMoistureInPercent();

  const bool result = threshold > 0 && currentMoisture < threshold;
  LOG_DEBUG(logger, "readyToWater - threshold=" << threshold << ", currentMoisture=" << currentMoisture << " => return " << result);

  return result;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
