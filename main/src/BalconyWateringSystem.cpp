#include "BalconyWateringSystem.h"

namespace balcony_watering_system {
namespace main {

BalconyWateringSystem::BalconyWateringSystem() : pump(), gui(pump) {
}

BalconyWateringSystem::~BalconyWateringSystem() {
}

void BalconyWateringSystem::run() {
  gui.run();
}

} /* namespace main */
} /* namespace balcony_watering_system */
