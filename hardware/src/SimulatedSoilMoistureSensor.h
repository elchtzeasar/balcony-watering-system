#ifndef HARDWARE_SRC_SIMULATEDSOILMOISTURESENSOR_H_
#define HARDWARE_SRC_SIMULATEDSOILMOISTURESENSOR_H_

#include "IReadNode.h"
#include "ISoilMoistureSensor.h"

#include <chrono>

namespace balcony_watering_system {
namespace hardware {

class Master;

class SimulatedSoilMoistureSensor : public IReadNode, public ISoilMoistureSensor {
public:
  SimulatedSoilMoistureSensor(const std::string& name, Master& master);
  virtual ~SimulatedSoilMoistureSensor();

  virtual const std::string& getName() const override;

  virtual void doSample() override;
  virtual int getMoistureInPercent() const override;

private:
  const std::string name;

  std::chrono::steady_clock::time_point lastUpdate;
  int increment;
  int currentLevel;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_SIMULATEDSOILMOISTURESENSOR_H_ */
