#ifndef HARDWARE_INCLUDE_ITEMPERATURESENSOR_H_
#define HARDWARE_INCLUDE_ITEMPERATURESENSOR_H_

#include "ISensor.h"

#include <string>

namespace balcony_watering_system {
namespace hardware {

class ITemperatureSensor : public virtual ISensor {
public:
  virtual ~ITemperatureSensor() = default;

  virtual const std::string& getName() const = 0;

  virtual float getMin() const = 0;
  virtual float getMax() const = 0;
  virtual float getTemperatureInDegrees() const = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_INCLUDE_ITEMPERATURESENSOR_H_ */
