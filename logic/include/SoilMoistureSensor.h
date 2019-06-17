#ifndef LOGIC_SRC_SOILMOISTURESENSOR_H_
#define LOGIC_SRC_SOILMOISTURESENSOR_H_

#include <string>

namespace balcony_watering_system::configuration {
class ISoilMoistureSensorConfiguration;
} /* namespace balcony_watering_system::configuration */

namespace balcony_watering_system::hardware {
class ISoilMoistureSensor;
} /* namespace balcony_watering_system::hardware */

namespace balcony_watering_system {
namespace logic {

class SoilMoistureSensor {
public:
  SoilMoistureSensor(const configuration::ISoilMoistureSensorConfiguration& configuration,
                     const hardware::ISoilMoistureSensor& sensor);
  virtual ~SoilMoistureSensor();

  const std::string& getName() const;

  int getMoistureLevelInPercent() const;

private:
  const std::string name;
  const hardware::ISoilMoistureSensor& sensor;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_SOILMOISTURESENSOR_H_ */
