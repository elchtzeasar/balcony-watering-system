#ifndef LOGIC_SRC_SOILMOISTUREMEASUREMENT_H_
#define LOGIC_SRC_SOILMOISTUREMEASUREMENT_H_

#include "Logger.h"

#include <string>
#include <vector>

namespace balcony_watering_system::configuration {
class ISoilMoistureMeasurementConfiguration;
} /* namespace balcony_watering_system::configuration */

namespace balcony_watering_system::hardware {
class ISoilMoistureSensor;
} /* namespace balcony_watering_system::hardware */

namespace balcony_watering_system {
namespace logic {

class SoilMoistureMeasurement {
public:
  SoilMoistureMeasurement(const configuration::ISoilMoistureMeasurementConfiguration& configuration,
                          const std::vector<hardware::ISoilMoistureSensor*>& sensor);
  virtual ~SoilMoistureMeasurement();

  const std::string& getName() const;

  int getMoistureInPercent() const;
  bool readyToWater() const;

private:
  const std::string name;
  const int threshold;
  const std::vector<hardware::ISoilMoistureSensor*> sensors;

  const platform::Logger logger;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_SOILMOISTUREMEASUREMENT_H_ */
