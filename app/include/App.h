#ifndef APP_INCLUDE_APP_H_
#define APP_INCLUDE_APP_H_

#include <chrono>

namespace balcony_watering_system::configuration {
class ConfigurationFile;
}
namespace balcony_watering_system::logic {
class LogicFactory;
}
namespace balcony_watering_system::hardware {
class HWFactory;
}

namespace balcony_watering_system {
namespace app {

class App {
public:
  App(const configuration::ConfigurationFile& configuration,
      const logic::LogicFactory& logicFactory,
      const hardware::HWFactory& hwFactory);
  virtual ~App();

  bool exec();

  const std::chrono::milliseconds& getCycleTime() const;

private:
  class Pimpl;
  Pimpl* pimpl;
};

} /* namespace app */
} /* namespace balcony_watering_system */

#endif /* APP_INCLUDE_APP_H_ */
