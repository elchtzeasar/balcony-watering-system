#include "LogicFactory.h"

#include "ConfigurationFile.h"
#include "Pump.h"
#include "SoilMoistureSensor.h"

namespace balcony_watering_system {
namespace logic {

using ::balcony_watering_system::configuration::ConfigurationFile;

LogicFactory::LogicFactory(const ConfigurationFile& configurationFile) :
  configurationFile(configurationFile),
  pumps(),
  soilMoistureSensors() {

}

LogicFactory::~LogicFactory() {
}

void LogicFactory::create() {
  for (const auto configuration : configurationFile.getPumpConfigurations()) {
    pumps.push_back(new Pump(*configuration));
  }

  for (const auto configuration : configurationFile.getSoilMoistureSensorConfigurations()) {
    soilMoistureSensors.push_back(new SoilMoistureSensor(*configuration));
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
