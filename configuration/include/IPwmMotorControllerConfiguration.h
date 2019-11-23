#ifndef CONFIGURATION_SRC_IPWMMOTORCONTROLLERCONFIGURATION_H_
#define CONFIGURATION_SRC_IPWMMOTORCONTROLLERCONFIGURATION_H_

#include <string>

namespace balcony_watering_system {
namespace configuration {

class IPwmMotorControllerConfiguration {
public:
  virtual ~IPwmMotorControllerConfiguration() = default;

  virtual const std::string& getName() const = 0;
  virtual int getOutput0Pin() const = 0;
  virtual int getOutput1Pin() const = 0;
  virtual int getPwmPin() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_IPWMMOTORCONTROLLERCONFIGURATION_H_ */
