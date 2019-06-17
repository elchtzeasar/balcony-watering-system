#ifndef LOGIC_SRC_PUMP_H_
#define LOGIC_SRC_PUMP_H_

#include <string>

namespace balcony_watering_system::configuration {
class IPumpConfiguration;
} /* namespace balcony_watering_system::configuration */

namespace balcony_watering_system::hardware {
class IMotorController;
} /* namespace balcony_watering_system::hardware */

namespace balcony_watering_system {
namespace logic {

class Pump {
public:
  Pump(const configuration::IPumpConfiguration& configuration,
       hardware::IMotorController& motorController);
  virtual ~Pump();

  const std::string& getName() const;

  void start();
  void stop();

  bool isPumping() const;

private:
  const std::string name;

  hardware::IMotorController& motorController;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_PUMP_H_ */
