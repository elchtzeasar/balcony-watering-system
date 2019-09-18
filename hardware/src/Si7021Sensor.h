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

  virtual int getMin() const override;
  virtual int getMax() const override;
  virtual int getTemperatureInDegrees() const override;

  virtual int getHumidityInPercent() const override;

 private:
  const std::string name;

  int temperatureInDegrees;
  int humidityInPercent;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif// HARDWARE_SRC_SI7021_SENSOR_H_
