#include "HWFactory.h"

#include "ConfigurationFile.h"
#include "ISimulationConfiguration.h"
#include "SimulatedMotor.h"
#include "SimulatedDistanceSensor.h"
#include "SimulatedHumiditySensor.h"
#include "SimulatedSoilMoistureSensor.h"
#include "SimulatedTemperatureSensor.h"

#include <cassert>

namespace balcony_watering_system {
namespace hardware {

using ::balcony_watering_system::configuration::ConfigurationFile;

HWFactory::HWFactory(const ConfigurationFile& configurationFile,
                     Master& master) :
  configurationFile(configurationFile),
  master(master),
  motors(),
  distanceSensors(),
  humiditySensors(),
  soilMoistureSensors(),
  temperatureSensors() {

}

HWFactory::~HWFactory() {
}

void HWFactory::create() {
  for (const auto simulationConfiguration : configurationFile.getSimulationConfigurations()) {
    for (const auto& name : simulationConfiguration->getMotors()) {
      motors.push_back(new SimulatedMotor(name));
    }
    for (const auto& name : simulationConfiguration->getDistanceSensors()) {
      distanceSensors.push_back(new SimulatedDistanceSensor(name, master));
    }
    for (const auto& name : simulationConfiguration->getHumiditySensors()) {
      humiditySensors.push_back(new SimulatedHumiditySensor(name, master));
    }
    for (const auto& name : simulationConfiguration->getSoilSensors()) {
      soilMoistureSensors.push_back(new SimulatedSoilMoistureSensor(name, master));
    }
    for (const auto& name : simulationConfiguration->getTemperatureSensors()) {
      temperatureSensors.push_back(new SimulatedTemperatureSensor(name, master));
    }
  }
}

IMotorController& HWFactory::getMotor(const std::string& name) {
  for (auto motor : motors) {
    if (motor->getName() == name) {
      return *motor;
    }
  }

  assert(false && "could not find motor");
}

const IMotorController& HWFactory::getMotor(const std::string& name) const {
  for (auto motor : motors) {
    if (motor->getName() == name) {
      return *motor;
    }
  }

  assert(false && "could not find motor");
}

const std::vector<IMotorController*>& HWFactory::getMotors() {
  return motors;
}

const std::vector<IMotorController*>& HWFactory::getMotors() const {
  return motors;
}

ITemperatureSensor& HWFactory::getTemperatureSensor(const std::string& name) {
  for (auto sensor : temperatureSensors) {
    if (sensor->getName() == name) {
      return *sensor;
    }
  }

  assert(false && "could not find sensor");
}

const ITemperatureSensor& HWFactory::getTemperatureSensor(const std::string& name) const {
  for (auto sensor : temperatureSensors) {
    if (sensor->getName() == name) {
      return *sensor;
    }
  }

  assert(false && "could not find sensor");
}

const std::vector<ITemperatureSensor*>& HWFactory::getTemperatureSensors() {
  return temperatureSensors;
}

const std::vector<ITemperatureSensor*>& HWFactory::getTemperatureSensors() const {
  return temperatureSensors;
}

ISoilMoistureSensor& HWFactory::getSoilMoistureSensor(const std::string& name) {
  for (auto sensor : soilMoistureSensors) {
    if (sensor->getName() == name) {
      return *sensor;
    }
  }

  assert(false && "could not find sensor");
}

const ISoilMoistureSensor& HWFactory::getSoilMoistureSensor(const std::string& name) const {
  for (auto sensor : soilMoistureSensors) {
    if (sensor->getName() == name) {
      return *sensor;
    }
  }

  assert(false && "could not find sensor");
}

const std::vector<ISoilMoistureSensor*>& HWFactory::getSoilMoistureSensors() {
  return soilMoistureSensors;
}

const std::vector<ISoilMoistureSensor*>& HWFactory::getSoilMoistureSensors() const {
  return soilMoistureSensors;
}

IDistanceSensor& HWFactory::getDistanceSensor(const std::string& name) {
  for (auto sensor : distanceSensors) {
    if (sensor->getName() == name) {
      return *sensor;
    }
  }

  assert(false && "could not find sensor");
}

const IDistanceSensor& HWFactory::getDistanceSensor(const std::string& name) const {
  for (auto sensor : distanceSensors) {
    if (sensor->getName() == name) {
      return *sensor;
    }
  }

  assert(false && "could not find sensor");
}

const std::vector<IDistanceSensor*>& HWFactory::getDistanceSensors() {
  return distanceSensors;
}

const std::vector<IDistanceSensor*>& HWFactory::getDistanceSensors() const {
  return distanceSensors;
}

IHumiditySensor& HWFactory::getHumiditySensor(const std::string& name) {
  for (auto sensor : humiditySensors) {
    if (sensor->getName() == name) {
      return *sensor;
    }
  }

  assert(false && "could not find sensor");
}

const IHumiditySensor& HWFactory::getHumiditySensor(const std::string& name) const {
  for (auto sensor : humiditySensors) {
    if (sensor->getName() == name) {
      return *sensor;
    }
  }

  assert(false && "could not find sensor");
}

const std::vector<IHumiditySensor*>& HWFactory::getHumiditySensors() {
  return humiditySensors;
}

const std::vector<IHumiditySensor*>& HWFactory::getHumiditySensors() const {
  return humiditySensors;
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
