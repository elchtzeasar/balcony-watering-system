#ifndef LOGIC_SRC_HUMIDITYMEASUREMENT_H_
#define LOGIC_SRC_HUMIDITYMEASUREMENT_H_

#include <string>
#include <vector>

namespace balcony_watering_system::configuration {
class IHumidityMeasurementConfiguration;
} /* namespace balcony_watering_system::configuration */

namespace balcony_watering_system::hardware {
class IHumiditySensor;
} /* namespace balcony_watering_system::hardware */

namespace balcony_watering_system {
namespace logic {

class HumidityMeasurement {
public:
  HumidityMeasurement(const configuration::IHumidityMeasurementConfiguration& configuration,
                     const std::vector<hardware::IHumiditySensor*>& sensor);
  virtual ~HumidityMeasurement();

  const std::string& getName() const;

  float getHumidityInPercent() const;

private:
  const std::string name;
  const std::vector<hardware::IHumiditySensor*> sensors;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_HUMIDITYMEASUREMENT_H_ */
