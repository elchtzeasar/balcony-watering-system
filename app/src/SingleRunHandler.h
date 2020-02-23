#ifndef APP_SRC_SINGLERUNHANDLER_H_
#define APP_SRC_SINGLERUNHANDLER_H_

#include "Logger.h"

namespace balcony_watering_system::hardware {
  class IArduino;
  class HWFactory;
}

namespace balcony_watering_system::logic {
  class LogicFactory;
  class WateringLogic;
}

namespace balcony_watering_system {
namespace app {

class SingleRunHandler {
public:
  SingleRunHandler(const logic::LogicFactory& logicFactory, const hardware::HWFactory& hwFactory);
  virtual ~SingleRunHandler();

  bool exec();

private:
  const logic::WateringLogic& wateringLogic;

  hardware::IArduino& arduino;

  const platform::Logger logger;
};

} /* namespace app */
} /* namespace balcony_watering_system */

#endif /* APP_SRC_SINGLERUNHANDLER_H_ */
