#include "BalconyWateringSystem.h"
#include "TextGui.h"
#include "Pump.h"
#include "SoilMoistureSensor.h"

#include <boost/di.hpp>

using balcony_watering_system::main::BalconyWateringSystem;
using boost::di::make_injector;

int main(int argc, char **argv) {
  auto injector = make_injector();

  auto system = injector.create<BalconyWateringSystem>();
  system.run();

	return 0;
}
