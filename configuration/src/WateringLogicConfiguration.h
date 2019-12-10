#ifndef CONFIGURATION_SRC_WATERINGLOGICCONFIGURATION_H_
#define CONFIGURATION_SRC_WATERINGLOGICCONFIGURATION_H_

#include "IConfiguration.h"
#include "IWateringLogicConfiguration.h"

#include "Logger.h"

namespace balcony_watering_system {
namespace configuration {

class WateringLogicConfiguration : public IConfiguration, public IWateringLogicConfiguration {
public:
  WateringLogicConfiguration();
  virtual ~WateringLogicConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::string& getPumpController() const override;

  virtual const std::string& getSoilMoistureMeasurement() const override;
  virtual const std::string& getHumidityMeasurement() const override;
  virtual const std::string& getTemperatureMeasurement() const override;

  virtual const std::chrono::seconds& getTimeToWater() const override;
  virtual const std::chrono::seconds& getTimeToNotWater() const override;

private:
  std::string pumpController;

  std::string soilMoistureMeasurement;
  std::string humidityMeasurement;
  std::string temperatureMeasurement;

  std::chrono::seconds timeToWater;
  std::chrono::seconds timeToNotWater;

  const platform::Logger logger;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_WATERINGLOGICCONFIGURATION_H_ */
