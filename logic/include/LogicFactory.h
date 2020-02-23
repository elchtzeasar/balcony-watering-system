#ifndef LOGIC_SRC_LOGICFACTORY_H_
#define LOGIC_SRC_LOGICFACTORY_H_

#include <string>
#include <vector>

namespace balcony_watering_system::configuration {
class ConfigurationFile;
} /* namespace balcony_watering_system::configuration */

namespace balcony_watering_system::hardware {
class HWFactory;
} /* namespace balcony_watering_system::hardware */

namespace balcony_watering_system {
namespace logic {

class Logic;
class HumidityMeasurement;
class Pump;
class SoilMoistureMeasurement;
class TemperatureMeasurement;
class VolumeMeasurement;
class WateringLogic;

class LogicFactory {
public:
  LogicFactory(const configuration::ConfigurationFile& configurationFile,
               Logic& logic,
               hardware::HWFactory& hwFactory);
  virtual ~LogicFactory();

  LogicFactory& operator=(const LogicFactory&) = delete;
  LogicFactory& operator=(const LogicFactory&&) = delete;

  void create();

  const std::vector<Pump*>& getPumps();
  const std::vector<Pump*>& getPumps() const;
  Pump* getPump(const std::string& name) const;
  const std::vector<HumidityMeasurement*>& getHumidityMeasurements();
  const std::vector<HumidityMeasurement*>& getHumidityMeasurements() const;
  const HumidityMeasurement* getHumidityMeasurement(const std::string& name) const;
  const std::vector<SoilMoistureMeasurement*>& getSoilMoistureMeasurements();
  const std::vector<SoilMoistureMeasurement*>& getSoilMoistureMeasurements() const;
  const SoilMoistureMeasurement* getSoilMoistureMeasurement(const std::string& name) const;
  const std::vector<TemperatureMeasurement*>& getTemperatureMeasurements();
  const std::vector<TemperatureMeasurement*>& getTemperatureMeasurements() const;
  const TemperatureMeasurement* getTemperatureMeasurement(const std::string& name) const;
  const std::vector<VolumeMeasurement*>& getVolumeMeasurements();
  const std::vector<VolumeMeasurement*>& getVolumeMeasurements() const;
  const VolumeMeasurement* getVolumeMeasurement(const std::string& name) const;

  const WateringLogic& getWateringLogic();
  const WateringLogic& getWateringLogic() const;

private:
  const configuration::ConfigurationFile& configurationFile;
  Logic& logic;
  hardware::HWFactory& hwFactory;

  std::vector<Pump*> pumps;
  std::vector<HumidityMeasurement*> humidityMeasurements;
  std::vector<SoilMoistureMeasurement*> soilMoistureMeasurements;
  std::vector<TemperatureMeasurement*> temperatureMeasurements;
  std::vector<VolumeMeasurement*> volumeMeasurements;
  WateringLogic const* wateringLogic;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_LOGICFACTORY_H_ */
