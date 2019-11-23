/*
 * PwmMotorController.h
 *
 *  Created on: Nov 19, 2019
 *      Author: peter
 */

#ifndef HARDWARE_SRC_PWMMOTORCONTROLLER_H_
#define HARDWARE_SRC_PWMMOTORCONTROLLER_H_

#include "IMotorController.h"
#include "IWriteNode.h"

#include "Logger.h"
#include "OutputPin.h"
#include "PwmPin.h"

#include <string>

namespace balcony_watering_system {
namespace hardware {

class Master;

class PwmMotorController : public IMotorController, public IWriteNode {
public:
  PwmMotorController(const std::string& name, int output0Pin, int output1Pin, int pwmPin, Master& master);
  virtual ~PwmMotorController();

  virtual const std::string& getName() const override;

  virtual void runInPercent(int percentage) override;
  virtual int getCurrentSpeedInPercentage() const override;

  virtual void doControl() const override;
  virtual void doShutdown() const override;

private:
  const std::string name;

  OutputPin output0;
  OutputPin output1;
  PwmPin pwm;

  int currentSpeedInPercent;

  const platform::Logger logger;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_PWMMOTORCONTROLLER_H_ */
