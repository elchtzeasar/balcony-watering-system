#include "BalconyWateringSystem.h"
#include "ConfigurationFile.h"
#include "Pump.h"
#include "SoilMoistureSensor.h"
#include "LogicFactory.h"
#include "TextGui.h"

#include <boost/di.hpp>

using balcony_watering_system::configuration::ConfigurationFile;
using balcony_watering_system::main::BalconyWateringSystem;
using balcony_watering_system::logic::LogicFactory;
using boost::di::make_injector;

int main(int argc, char **argv) {
  auto injector = make_injector();

  auto& configuration = injector.create<ConfigurationFile&>();
  configuration.parse();

  auto& logicFactory = injector.create<LogicFactory&>();
  logicFactory.create();

  auto& system = injector.create<BalconyWateringSystem&>();
  system.run();

	return 0;
}
