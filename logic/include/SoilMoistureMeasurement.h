#ifndef LOGIC_SRC_SOILMOISTUREMEASUREMENT_H_
#define LOGIC_SRC_SOILMOISTUREMEASUREMENT_H_

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

  int getMoistureLevelInPercent() const;

private:
  const std::string name;
  const std::vector<hardware::ISoilMoistureSensor*> sensors;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_SOILMOISTUREMEASUREMENT_H_ */
