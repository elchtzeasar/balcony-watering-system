#ifndef CONFIGURATION_SRC_SOILMOISTURESENSORCONFIGURATION_H_
#define CONFIGURATION_SRC_SOILMOISTURESENSORCONFIGURATION_H_

#include "IConfiguration.h"
#include "ISoilMoistureSensorConfiguration.h"

namespace balcony_watering_system {
namespace configuration {

class SoilMoistureSensorConfiguration : public IConfiguration, public ISoilMoistureSensorConfiguration {
public:
  SoilMoistureSensorConfiguration();
  virtual ~SoilMoistureSensorConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::string& getName() const override;
  virtual const std::string& getSensor() const override;

private:
  std::string name;
  std::string sensor;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_SOILMOISTURESENSORCONFIGURATION_H_ */
