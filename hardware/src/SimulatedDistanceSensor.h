#ifndef HARDWARE_SRC_SIMULATEDDISTANCESENSOR_H_
#define HARDWARE_SRC_SIMULATEDDISTANCESENSOR_H_

#include "IReadNode.h"
#include "IDistanceSensor.h"

#include <chrono>

namespace balcony_watering_system {
namespace hardware {

class Master;

class SimulatedDistanceSensor : public IReadNode, public IDistanceSensor {
public:
  SimulatedDistanceSensor(const std::string& name, Master& master);
  virtual ~SimulatedDistanceSensor();

  virtual const std::string& getName() const override;

  virtual void doSample() override;

  virtual int getMin() const override;
  virtual int getMax() const override;
  virtual int getDistanceInMillimeters() const override;

private:
  const std::string name;

  std::chrono::steady_clock::time_point lastUpdate;
  int increment;
  int currentLevel;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_SIMULATEDDISTANCESENSOR_H_ */
