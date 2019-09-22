#ifndef HARDWARE_SRC_SI7021_SENSOR_H_
#define HARDWARE_SRC_SI7021_SENSOR_H_

#include "IHumiditySensor.h"
#include "IReadNode.h"
#include "ITemperatureSensor.h"

namespace balcony_watering_system {
namespace hardware {

class Master;

class Si7021Sensor : public IReadNode, public ITemperatureSensor, public IHumiditySensor {
 public:
  Si7021Sensor(const std::string& name, Master& master);
  virtual ~Si7021Sensor();

  virtual const std::string& getName() const override;

  virtual void doSample() override;

  virtual float getMin() const override;
  virtual float getMax() const override;
  virtual float getTemperatureInDegrees() const override;

  virtual float getHumidityInPercent() const override;

 private:
  const std::string name;

  float temperatureInDegrees;
  float humidityInPercent;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif// HARDWARE_SRC_SI7021_SENSOR_H_
