#ifndef LOGIC_SRC_TEMPERATUREMEASUREMENT_H_
#define LOGIC_SRC_TEMPERATUREMEASUREMENT_H_

#include <string>
#include <vector>

namespace balcony_watering_system::configuration {
class ITemperatureMeasurementConfiguration;
} /* namespace balcony_watering_system::configuration */

namespace balcony_watering_system::hardware {
class ITemperatureSensor;
} /* namespace balcony_watering_system::hardware */

namespace balcony_watering_system {
namespace logic {

class TemperatureMeasurement {
public:
  TemperatureMeasurement(const configuration::ITemperatureMeasurementConfiguration& configuration,
                     const std::vector<hardware::ITemperatureSensor*>& sensor);
  virtual ~TemperatureMeasurement();

  const std::string& getName() const;

  float getMin() const;
  float getMax() const;
  float getTemperatureInDegrees() const;

private:
  const std::string name;
  const std::vector<hardware::ITemperatureSensor*> sensors;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_TEMPERATUREMEASUREMENT_H_ */
