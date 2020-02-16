#include "App.h"

#include "TextGui.h"

namespace balcony_watering_system {
namespace app {

using ::balcony_watering_system::hardware::HWFactory;
using ::balcony_watering_system::logic::LogicFactory;

class App::Pimpl {
public:
  Pimpl(const LogicFactory& logicFactory,
        const HWFactory& hwFactory) : ui(logicFactory, hwFactory) {}

  bool exec() {
    return ui.exec();
  }
private:
  TextGui ui;
};

App::App(const LogicFactory& logicFactory,
         const HWFactory& hwFactory) :
      pimpl(new Pimpl(logicFactory, hwFactory)) {
}

App::~App() {
  delete pimpl;
}

bool App::exec() {
  return pimpl->exec();
}

} /* namespace app */
} /* namespace balcony_watering_system */
