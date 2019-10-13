#ifndef CONFIGURATION_SRC_IANALOGSOILMOISTURESENSORCONFIGURATION_H_
#define CONFIGURATION_SRC_IANALOGSOILMOISTURESENSORCONFIGURATION_H_

#include <string>

namespace balcony_watering_system {
namespace configuration {

class IAnalogSoilMoistureSensorConfiguration {
public:
  virtual ~IAnalogSoilMoistureSensorConfiguration() = default;

  virtual const std::string& getName() const = 0;
  virtual const std::string& getInputName() const = 0;
  virtual float getWaterVoltage() const = 0;
  virtual float getDryVoltage() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_IANALOGSOILMOISTURESENSORCONFIGURATION_H_ */
