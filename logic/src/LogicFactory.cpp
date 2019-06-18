#include "LogicFactory.h"

#include "ConfigurationFile.h"
#include "IPumpConfiguration.h"
#include "ISoilMoistureMeasurementConfiguration.h"
#include "HWFactory.h"
#include "Pump.h"
#include "SoilMoistureMeasurement.h"

#include <vector>

namespace balcony_watering_system {
namespace logic {

using ::std::vector;
using ::balcony_watering_system::configuration::ConfigurationFile;
using ::balcony_watering_system::hardware::HWFactory;
using ::balcony_watering_system::hardware::ISoilMoistureSensor;

LogicFactory::LogicFactory(const ConfigurationFile& configurationFile,
                           HWFactory& hwFactory) :
  configurationFile(configurationFile),
  hwFactory(hwFactory),
  pumps(),
  soilMoistureMeasurements() {

}

LogicFactory::~LogicFactory() {
}

void LogicFactory::create() {
  for (const auto configuration : configurationFile.getPumpConfigurations()) {
    auto& motor = hwFactory.getMotor(configuration->getMotor());
    pumps.push_back(new Pump(*configuration, motor));
  }

  for (const auto configuration : configurationFile.getSoilMoistureMeasurementConfigurations()) {
    vector<ISoilMoistureSensor*> sensors;
    const auto& sensorNames = configuration->getSensors();
    for (const auto& sensorName : sensorNames) {
      auto& sensor = hwFactory.getSoilMoistureSensor(sensorName);
      sensors.push_back(&sensor);
    }
    soilMoistureMeasurements.push_back(new SoilMoistureMeasurement(*configuration, sensors));
  }
}

const std::vector<Pump*>& LogicFactory::getPumps() {
  return pumps;
}

const std::vector<Pump*>& LogicFactory::getPumps() const {
  return pumps;
}

const std::vector<SoilMoistureMeasurement*>& LogicFactory::getSoilMoistureMeasurements() {
  return soilMoistureMeasurements;
}

const std::vector<SoilMoistureMeasurement*>& LogicFactory::getSoilMoistureMeasurements() const {
  return soilMoistureMeasurements;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
