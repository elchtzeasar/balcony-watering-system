#ifndef HARDWARE_INCLUDE_ITEMPERATURESENSOR_H_
#define HARDWARE_INCLUDE_ITEMPERATURESENSOR_H_

#include <string>

namespace balcony_watering_system {
namespace hardware {

class ITemperatureSensor {
public:
  virtual ~ITemperatureSensor() = default;

  virtual const std::string& getName() const = 0;

  virtual int getMin() const = 0;
  virtual int getMax() const = 0;
  virtual int getTemperatureInDegrees() const = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_INCLUDE_ITEMPERATURESENSOR_H_ */
