#ifndef HARDWARE_INCLUDE_ISOILMOISTURESENSOR_H_
#define HARDWARE_INCLUDE_ISOILMOISTURESENSOR_H_

#include <string>

namespace balcony_watering_system {
namespace hardware {

class ISoilMoistureSensor {
public:
  virtual ~ISoilMoistureSensor() = default;

  virtual const std::string& getName() const = 0;

  virtual int getMoistureLevelInPercent() const = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_INCLUDE_ISOILMOISTURESENSOR_H_ */
