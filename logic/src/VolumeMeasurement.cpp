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

double VolumeMeasurement::getMin() const {
  const double distanceInMeters = sensor.getMin() / 1000.0;
  const double volume = areaInSquareMeters * distanceInMeters;
  return volume;
}

double VolumeMeasurement::getMax() const {
  const double distanceInMeters = sensor.getMax() / 1000.0;
  const double volume = areaInSquareMeters * distanceInMeters;
  return volume;
}

double VolumeMeasurement::getVolumeInLiters() const {
  const double distanceInMeters = sensor.getDistanceInMillimeters() / 1000.0;
  const double volume = areaInSquareMeters * distanceInMeters;
  return volume;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
