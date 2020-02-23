#include "LogicFactory.h"

#include "ConfigurationFile.h"
#include "HumidityMeasurement.h"
#include "HWFactory.h"
#include "IHumidityMeasurementConfiguration.h"
#include "IPumpConfiguration.h"
#include "ISoilMoistureMeasurementConfiguration.h"
#include "ITemperatureMeasurementConfiguration.h"
#include "IVolumeMeasurementConfiguration.h"
#include "IWateringLogicConfiguration.h"
#include "Pump.h"
#include "SoilMoistureMeasurement.h"
#include "TemperatureMeasurement.h"
#include "VolumeMeasurement.h"
#include "WateringLogic.h"

#include <algorithm>
#include <cassert>

namespace balcony_watering_system {
namespace logic {

using ::std::find_if;
using ::std::string;
using ::std::vector;
using ::balcony_watering_system::configuration::ConfigurationFile;
using ::balcony_watering_system::hardware::HWFactory;
using ::balcony_watering_system::hardware::IDistanceSensor;
using ::balcony_watering_system::hardware::IHumiditySensor;
using ::balcony_watering_system::hardware::ISoilMoistureSensor;
using ::balcony_watering_system::hardware::ITemperatureSensor;

LogicFactory::LogicFactory(const ConfigurationFile& configurationFile,
                           Logic& logic,
                           HWFactory& hwFactory) :
  configurationFile(configurationFile),
  logic(logic),
  hwFactory(hwFactory),
  pumps(),
  soilMoistureMeasurements(),
  wateringLogic(nullptr) {
}

LogicFactory::~LogicFactory() {
  for (auto pump : pumps) {
    delete pump;
  }
  for (auto measurement : humidityMeasurements) {
    delete measurement;
  }
  for (auto measurement : soilMoistureMeasurements) {
    delete measurement;
  }
  for (auto measurement : temperatureMeasurements) {
    delete measurement;
  }
  for (auto measurement : volumeMeasurements) {
    delete measurement;
  }
}

void LogicFactory::create() {
  for (const auto configuration : configurationFile.getPumpConfigurations()) {
    auto& motor = hwFactory.getMotor(configuration->getMotor());
    pumps.push_back(new Pump(*configuration, motor));
  }

  for (const auto configuration : configurationFile.getHumidityMeasurementConfigurations()) {
    vector<IHumiditySensor*> sensors;
    const auto& sensorNames = configuration->getSensors();
    for (const auto& sensorName : sensorNames) {
      auto& sensor = hwFactory.getHumiditySensor(sensorName);
      sensors.push_back(&sensor);
    }
    humidityMeasurements.push_back(new HumidityMeasurement(*configuration, sensors));
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
  for (const auto configuration : configurationFile.getTemperatureMeasurementConfigurations()) {
    vector<ITemperatureSensor*> sensors;
    const auto& sensorNames = configuration->getSensors();
    for (const auto& sensorName : sensorNames) {
      auto& sensor = hwFactory.getTemperatureSensor(sensorName);
      sensors.push_back(&sensor);
    }
    temperatureMeasurements.push_back(new TemperatureMeasurement(*configuration, sensors));
  }
  for (const auto configuration : configurationFile.getVolumeMeasurementConfigurations()) {
    IDistanceSensor& sensor = hwFactory.getDistanceSensor(configuration->getSensor());
    volumeMeasurements.push_back(new VolumeMeasurement(*configuration, sensor));
  }

  {
    const auto& configuration = configurationFile.getWateringLogicConfiguration();
    auto* soil = getSoilMoistureMeasurement(configuration.getSoilMoistureMeasurement());
    auto* temperature = getTemperatureMeasurement(configuration.getTemperatureMeasurement());
    auto* humidity = getHumidityMeasurement(configuration.getHumidityMeasurement());
    auto* pump = getPump(configuration.getPumpController());
    const auto& timeToWater = configuration.getTimeToWater();
    const auto& timeToNotWater = configuration.getTimeToNotWater();

    wateringLogic = new WateringLogic(logic, soil, temperature, humidity, pump, timeToWater, timeToNotWater);
  }
}

const std::vector<Pump*>& LogicFactory::getPumps() {
  return pumps;
}

const std::vector<Pump*>& LogicFactory::getPumps() const {
  return pumps;
}

Pump* LogicFactory::getPump(const string& name) const {
  const auto it = find_if(pumps.begin(), pumps.end(), [name](Pump* pump) {
    return name == pump->getName();
  });

  if (it != pumps.end()) {
    return *it;
  }
  return nullptr;
}

const std::vector<HumidityMeasurement*>& LogicFactory::getHumidityMeasurements() {
  return humidityMeasurements;
}

const std::vector<HumidityMeasurement*>& LogicFactory::getHumidityMeasurements() const {
  return humidityMeasurements;
}

const HumidityMeasurement* LogicFactory::getHumidityMeasurement(const string& name) const {
  const auto it = find_if(humidityMeasurements.begin(), humidityMeasurements.end(), [name](auto* measurement) {
    return name == measurement->getName();
  });

  if (it != humidityMeasurements.end()) {
    return *it;
  }
  return nullptr;
}

const std::vector<SoilMoistureMeasurement*>& LogicFactory::getSoilMoistureMeasurements() {
  return soilMoistureMeasurements;
}

const std::vector<SoilMoistureMeasurement*>& LogicFactory::getSoilMoistureMeasurements() const {
  return soilMoistureMeasurements;
}

const SoilMoistureMeasurement* LogicFactory::getSoilMoistureMeasurement(const string& name) const {
  const auto it = find_if(soilMoistureMeasurements.begin(), soilMoistureMeasurements.end(), [name](auto* mearsurement) {
    return name == mearsurement->getName();
  });

  if (it != soilMoistureMeasurements.end()) {
    return *it;
  }
  return nullptr;
}

const std::vector<TemperatureMeasurement*>& LogicFactory::getTemperatureMeasurements() {
  return temperatureMeasurements;
}

const std::vector<TemperatureMeasurement*>& LogicFactory::getTemperatureMeasurements() const {
  return temperatureMeasurements;
}

const TemperatureMeasurement* LogicFactory::getTemperatureMeasurement(const string& name) const {
  const auto it = find_if(temperatureMeasurements.begin(), temperatureMeasurements.end(), [name](auto* measurement) {
    return name == measurement->getName();
  });

  if (it != temperatureMeasurements.end()) {
    return *it;
  }
  return nullptr;
}

const std::vector<VolumeMeasurement*>& LogicFactory::getVolumeMeasurements() {
  return volumeMeasurements;
}

const std::vector<VolumeMeasurement*>& LogicFactory::getVolumeMeasurements() const {
  return volumeMeasurements;
}

const VolumeMeasurement* LogicFactory::getVolumeMeasurement(const string& name) const {
  const auto it = find_if(volumeMeasurements.begin(), volumeMeasurements.end(), [name](auto* measurement) {
    return name == measurement->getName();
  });

  if (it != volumeMeasurements.end()) {
    return *it;
  }
  return nullptr;
}

const WateringLogic& LogicFactory::getWateringLogic() {
  assert(wateringLogic != nullptr && "no watering logic created");
  return *wateringLogic;
}

const WateringLogic& LogicFactory::getWateringLogic() const {
  assert(wateringLogic != nullptr && "no watering logic created");
  return *wateringLogic;
}


} /* namespace logic */
} /* namespace balcony_watering_system */
