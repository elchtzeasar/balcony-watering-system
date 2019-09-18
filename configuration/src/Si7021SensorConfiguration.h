#ifndef CONFIGURATION_SRC_SI7021SENSORCONFIGURATION_H_
#define CONFIGURATION_SRC_SI7021SENSORCONFIGURATION_H_

#include "IConfiguration.h"
#include "ISi7021SensorConfiguration.h"

namespace balcony_watering_system {
namespace configuration {

class Si7021SensorConfiguration : public IConfiguration, public ISi7021SensorConfiguration {
public:
  Si7021SensorConfiguration();
  virtual ~Si7021SensorConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::string& getName() const override;

private:
  std::string name;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_SI7021SENSORCONFIGURATION_H_ */
