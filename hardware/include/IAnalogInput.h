#ifndef HARDWARE_INCLUDE_IANALOGINPUT_H_
#define HARDWARE_INCLUDE_IANALOGINPUT_H_

#include "ISensor.h"

#include <string>

namespace balcony_watering_system {
namespace hardware {

class IAnalogInput : public virtual ISensor {
public:
  virtual ~IAnalogInput() = default;

  virtual float getMin() const = 0;
  virtual float getMax() const = 0;
  virtual float getCurrentVoltage() const = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_INCLUDE_IANALOGINPUT_H_ */
