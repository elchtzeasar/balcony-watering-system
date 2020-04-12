#ifndef CONFIGURATION_SRC_ARDUINOCONFIGURATION_H_
#define CONFIGURATION_SRC_ARDUINOCONFIGURATION_H_

#include "IConfiguration.h"
#include "IArduinoConfiguration.h"

#include "Logger.h"

namespace balcony_watering_system {
namespace configuration {

class ArduinoConfiguration : public IConfiguration, public IArduinoConfiguration {
public:
  ArduinoConfiguration();
  virtual ~ArduinoConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual int getAddress() const override;
  virtual int getShutdownEnabledPin() const override;
  virtual const std::string& getNamePrefix() const override;

private:
  const platform::Logger logger;

  int address;
  int shutdownEnabledPin;
  std::string namePrefix;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_ARDUINOCONFIGURATION_H_ */
