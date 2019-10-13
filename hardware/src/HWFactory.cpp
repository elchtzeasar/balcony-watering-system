#include "HWFactory.h"

#include "ConfigurationFile.h"
#include "IADS1015Configuration.h"
#include "IAnalogSoilMoistureSensorConfiguration.h"
#include "ISi7021SensorConfiguration.h"
#include "ISimulationConfiguration.h"
#include "ADS1015.h"
#include "AnalogSoilMoistureSensor.h"
#include "Si7021Sensor.h"
#include "SimulatedMotor.h"
#include "SimulatedDistanceSensor.h"
#include "SimulatedHumiditySensor.h"
#include "SimulatedSoilMoistureSensor.h"
#include "SimulatedTemperatureSensor.h"

#include <algorithm>
#include <cassert>
#include <iterator>

namespace balcony_watering_system {
namespace hardware {

using ::balcony_watering_system::configuration::ConfigurationFile;
using ::std::back_inserter;
using ::std::transform;

HWFactory::HWFactory(const ConfigurationFile& configurationFile,
                     Master& master) :
  configurationFile(configurationFile),
  master(master),
  motors(),
  distanceSensors(),
  humiditySensors(),
  soilMoistureSensors(),
  temperatureSensors(),
  circuits(),
  analogInputs() {
}

HWFactory::~HWFactory() {
  for (auto motor : motors) {
    delete motor;
  }
  for (auto sensor : distanceSensors) {
    delete sensor;
  }
  for (auto sensor : humiditySensors) {
    delete sensor;
  }
  for (auto sensor : soilMoistureSensors) {
    delete sensor;
  }
  for (auto sensor : temperatureSensors) {
    delete sensor;
  }
  for (auto circuit : circuits) {
    delete circuit;
  }
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
  for (const auto& configuration : configurationFile.getSi7021SensorConfigurations()) {
    auto sensor = new Si7021Sensor(configuration->getName(), master);
    temperatureSensors.push_back(sensor);
    humiditySensors.push_back(sensor);
  }
  for (const auto& configuration : configurationFile.getADS1015Configurations()) {
    auto circuit = new ADS1015(configuration->getNamePrefix(), master);
    circuits.push_back(circuit);
    const auto& sensorInputs = circuit->getAnalogInputs();
    transform(sensorInputs.begin(), sensorInputs.end(), back_inserter(analogInputs),
        [](const AnalogInput& input) -> IAnalogInput const* { return &input; });
  }
  for (const auto& configuration : configurationFile.getAnalogSoilMoistureSensors()) {
    const auto& analogInput = getAnalogInput(configuration->getInputName());
    auto sensor = new AnalogSoilMoistureSensor(configuration->getName(),
                                               configuration->getWaterVoltage(),
                                               configuration->getDryVoltage(),
                                               analogInput,
                                               master);
    soilMoistureSensors.push_back(sensor);
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
const IAnalogInput& HWFactory::getAnalogInput(const std::string& name) const {
  for (auto input : analogInputs) {
    if (input->getName() == name) {
      return *input;
    }
  }

  assert(false && "could not find sensor");
}

const std::vector<IAnalogInput const*>& HWFactory::getAnalogInputs() {
  return analogInputs;
}

const std::vector<IAnalogInput const*>& HWFactory::getAnalogInputs() const {
  return analogInputs;
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
