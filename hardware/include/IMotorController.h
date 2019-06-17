#ifndef HARDWARE_INCLUDE_IMOTORCONTROLLER_H_
#define HARDWARE_INCLUDE_IMOTORCONTROLLER_H_

#include <string>

namespace balcony_watering_system {
namespace hardware {

class IMotorController {
public:
  virtual ~IMotorController() = default;

  virtual const std::string& getName() const = 0;

  virtual void runInPercent(int percentage) = 0;
  virtual int getCurrentSpeedInPercentage() const = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_INCLUDE_IMOTORCONTROLLER_H_ */
