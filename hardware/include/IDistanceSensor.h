#ifndef HARDWARE_INCLUDE_IDISTANCESENSOR_H_
#define HARDWARE_INCLUDE_IDISTANCESENSOR_H_

#include <string>

namespace balcony_watering_system {
namespace hardware {

class IDistanceSensor {
public:
  virtual ~IDistanceSensor() = default;

  virtual const std::string& getName() const = 0;

  virtual int getMin() const = 0;
  virtual int getMax() const = 0;
  virtual int getDistanceInMillimeters() const = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_INCLUDE_IDISTANCESENSOR_H_ */
