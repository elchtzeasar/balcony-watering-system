#include "Pump.h"

#include "IPumpConfiguration.h"
#include "IMotorController.h"

namespace balcony_watering_system {
namespace logic {

using ::balcony_watering_system::configuration::IPumpConfiguration;
using ::balcony_watering_system::hardware::IMotorController;
using ::std::string;

Pump::Pump(const IPumpConfiguration& configuration, IMotorController& motorController) :
    name(configuration.getName()),
    motorController(motorController) {
}

Pump::~Pump() {
}

const string& Pump::getName() const {
  return name;
}

void Pump::start() {
  motorController.runInPercent(100);
}

void Pump::stop() {
  motorController.runInPercent(0);
}

bool Pump::isPumping() const {
  return motorController.getCurrentSpeedInPercentage() > 0;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
