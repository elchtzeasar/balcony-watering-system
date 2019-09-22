#include "SimulatedTemperatureSensor.h"

#include "Master.h"

#include <random>

namespace balcony_watering_system {
namespace hardware {

using ::std::chrono::duration_cast;
using ::std::chrono::milliseconds;
using ::std::chrono::steady_clock;
using ::std::string;

SimulatedTemperatureSensor::SimulatedTemperatureSensor(
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

SimulatedTemperatureSensor::~SimulatedTemperatureSensor() {
}

const string& SimulatedTemperatureSensor::getName() const {
  return name;
}
void SimulatedTemperatureSensor::doSample() {
  const auto now = steady_clock::now();
  const auto timeSinceLastUpdate = duration_cast<milliseconds>(now - lastUpdate);
  if (timeSinceLastUpdate > milliseconds(500)) {
    currentLevel += increment;
  }

  if (currentLevel > getMax()) {
    currentLevel = getMax();
    increment *= -1;
  }
  else if (currentLevel < getMin()) {
    currentLevel = getMin();
    increment *= -1;
  }
}

float SimulatedTemperatureSensor::getMin() const {
  return 0;
}

float SimulatedTemperatureSensor::getMax() const {
  return 100;
}

float SimulatedTemperatureSensor::getTemperatureInDegrees() const {
  return currentLevel;
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
