#ifndef CONFIGURATION_SRC_ISI7021SENSORCONFIGURATION_H_
#define CONFIGURATION_SRC_ISI7021SENSORCONFIGURATION_H_

#include <string>

namespace balcony_watering_system {
namespace configuration {

class ISi7021SensorConfiguration {
public:
  virtual ~ISi7021SensorConfiguration() = default;

  virtual const std::string& getName() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_ISI7021SENSORCONFIGURATION_H_ */
