#include "SoilMoistureSensor.h"

#include "ISoilMoistureSensorConfiguration.h"

#include <chrono>

namespace balcony_watering_system {
namespace logic {

using ::balcony_watering_system::configuration::ISoilMoistureSensorConfiguration;
using ::std::chrono::duration_cast;
using ::std::chrono::milliseconds;
using ::std::chrono::steady_clock;
using ::std::string;

SoilMoistureSensor::SoilMoistureSensor(const ISoilMoistureSensorConfiguration& configuration) :
  name(configuration.getName()) {
}

SoilMoistureSensor::~SoilMoistureSensor() {
}

const string& SoilMoistureSensor::getName() const {
  return name;
}

int SoilMoistureSensor::getMoistureLevel() const {
  static auto lastUpdate = steady_clock::now();
  static int level = 0;
  static bool increment = true;

  const auto now = steady_clock::now();
  const auto timeSinceLastUpdate = duration_cast<milliseconds>(now - lastUpdate);
  if (timeSinceLastUpdate > milliseconds(500)) {
    if (increment)
      level++;
    else
      level--;
  }

  if (level > 100) {
    level = 100;
    increment = false;
  }
  else if (level < 0) {
    level = 0;
    increment = true;
  }

  return level;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
