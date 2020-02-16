#include "BalconyWateringSystem.h"

#include "App.h"
#include "Logic.h"
#include "Master.h"

#include <chrono>
#include <thread>

namespace balcony_watering_system {
namespace main {

using ::balcony_watering_system::logic::Logic;
using ::balcony_watering_system::hardware::Master;
using ::balcony_watering_system::app::App;
using ::std::this_thread::sleep_for;
using ::std::chrono::milliseconds;

BalconyWateringSystem::BalconyWateringSystem(Logic& logic,
                                             Master& master,
                                             App& app) :
    master(master),
    logic(logic),
    app(app) {
}

BalconyWateringSystem::~BalconyWateringSystem() {
}

void BalconyWateringSystem::run() {
  bool keepRunning = true;

  while (keepRunning) {
    master.doSampleNodes();

    keepRunning = app.exec();
    logic.control();

    master.doControlNodes();

    sleep_for(milliseconds(100));
  }

  master.doShutdownNodes();
}

} /* namespace main */
} /* namespace balcony_watering_system */
