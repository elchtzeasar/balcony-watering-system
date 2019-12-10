#include "BalconyWateringSystem.h"

#include "Logic.h"
#include "TextGui.h"
#include "Master.h"

#include <chrono>
#include <thread>

namespace balcony_watering_system {
namespace main {

using ::std::this_thread::sleep_for;
using ::std::chrono::milliseconds;

BalconyWateringSystem::BalconyWateringSystem(
    logic::Logic& logic, hardware::Master& master, ui::TextGui& gui) :
    master(master),
    logic(logic),
    gui(gui) {
}

BalconyWateringSystem::~BalconyWateringSystem() {
}

void BalconyWateringSystem::run() {
  bool keepRunning = true;

  while (keepRunning) {
    master.doSampleNodes();

    keepRunning = gui.exec();
    logic.control();

    master.doControlNodes();

    sleep_for(milliseconds(100));
  }

  master.doShutdownNodes();
}

} /* namespace main */
} /* namespace balcony_watering_system */
