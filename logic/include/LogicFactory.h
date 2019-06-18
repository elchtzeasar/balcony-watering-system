#ifndef LOGIC_SRC_LOGICFACTORY_H_
#define LOGIC_SRC_LOGICFACTORY_H_

#include <vector>

namespace balcony_watering_system::configuration {
class ConfigurationFile;
} /* namespace balcony_watering_system::configuration */

namespace balcony_watering_system::hardware {
class HWFactory;
} /* namespace balcony_watering_system::hardware */

namespace balcony_watering_system {
namespace logic {

class Pump;
class SoilMoistureMeasurement;

class LogicFactory {
public:
  LogicFactory(const configuration::ConfigurationFile& configurationFile,
               hardware::HWFactory& hwFactory);
  virtual ~LogicFactory();

  LogicFactory& operator=(const LogicFactory&) = delete;
  LogicFactory& operator=(const LogicFactory&&) = delete;

  void create();

  const std::vector<Pump*>& getPumps();
  const std::vector<Pump*>& getPumps() const;
  const std::vector<SoilMoistureMeasurement*>& getSoilMoistureMeasurements();
  const std::vector<SoilMoistureMeasurement*>& getSoilMoistureMeasurements() const;

private:
  const configuration::ConfigurationFile& configurationFile;
  hardware::HWFactory& hwFactory;

  std::vector<Pump*> pumps;
  std::vector<SoilMoistureMeasurement*> soilMoistureMeasurements;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_LOGICFACTORY_H_ */
