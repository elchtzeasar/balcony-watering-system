#include "Pump.h"

#include "IPumpConfiguration.h"

namespace balcony_watering_system {
namespace logic {

using ::balcony_watering_system::configuration::IPumpConfiguration;
using ::std::string;

Pump::Pump(const IPumpConfiguration& configuration) :
    started(false),
    name(configuration.getName()) {
}

Pump::~Pump() {
}

const string& Pump::getName() const {
  return name;
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
