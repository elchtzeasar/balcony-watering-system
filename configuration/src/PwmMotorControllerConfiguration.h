#ifndef CONFIGURATION_SRC_PwmMotorControllerConfiguration_H_
#define CONFIGURATION_SRC_PwmMotorControllerConfiguration_H_

#include "IConfiguration.h"
#include "IPwmMotorControllerConfiguration.h"

#include "Logger.h"

namespace balcony_watering_system {
namespace configuration {

class PwmMotorControllerConfiguration : public IConfiguration, public IPwmMotorControllerConfiguration {
public:
  PwmMotorControllerConfiguration();
  virtual ~PwmMotorControllerConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::string& getName() const override;
  virtual int getOutput0Pin() const override;
  virtual int getOutput1Pin() const override;
  virtual int getPwmPin() const override;

private:
  std::string name;
  int output0Pin;
  int output1Pin;
  int pwmPin;

  const platform::Logger logger;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_PwmMotorControllerConfiguration_H_ */
