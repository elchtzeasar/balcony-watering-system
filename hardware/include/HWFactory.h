#ifndef LOGIC_SRC_HWFACTORY_H_
#define LOGIC_SRC_HWFACTORY_H_

#include <string>
#include <vector>

namespace balcony_watering_system::configuration {

class ConfigurationFile;

} /* namespace balcony_watering_system::configuration */

namespace balcony_watering_system {
namespace hardware {

class IMotorController;
class ISoilMoistureSensor;
class Master;

class HWFactory {
public:
  HWFactory(const configuration::ConfigurationFile& configurationFile,
            Master& master);
  virtual ~HWFactory();

  HWFactory& operator=(const HWFactory&) = delete;
  HWFactory& operator=(const HWFactory&&) = delete;

  void create();

  IMotorController& getMotor(const std::string& name);
  const IMotorController& getMotor(const std::string& name) const;
  const std::vector<IMotorController*>& getMotors();
  const std::vector<IMotorController*>& getMotors() const;
  ISoilMoistureSensor& getSoilMoistureSensor(const std::string& name);
  const ISoilMoistureSensor& getSoilMoistureSensor(const std::string& name) const;
  const std::vector<ISoilMoistureSensor*>& getSoilMoistureSensors();
  const std::vector<ISoilMoistureSensor*>& getSoilMoistureSensors() const;

private:
  const configuration::ConfigurationFile& configurationFile;
  Master& master;

  std::vector<IMotorController*> motors;
  std::vector<ISoilMoistureSensor*> soilMoistureSensors;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_HWFACTORY_H_ */
