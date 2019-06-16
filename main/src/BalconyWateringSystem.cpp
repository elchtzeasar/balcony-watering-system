#include "BalconyWateringSystem.h"

#include "TextGui.h"

namespace balcony_watering_system {
namespace main {

BalconyWateringSystem::BalconyWateringSystem(ui::TextGui& gui) :
    gui(gui) {
}

BalconyWateringSystem::~BalconyWateringSystem() {
}

void BalconyWateringSystem::run() {
  gui.run();
}

} /* namespace main */
} /* namespace balcony_watering_system */
