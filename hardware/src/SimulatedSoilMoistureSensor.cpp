#include "SimulatedSoilMoistureSensor.h"

#include "Master.h"

#include <random>

namespace balcony_watering_system {
namespace hardware {

using ::std::chrono::duration_cast;
using ::std::chrono::milliseconds;
using ::std::chrono::steady_clock;
using ::std::string;

SimulatedSoilMoistureSensor::SimulatedSoilMoistureSensor(
    const string& name, Master& master) :
  name(name),
  currentLevel(0),
  increment(true),
  lastUpdate(steady_clock::now()) {
  master.registerReadNode(*this);

  static std::random_device rd;
  currentLevel = rd() % 100;
  increment = rd() % 5 - 3;
}

SimulatedSoilMoistureSensor::~SimulatedSoilMoistureSensor() {
}

const string& SimulatedSoilMoistureSensor::getName() const {
  return name;
}

void SimulatedSoilMoistureSensor::doSample() {
  const auto now = steady_clock::now();
  const auto timeSinceLastUpdate = duration_cast<milliseconds>(now - lastUpdate);
  if (timeSinceLastUpdate > milliseconds(500)) {
    currentLevel += increment;
  }

  if (currentLevel > 100) {
    currentLevel = 100;
    increment *= -1;
  }
  else if (currentLevel < 0) {
    currentLevel = 0;
    increment *= -1;
  }
}

int SimulatedSoilMoistureSensor::getMoistureInPercent() const {
  return currentLevel;
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
