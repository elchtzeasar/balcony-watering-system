#include "BalconyWateringSystem.h"
#include "ConfigurationFile.h"
#include "HWFactory.h"
#include "LogicFactory.h"
#include "Master.h"
#include "TextGui.h"

#include <boost/di.hpp>

using balcony_watering_system::configuration::ConfigurationFile;
using balcony_watering_system::main::BalconyWateringSystem;
using balcony_watering_system::logic::LogicFactory;
using balcony_watering_system::hardware::HWFactory;
using boost::di::make_injector;

int main(int argc, char **argv) {
  auto injector = make_injector();

  auto& configuration = injector.create<ConfigurationFile&>();
  configuration.parse();

  auto& hwFactory = injector.create<HWFactory&>();
  hwFactory.create();

  auto& logicFactory = injector.create<LogicFactory&>();
  logicFactory.create();

  auto& system = injector.create<BalconyWateringSystem&>();
  system.run();

	return 0;
}
