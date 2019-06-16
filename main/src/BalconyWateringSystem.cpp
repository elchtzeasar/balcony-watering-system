#include "BalconyWateringSystem.h"

#include "TextGui.h"

#include <chrono>
#include <thread>

namespace balcony_watering_system {
namespace main {

using ::std::this_thread::sleep_for;
using ::std::chrono::milliseconds;

BalconyWateringSystem::BalconyWateringSystem(ui::TextGui& gui) :
    gui(gui) {
}

BalconyWateringSystem::~BalconyWateringSystem() {
}

void BalconyWateringSystem::run() {
  bool keepRunning = true;

  while (keepRunning) {
    keepRunning = gui.exec();

    sleep_for(milliseconds(100));
  }
}

} /* namespace main */
} /* namespace balcony_watering_system */
