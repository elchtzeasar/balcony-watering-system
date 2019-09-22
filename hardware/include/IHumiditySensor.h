#ifndef HARDWARE_INCLUDE_IHUMIDITYSENSOR_H_
#define HARDWARE_INCLUDE_IHUMIDITYSENSOR_H_

#include "ISensor.h"

#include <string>

namespace balcony_watering_system {
namespace hardware {

class IHumiditySensor : public virtual ISensor {
public:
  virtual ~IHumiditySensor() = default;

  virtual const std::string& getName() const = 0;

  virtual float getHumidityInPercent() const = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_INCLUDE_IHUMIDITYSENSOR_H_ */
