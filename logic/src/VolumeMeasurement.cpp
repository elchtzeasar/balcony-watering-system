#include "VolumeMeasurement.h"

#include "IDistanceSensor.h"
#include "IVolumeMeasurementConfiguration.h"

#include <algorithm>

namespace balcony_watering_system {
namespace logic {

using ::balcony_watering_system::configuration::IVolumeMeasurementConfiguration;
using ::balcony_watering_system::hardware::IDistanceSensor;
using ::std::max;
using ::std::string;
using ::std::vector;

VolumeMeasurement::VolumeMeasurement(
    const IVolumeMeasurementConfiguration& configuration,
    const IDistanceSensor& sensor) :
  name(configuration.getName()),
  areaInSquareMeters(configuration.getAreaInSquareMeters()),
  sensor(sensor) {
}

VolumeMeasurement::~VolumeMeasurement() {
}

const string& VolumeMeasurement::getName() const {
  return name;
}

float VolumeMeasurement::getMin() const {
  const float distanceInMeters = sensor.getMin() / 1000.0;
  const float volume = areaInSquareMeters * distanceInMeters;
  return volume;
}

float VolumeMeasurement::getMax() const {
  const float distanceInMeters = sensor.getMax() / 1000.0;
  const float volume = areaInSquareMeters * distanceInMeters;
  return volume;
}

float VolumeMeasurement::getVolumeInLiters() const {
  const float distanceInMeters = sensor.getDistanceInMillimeters() / 1000.0;
  const float volume = areaInSquareMeters * distanceInMeters;
  return volume;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
