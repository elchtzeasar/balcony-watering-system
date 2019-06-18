#ifndef CONFIGURATION_SRC_IVOLUMEMEASUREMENTCONFIGURATION_H_
#define CONFIGURATION_SRC_IVOLUMEMEASUREMENTCONFIGURATION_H_

#include <string>
#include <vector>

namespace balcony_watering_system {
namespace configuration {

class IVolumeMeasurementConfiguration {
public:
  virtual ~IVolumeMeasurementConfiguration() = default;

  virtual const std::string& getName() const = 0;
  virtual const std::string& getSensor() const = 0;
  virtual double getAreaInSquareMeters() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_IVOLUMEMEASUREMENTCONFIGURATION_H_ */
