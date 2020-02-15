#ifndef CONFIGURATION_SRC_IARDUINOCONFIGURATION_H_
#define CONFIGURATION_SRC_IARDUINOCONFIGURATION_H_

#include <string>

namespace balcony_watering_system {
namespace configuration {

class IArduinoConfiguration {
public:
  virtual ~IArduinoConfiguration() = default;

  virtual int getAddress() const = 0;
  virtual const std::string& getNamePrefix() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_IARDUINOCONFIGURATION_H_ */
