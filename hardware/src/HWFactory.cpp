#include "HWFactory.h"

#include "ConfigurationFile.h"
#include "ISimulationConfiguration.h"
#include "SimulatedMotor.h"
#include "SimulatedSoilMoistureSensor.h"

#include <cassert>

namespace balcony_watering_system {
namespace hardware {

using ::balcony_watering_system::configuration::ConfigurationFile;

HWFactory::HWFactory(const ConfigurationFile& configurationFile,
                     Master& master) :
  configurationFile(configurationFile),
  master(master),
  motors(),
  soilMoistureSensors() {

}

HWFactory::~HWFactory() {
}

void HWFactory::create() {
  for (const auto configuration : configurationFile.getPumpConfigurations()) {
  }

  for (const auto simulationConfiguration : configurationFile.getSimulationConfigurations()) {
    for (const auto& name : simulationConfiguration->getMotors()) {
      motors.push_back(new SimulatedMotor(name));
    }
    for (const auto& name : simulationConfiguration->getSoilSensors()) {
      soilMoistureSensors.push_back(new SimulatedSoilMoistureSensor(name, master));
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

} /* namespace hardware */
} /* namespace balcony_watering_system */
