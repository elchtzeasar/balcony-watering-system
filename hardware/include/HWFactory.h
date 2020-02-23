#ifndef LOGIC_SRC_HWFACTORY_H_
#define LOGIC_SRC_HWFACTORY_H_

#include <string>
#include <vector>

namespace balcony_watering_system::configuration {

class ConfigurationFile;

} /* namespace balcony_watering_system::configuration */

namespace balcony_watering_system {
namespace hardware {

class IAnalogInput;
class IArduino;
class IDistanceSensor;
class IHumiditySensor;
class IMotorController;
class IReadNode;
class ISoilMoistureSensor;
class ITemperatureSensor;
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

  IDistanceSensor& getDistanceSensor(const std::string& name);
  const IDistanceSensor& getDistanceSensor(const std::string& name) const;
  const std::vector<IDistanceSensor*>& getDistanceSensors();
  const std::vector<IDistanceSensor*>& getDistanceSensors() const;

  IHumiditySensor& getHumiditySensor(const std::string& name);
  const IHumiditySensor& getHumiditySensor(const std::string& name) const;
  const std::vector<IHumiditySensor*>& getHumiditySensors();
  const std::vector<IHumiditySensor*>& getHumiditySensors() const;

  ISoilMoistureSensor& getSoilMoistureSensor(const std::string& name);
  const ISoilMoistureSensor& getSoilMoistureSensor(const std::string& name) const;
  const std::vector<ISoilMoistureSensor*>& getSoilMoistureSensors();
  const std::vector<ISoilMoistureSensor*>& getSoilMoistureSensors() const;

  ITemperatureSensor& getTemperatureSensor(const std::string& name);
  const ITemperatureSensor& getTemperatureSensor(const std::string& name) const;
  const std::vector<ITemperatureSensor*>& getTemperatureSensors();
  const std::vector<ITemperatureSensor*>& getTemperatureSensors() const;

  IArduino& getArduino() const;

  const IAnalogInput& getAnalogInput(const std::string& name) const;
  const std::vector<IAnalogInput const*>& getAnalogInputs();
  const std::vector<IAnalogInput const*>& getAnalogInputs() const;

private:
  const configuration::ConfigurationFile& configurationFile;
  Master& master;

  std::vector<IMotorController*> motors;
  std::vector<IDistanceSensor*> distanceSensors;
  std::vector<IHumiditySensor*> humiditySensors;
  std::vector<ISoilMoistureSensor*> soilMoistureSensors;
  std::vector<ITemperatureSensor*> temperatureSensors;
  std::vector<IReadNode*> circuits;
  IArduino* arduino;
  std::vector<IAnalogInput const*> analogInputs;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_HWFACTORY_H_ */
