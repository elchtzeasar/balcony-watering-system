#ifndef LOGIC_SRC_SOILMOISTURESENSOR_H_
#define LOGIC_SRC_SOILMOISTURESENSOR_H_

namespace balcony_watering_system {
namespace logic {

class SoilMoistureSensor {
public:
  SoilMoistureSensor();
  virtual ~SoilMoistureSensor();

  int getMoistureLevel() const;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_SOILMOISTURESENSOR_H_ */
