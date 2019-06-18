#include "SimulationConfiguration.h"

#include <cassert>

namespace balcony_watering_system {
namespace configuration {

SimulationConfiguration::SimulationConfiguration() {
}

SimulationConfiguration::~SimulationConfiguration() {
}

void SimulationConfiguration::setField(const std::string& fieldName, const std::string& value) {
  if (fieldName == "distance-sensor") {
    distanceSensors.push_back(value);
  }
  else if (fieldName == "humidity-sensor") {
    humiditySensors.push_back(value);
  }
  else if (fieldName == "soil-sensor") {
    soilSensors.push_back(value);
  }
  else if (fieldName == "temperature-sensor") {
    temperatureSensors.push_back(value);
  }
  else if (fieldName == "motor") {
    motors.push_back(value);
  }
  else {
    assert(false && "unknown fieldName");
  }
}

const std::vector<std::string>& SimulationConfiguration::getDistanceSensors() const {
  return distanceSensors;
}

const std::vector<std::string>& SimulationConfiguration::getHumiditySensors() const {
  return humiditySensors;
}

const std::vector<std::string>& SimulationConfiguration::getSoilSensors() const {
  return soilSensors;
}

const std::vector<std::string>& SimulationConfiguration::getTemperatureSensors() const {
  return temperatureSensors;
}

const std::vector<std::string>& SimulationConfiguration::getMotors() const {
  return motors;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
