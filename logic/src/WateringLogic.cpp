#include "WateringLogic.h"

#include "Logic.h"
#include "HumidityMeasurement.h"
#include "Pump.h"
#include "SoilMoistureMeasurement.h"
#include "TemperatureMeasurement.h"

#include <cassert>
#include <ctime>
#include <iomanip>

namespace std {
ostream& operator<<(ostream& stream, const chrono::steady_clock::time_point& time_point);
}

namespace balcony_watering_system {
namespace logic {

using ::std::chrono::seconds;
using ::std::chrono::steady_clock;
using ::std::chrono::system_clock;

WateringLogic::WateringLogic(
    Logic& logic,
    SoilMoistureMeasurement const* soil,
    TemperatureMeasurement const* temperature,
    HumidityMeasurement const* humidity,
    Pump* pump,
    const seconds& timeToWater,
    const seconds& timeToNotWater) :
  soil(soil),
  temperature(temperature),
  humidity(humidity),
  pump(*pump),
  timeToWater(timeToWater),
  timeToNotWater(timeToNotWater),
  transitionTime(),
  state(State::IDLE),
  logger("logic.watering-logic.logic") {
  assert(pump != nullptr);

  logic.registerNode(*this);
}

void WateringLogic::control() {
  State newState = state;

  switch (state) {
  case State::IDLE: {
    const bool shouldWater = handleIdle();

    if (shouldWater) {
      newState = State::WATERING;
    }
    else {
      newState = State::NOT_WATERING;
    }
  } break;
  case State::WATERING: {
    const bool wateringDone = handleWatering();
    if (wateringDone) {
      newState = State::NOT_WATERING;
    }
  } break;
  case State::NOT_WATERING: {
    const bool transition = handleNotWatering();
    if (transition) {
      newState = State::IDLE;
    }
  } break;
  }

  if (newState != state) {
    switch (newState) {
    case State::WATERING:
      pump.start();
      transitionTime = steady_clock::now() + timeToWater;
      break;
    case State::NOT_WATERING:
      pump.stop();
      transitionTime = steady_clock::now() + timeToNotWater;
      break;
    case State::IDLE:
      break;
    }

    state = newState;
  }
}

WateringLogic::State WateringLogic::getState() const {
  return state;
}

bool WateringLogic::handleIdle() const {
  const bool temperatureReady =
      temperature == nullptr || temperature->readyToWater();
  const bool soilReady =
      soil == nullptr || soil->readyToWater();
  const bool humidityReady =
      humidity == nullptr || humidity->readyToWater();

  const bool shouldWater = temperatureReady && soilReady && humidityReady;

  LOG_DEBUG(logger, "handleIdle - temperatureReady=" << temperatureReady
      << ", soilReady=" << soilReady
      << ", humidityReady=" << humidityReady
      << " => shouldWater=" << shouldWater);

  return shouldWater;
}

bool WateringLogic::handleWatering() const {
  const auto now = steady_clock::now();

  const bool wateringDone = transitionTime < now;

  LOG_DEBUG(logger, "handleWatering - now=" << now
      << ", transitionTime=" << transitionTime
      << " => wateringDone=" << wateringDone);

  return wateringDone;
}

bool WateringLogic::handleNotWatering() const {
  const auto now = steady_clock::now();

  const bool wateringDone = transitionTime < now;

  LOG_DEBUG(logger, "handleNotWatering - now=" << now
      << ", transitionTime=" << transitionTime
      << " => wateringDone=" << wateringDone);

  return wateringDone;
}

std::ostream& operator<<(std::ostream& stream, const WateringLogic::State& state) {
  switch (state) {
  case WateringLogic::State::IDLE: stream << "IDLE"; break;
  case WateringLogic::State::WATERING: stream << "WATERING"; break;
  case WateringLogic::State::NOT_WATERING: stream << "NOT_WATERING"; break;
  default: stream << "UNKNOWN: " << int(state); break;
  }

  return stream;
}

} /* namespace logic */
} /* namespace balcony_watering_system */

namespace std {

using namespace ::std::chrono;

ostream &operator<<(ostream &stream, const steady_clock::time_point& steadyT) {
  const auto timeFromNow = duration_cast<system_clock::duration>(steadyT - steady_clock::now());
  const system_clock::time_point systemT = system_clock::now() + timeFromNow;
  const time_t time = system_clock::to_time_t(systemT);

  struct tm tm;
  localtime_r(&time, &tm);
  return stream << std::put_time(&tm, "%c");
}

}
