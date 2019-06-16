#include "SoilMoistureSensor.h"

#include <chrono>

namespace balcony_watering_system {
namespace logic {

SoilMoistureSensor::SoilMoistureSensor() {
}

SoilMoistureSensor::~SoilMoistureSensor() {
}

int SoilMoistureSensor::getMoistureLevel() const {
  static auto lastUpdate = std::chrono::steady_clock::now();
  static int level = 0;
  static bool increment = true;

  const auto now = std::chrono::steady_clock::now();
  const auto timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate);
  if (timeSinceLastUpdate > std::chrono::milliseconds(500)) {
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
