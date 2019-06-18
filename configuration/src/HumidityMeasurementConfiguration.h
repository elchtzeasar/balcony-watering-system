#ifndef CONFIGURATION_SRC_HUMIDITYMEASUREMENTCONFIGURATION_H_
#define CONFIGURATION_SRC_HUMIDITYMEASUREMENTCONFIGURATION_H_

#include "IConfiguration.h"
#include "IHumidityMeasurementConfiguration.h"

namespace balcony_watering_system {
namespace configuration {

class HumidityMeasurementConfiguration : public IConfiguration, public IHumidityMeasurementConfiguration {
public:
  HumidityMeasurementConfiguration();
  virtual ~HumidityMeasurementConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::string& getName() const override;
  virtual const std::vector<std::string>& getSensors() const override;

private:
  std::string name;
  std::vector<std::string> sensors;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_HUMIDITYMEASUREMENTCONFIGURATION_H_ */
