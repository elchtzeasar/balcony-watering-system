#ifndef HARDWARE_SRC_SIMULATEDMOTOR_H_
#define HARDWARE_SRC_SIMULATEDMOTOR_H_

#include "IMotorController.h"

#include <string>

namespace balcony_watering_system {
namespace hardware {

class SimulatedMotor : public IMotorController{
public:
  SimulatedMotor(const std::string& name);
  virtual ~SimulatedMotor();

  virtual const std::string& getName() const override;

  virtual void runInPercent(int percentage) override;
  virtual int getCurrentSpeedInPercentage() const override;

private:
  const std::string name;
  int currentSpeed;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_SIMULATEDMOTOR_H_ */
