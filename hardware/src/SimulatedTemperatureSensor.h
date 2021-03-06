#ifndef HARDWARE_SRC_SIMULATEDTEMPERATURESENSOR_H_
#define HARDWARE_SRC_SIMULATEDTEMPERATURESENSOR_H_

#include "IReadNode.h"
#include "ITemperatureSensor.h"

#include <chrono>

namespace balcony_watering_system {
namespace hardware {

class Master;

class SimulatedTemperatureSensor : public IReadNode, public ITemperatureSensor {
public:
  SimulatedTemperatureSensor(const std::string& name, Master& master);
  virtual ~SimulatedTemperatureSensor();

  virtual const std::string& getName() const override;

  virtual void doSample() override;

  virtual float getMin() const override;
  virtual float getMax() const override;
  virtual float getTemperatureInDegrees() const override;

private:
  const std::string name;

  std::chrono::steady_clock::time_point lastUpdate;
  int increment;
  float currentLevel;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_SIMULATEDTEMPERATURESENSOR_H_ */
