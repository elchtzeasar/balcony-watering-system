#include "Pump.h"

namespace balcony_watering_system {
namespace logic {

Pump::Pump() : started(false) {
}

Pump::~Pump() {
}

void Pump::start() {
  started = true;
}

void Pump::stop() {
  started = false;
}

bool Pump::isPumping() const {
  return started;
}

} /* namespace logic */
} /* namespace balcony_watering_system */
