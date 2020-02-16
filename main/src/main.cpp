#include "BalconyWateringSystem.h"
#include "ConfigurationFile.h"
#include "HWFactory.h"
#include "Logic.h"
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

  ConfigurationFile& configuration = injector.create<ConfigurationFile&>();
  configuration.parse();

  HWFactory& hwFactory = injector.create<HWFactory&>();
  hwFactory.create();

  LogicFactory& logicFactory = injector.create<LogicFactory&>();
  logicFactory.create();

  BalconyWateringSystem& system = injector.create<BalconyWateringSystem&>();
  system.run();

	return 0;
}
