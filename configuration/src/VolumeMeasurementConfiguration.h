#ifndef CONFIGURATION_SRC_VOLUMEMEASUREMENTCONFIGURATION_H_
#define CONFIGURATION_SRC_VOLUMEMEASUREMENTCONFIGURATION_H_

#include "IConfiguration.h"
#include "IVolumeMeasurementConfiguration.h"

namespace balcony_watering_system {
namespace configuration {

class VolumeMeasurementConfiguration : public IConfiguration, public IVolumeMeasurementConfiguration {
public:
  VolumeMeasurementConfiguration();
  virtual ~VolumeMeasurementConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::string& getName() const override;
  virtual const std::string& getSensor() const override;
  virtual double getAreaInSquareMeters() const override;

private:
  std::string name;
  std::string sensor;
  double areaInSquareMeters;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_VOLUMEMEASUREMENTCONFIGURATION_H_ */
