#ifndef CONFIGURATION_SRC_ISOILMOISTURESENSORCONFIGURATION_H_
#define CONFIGURATION_SRC_ISOILMOISTURESENSORCONFIGURATION_H_

#include <string>

namespace balcony_watering_system {
namespace configuration {

class ISoilMoistureSensorConfiguration {
public:
  virtual ~ISoilMoistureSensorConfiguration() = default;

  virtual const std::string& getName() const = 0;
  virtual const std::string& getSensor() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_ISOILMOISTURESENSORCONFIGURATION_H_ */
