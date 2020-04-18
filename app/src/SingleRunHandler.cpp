#include "SingleRunHandler.h"

#include "IArduino.h"
#include "HWFactory.h"
#include "LogicFactory.h"
#include "WateringLogic.h"

#include <string>
#include <iostream>

namespace balcony_watering_system {
namespace app {

using ::balcony_watering_system::hardware::HWFactory;
using ::balcony_watering_system::logic::LogicFactory;
using ::balcony_watering_system::logic::WateringLogic;

SingleRunHandler::SingleRunHandler(const LogicFactory& logicFactory, const HWFactory& hwFactory) :
    wateringLogic(logicFactory.getWateringLogic()),
    arduino(hwFactory.getArduino()),
    logger("app.single-run") {
}

SingleRunHandler::~SingleRunHandler() {
}

bool SingleRunHandler::exec() {
  const auto state = wateringLogic.getState();

  bool keepRunning;

  switch (state) {
  case WateringLogic::State::IDLE:
  case WateringLogic::State::NOT_WATERING:
    keepRunning = false;
    LOG_INFO(logger, "state=" << state << " => shutting down");
    break;
  case WateringLogic::State::WATERING:
    keepRunning = true;
    LOG_INFO(logger, "state=" << state << " => waiting");
    break;
  default:
    keepRunning = true;
    LOG_FATAL(logger, "unknown state=" << int(state) << " => shutting down");
    break;
  }

  if (!keepRunning && arduino.isShutdownEnabled()) {
    arduino.shutdown();
    system("shutdown -h now");
    exit(0);
  }

  return keepRunning;
}

} /* namespace app */
} /* namespace balcony_watering_system */
