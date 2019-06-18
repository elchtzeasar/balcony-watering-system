#ifndef HARDWARE_INCLUDE_IHUMIDITYSENSOR_H_
#define HARDWARE_INCLUDE_IHUMIDITYSENSOR_H_

#include <string>

namespace balcony_watering_system {
namespace hardware {

class IHumiditySensor {
public:
  virtual ~IHumiditySensor() = default;

  virtual const std::string& getName() const = 0;

  virtual int getHumidityInPercent() const = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_INCLUDE_IHUMIDITYSENSOR_H_ */
