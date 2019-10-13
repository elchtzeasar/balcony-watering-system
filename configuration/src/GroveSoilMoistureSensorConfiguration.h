#ifndef CONFIGURATION_SRC_GROVESOILMOISTURESENSORCONFIGURATION_H_
#define CONFIGURATION_SRC_GROVESOILMOISTURESENSORCONFIGURATION_H_

#include "IConfiguration.h"
#include "IAnalogSoilMoistureSensorConfiguration.h"

namespace balcony_watering_system {
namespace configuration {

class GroveSoilMoistureSensorConfiguration : public IConfiguration, public IAnalogSoilMoistureSensorConfiguration {
public:
  GroveSoilMoistureSensorConfiguration();
  virtual ~GroveSoilMoistureSensorConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::string& getName() const override;
  virtual const std::string& getInputName() const override;
  virtual float getWaterVoltage() const override;
  virtual float getDryVoltage() const override;

private:
  std::string name;
  std::string inputName;
  float waterVoltage;
  float dryVoltage;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_GROVESOILMOISTURESENSORCONFIGURATION_H_ */
