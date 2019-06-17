#ifndef CONFIGURATION_SRC_IPUMPCONFIGURATION_H_
#define CONFIGURATION_SRC_IPUMPCONFIGURATION_H_

#include <string>

namespace balcony_watering_system {
namespace configuration {

class IPumpConfiguration {
public:
  virtual ~IPumpConfiguration() = default;

  virtual const std::string& getName() const = 0;
  virtual const std::string& getMotor() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_IPUMPCONFIGURATION_H_ */
