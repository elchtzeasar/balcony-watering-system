#ifndef CONFIGURATION_SRC_PUMPCONFIGURATION_H_
#define CONFIGURATION_SRC_PUMPCONFIGURATION_H_

#include "IConfiguration.h"
#include "IPumpConfiguration.h"

#include "Logger.h"

namespace balcony_watering_system {
namespace configuration {

class PumpConfiguration : public IConfiguration, public IPumpConfiguration {
public:
  PumpConfiguration();
  virtual ~PumpConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::string& getName() const override;
  virtual const std::string& getMotor() const override;

private:
  std::string name;
  std::string motor;

  const platform::Logger logger;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_PUMPCONFIGURATION_H_ */
