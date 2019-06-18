#ifndef LOGIC_SRC_VOLUMEMEASUREMENT_H_
#define LOGIC_SRC_VOLUMEMEASUREMENT_H_

#include <string>
#include <vector>

namespace balcony_watering_system::configuration {
class IVolumeMeasurementConfiguration;
} /* namespace balcony_watering_system::configuration */

namespace balcony_watering_system::hardware {
class IDistanceSensor;
} /* namespace balcony_watering_system::hardware */

namespace balcony_watering_system {
namespace logic {

class VolumeMeasurement {
public:
  VolumeMeasurement(const configuration::IVolumeMeasurementConfiguration& configuration,
                     const hardware::IDistanceSensor& sensor);
  virtual ~VolumeMeasurement();

  const std::string& getName() const;

  double getMin() const;
  double getMax() const;
  double getVolumeInLiters() const;

private:
  const std::string name;
  const double areaInSquareMeters;
  const hardware::IDistanceSensor& sensor;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_VOLUMEMEASUREMENT_H_ */
