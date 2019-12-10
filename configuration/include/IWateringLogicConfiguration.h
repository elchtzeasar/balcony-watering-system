#ifndef CONFIGURATION_SRC_IWATERINGLOGICCONFIGURATION_H_
#define CONFIGURATION_SRC_IWATERINGLOGICCONFIGURATION_H_

#include <chrono>
#include <string>

namespace balcony_watering_system {
namespace configuration {

class IWateringLogicConfiguration {
public:
  virtual ~IWateringLogicConfiguration() = default;

  virtual const std::string& getPumpController() const = 0;

  virtual const std::string& getSoilMoistureMeasurement() const = 0;
  virtual const std::string& getHumidityMeasurement() const = 0;
  virtual const std::string& getTemperatureMeasurement() const = 0;

  virtual const std::chrono::seconds& getTimeToWater() const = 0;
  virtual const std::chrono::seconds& getTimeToNotWater() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_IWATERINGLOGICCONFIGURATION_H_ */
