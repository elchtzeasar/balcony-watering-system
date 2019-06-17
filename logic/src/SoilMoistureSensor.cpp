#include "SoilMoistureSensor.h"

#include "ISoilMoistureSensor.h"
#include "ISoilMoistureSensorConfiguration.h"

namespace balcony_watering_system {
namespace logic {

using ::balcony_watering_system::configuration::ISoilMoistureSensorConfiguration;
using ::balcony_watering_system::hardware::ISoilMoistureSensor;
using ::std::string;

SoilMoistureSensor::SoilMoistureSensor(
    const ISoilMoistureSensorConfiguration& configuration,
    const ISoilMoistureSensor& sensor) :
  name(configuration.getName()),
  sensor(sensor) {
}

SoilMoistureSensor::~SoilMoistureSensor() {
}

const string& SoilMoistureSensor::getName() const {
  return name;
}

int SoilMoistureSensor::getMoistureLevelInPercent() const {
  return sensor.getMoistureLevelInPercent();
}

} /* namespace logic */
} /* namespace balcony_watering_system */
