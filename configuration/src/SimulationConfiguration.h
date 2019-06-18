#ifndef CONFIGURATION_SRC_SIMULATIONCONFIGURATION_H_
#define CONFIGURATION_SRC_SIMULATIONCONFIGURATION_H_

#include "IConfiguration.h"
#include "ISimulationConfiguration.h"

namespace balcony_watering_system {
namespace configuration {

class SimulationConfiguration: public IConfiguration, public ISimulationConfiguration {
public:
  SimulationConfiguration();
  virtual ~SimulationConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::vector<std::string>& getHumiditySensors() const override;
  virtual const std::vector<std::string>& getDistanceSensors() const override;
  virtual const std::vector<std::string>& getSoilSensors() const override;
  virtual const std::vector<std::string>& getTemperatureSensors() const override;
  virtual const std::vector<std::string>& getMotors() const override;

private:
  std::vector<std::string> distanceSensors;
  std::vector<std::string> humiditySensors;
  std::vector<std::string> soilSensors;
  std::vector<std::string> temperatureSensors;
  std::vector<std::string> motors;

};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_SIMULATIONCONFIGURATION_H_ */
