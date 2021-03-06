#ifndef CONFIGURATION_SRC_TEMPERATUREMEASUREMENTCONFIGURATION_H_
#define CONFIGURATION_SRC_TEMPERATUREMEASUREMENTCONFIGURATION_H_

#include "IConfiguration.h"
#include "ITemperatureMeasurementConfiguration.h"

#include "Logger.h"
namespace balcony_watering_system {
namespace configuration {

class TemperatureMeasurementConfiguration : public IConfiguration, public ITemperatureMeasurementConfiguration {
public:
  TemperatureMeasurementConfiguration();
  virtual ~TemperatureMeasurementConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::string& getName() const override;
  virtual float getThreshold() const override;
  virtual const std::vector<std::string>& getSensors() const override;

private:
  std::string name;
  float threshold;
  std::vector<std::string> sensors;

  const platform::Logger logger;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_TEMPERATUREMEASUREMENTCONFIGURATION_H_ */
