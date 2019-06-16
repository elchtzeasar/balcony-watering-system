#include "SoilMoistureSensor.h"

#include <chrono>

namespace balcony_watering_system {
namespace logic {

using ::std::chrono::duration_cast;
using ::std::chrono::milliseconds;
using ::std::chrono::steady_clock;

SoilMoistureSensor::SoilMoistureSensor() {
}

SoilMoistureSensor::~SoilMoistureSensor() {
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
