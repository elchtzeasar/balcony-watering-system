#ifndef CONFIGURATION_SRC_ISOILMOISTUREMEASUREMENTCONFIGURATION_H_
#define CONFIGURATION_SRC_ISOILMOISTUREMEASUREMENTCONFIGURATION_H_

#include <string>
#include <vector>

namespace balcony_watering_system {
namespace configuration {

class ISoilMoistureMeasurementConfiguration {
public:
  virtual ~ISoilMoistureMeasurementConfiguration() = default;

  virtual const std::string& getName() const = 0;
  virtual int getThreshold() const = 0;
  virtual const std::vector<std::string>& getSensors() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_ISOILMOISTUREMEASUREMENTCONFIGURATION_H_ */
