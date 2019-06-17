#include "SimulatedMotor.h"

namespace balcony_watering_system {
namespace hardware {

using ::std::string;

SimulatedMotor::SimulatedMotor(const string& name) :
    name(name),
    currentSpeed(0) {
}

SimulatedMotor::~SimulatedMotor() {
}

const string& SimulatedMotor::getName() const {
  return name;
}

void SimulatedMotor::runInPercent(int percentage) {
  currentSpeed = percentage;
}

int SimulatedMotor::getCurrentSpeedInPercentage() const {
  return currentSpeed;
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
