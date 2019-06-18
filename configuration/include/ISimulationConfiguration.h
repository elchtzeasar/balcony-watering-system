#ifndef CONFIGURATION_SRC_ISIMULATIONCONFIGURATION_H_
#define CONFIGURATION_SRC_ISIMULATIONCONFIGURATION_H_

#include <string>
#include <vector>

namespace balcony_watering_system {
namespace configuration {

class ISimulationConfiguration {
public:
  virtual ~ISimulationConfiguration() = default;

  virtual const std::vector<std::string>& getDistanceSensors() const = 0;
  virtual const std::vector<std::string>& getHumiditySensors() const = 0;
  virtual const std::vector<std::string>& getSoilSensors() const = 0;
  virtual const std::vector<std::string>& getTemperatureSensors() const = 0;
  virtual const std::vector<std::string>& getMotors() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_ISIMULATIONCONFIGURATION_H_ */
