#include "App.h"

#include "IAppConfiguration.h"
#include "ConfigurationFile.h"
#include "SingleRunHandler.h"
#include "TextGui.h"

#include <cassert>
#include <variant>

namespace balcony_watering_system {
namespace app {

using ::balcony_watering_system::configuration::IAppConfiguration;
using ::balcony_watering_system::configuration::ConfigurationFile;
using ::balcony_watering_system::hardware::HWFactory;
using ::balcony_watering_system::logic::LogicFactory;
using ::std::chrono::milliseconds;

class App::Pimpl {
public:
  Pimpl(const ConfigurationFile& configurationFile,
        const LogicFactory& logicFactory,
        const HWFactory& hwFactory) :
          cycleTime(configurationFile.getAppConfiguration().getCycleTime()),
          app(false) {
    const auto& configuration = configurationFile.getAppConfiguration();
    const auto mode = configuration.getMode();

    switch (mode) {
    case IAppConfiguration::Mode::TEXT_GUI:
      app.emplace<TextGui>(logicFactory, hwFactory);
      break;
    case IAppConfiguration::Mode::SINGLE_RUN:
      app.emplace<SingleRunHandler>(logicFactory, hwFactory);
      break;
    default:
      break;
    }
  }

  bool exec() {
    if(TextGui* ui = std::get_if<TextGui>(&app)) {
      return ui->exec();
    }
    else if(SingleRunHandler* handler = std::get_if<SingleRunHandler>(&app)) {
      return handler->exec();
    }
    return true;
  }

  const milliseconds& getCycleTime() const {
    return cycleTime;
  }

private:
  std::variant<bool, TextGui, SingleRunHandler> app;
  const milliseconds cycleTime;
};

App::App(const ConfigurationFile& configuration,
         const LogicFactory& logicFactory,
         const HWFactory& hwFactory) :
      pimpl(new Pimpl(configuration, logicFactory, hwFactory)) {
}

App::~App() {
  delete pimpl;
}

bool App::exec() {
  return pimpl->exec();
}

const milliseconds& App::getCycleTime() const {
  return pimpl->getCycleTime();
}

} /* namespace app */
} /* namespace balcony_watering_system */
