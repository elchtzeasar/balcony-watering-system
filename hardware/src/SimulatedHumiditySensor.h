#ifndef HARDWARE_SRC_SIMULATEDHUMIDITYSENSOR_H_
#define HARDWARE_SRC_SIMULATEDHUMIDITYSENSOR_H_

#include "IReadNode.h"
#include "IHumiditySensor.h"

#include <chrono>

namespace balcony_watering_system {
namespace hardware {

class Master;

class SimulatedHumiditySensor : public IReadNode, public IHumiditySensor {
public:
  SimulatedHumiditySensor(const std::string& name, Master& master);
  virtual ~SimulatedHumiditySensor();

  virtual const std::string& getName() const override;

  virtual void doSample() override;
  virtual float getHumidityInPercent() const override;

private:
  const std::string name;

  std::chrono::steady_clock::time_point lastUpdate;
  int increment;
  float currentLevel;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_SIMULATEDHUMIDITYSENSOR_H_ */
