#ifndef CONFIGURATION_SRC_ITEMPERATUREMEASUREMENTCONFIGURATION_H_
#define CONFIGURATION_SRC_ITEMPERATUREMEASUREMENTCONFIGURATION_H_

#include <string>
#include <vector>

namespace balcony_watering_system {
namespace configuration {

class ITemperatureMeasurementConfiguration {
public:
  virtual ~ITemperatureMeasurementConfiguration() = default;

  virtual const std::string& getName() const = 0;
  virtual float getThreshold() const = 0;
  virtual const std::vector<std::string>& getSensors() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_ITEMPERATUREMEASUREMENTCONFIGURATION_H_ */
