#include "SoilMoistureSensor.h"

namespace balcony_watering_system {
namespace logic {

SoilMoistureSensor::SoilMoistureSensor() {
}

SoilMoistureSensor::~SoilMoistureSensor() {
}

int SoilMoistureSensor::getMoistureLevel() const {
  static int level = 0;
  static int wait = 0;
  static bool increment = true;

  if (++wait > 1000) {
    wait = 0;
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
