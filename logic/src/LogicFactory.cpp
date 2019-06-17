#include "LogicFactory.h"

#include "ConfigurationFile.h"
#include "IPumpConfiguration.h"
#include "ISoilMoistureSensorConfiguration.h"
#include "HWFactory.h"
#include "Pump.h"
#include "SoilMoistureSensor.h"

namespace balcony_watering_system {
namespace logic {

using ::balcony_watering_system::configuration::ConfigurationFile;
using ::balcony_watering_system::hardware::HWFactory;

LogicFactory::LogicFactory(const ConfigurationFile& configurationFile,
                           HWFactory& hwFactory) :
  configurationFile(configurationFile),
  hwFactory(hwFactory),
  pumps(),
  soilMoistureSensors() {

}

LogicFactory::~LogicFactory() {
}

void LogicFactory::create() {
  for (const auto configuration : configurationFile.getPumpConfigurations()) {
    auto& motor = hwFactory.getMotor(configuration->getMotor());
    pumps.push_back(new Pump(*configuration, motor));
  }

  for (const auto configuration : configurationFile.getSoilMoistureSensorConfigurations()) {
    auto& sensor = hwFactory.getSoilMoistureSensor(configuration->getSensor());
    soilMoistureSensors.push_back(new SoilMoistureSensor(*configuration, sensor));
  }
}

const std::vector<Pump*>& LogicFactory::getPumps() {
  return pumps;
}

const std::vector<Pump*>& LogicFactory::getPumps() const {
  return pumps;
}

const std::vector<SoilMoistureSensor*>& LogicFactory::getSoilMoistureSensors() {
  return soilMoistureSensors;
}

const std::vector<SoilMoistureSensor*>& LogicFactory::getSoilMoistureSensors() const {
  return soilMoistureSensors;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
