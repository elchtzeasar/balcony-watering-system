#ifndef HARDWARE_INCLUDE_ISOILMOISTURESENSOR_H_
#define HARDWARE_INCLUDE_ISOILMOISTURESENSOR_H_

#include "ISensor.h"

#include <string>

namespace balcony_watering_system {
namespace hardware {

class ISoilMoistureSensor : public virtual ISensor {
public:
  virtual ~ISoilMoistureSensor() = default;

  virtual int getMoistureInPercent() const = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_INCLUDE_ISOILMOISTURESENSOR_H_ */
