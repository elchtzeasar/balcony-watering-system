#ifndef CONFIGURATION_SRC_WATERINGLOGIC_H_
#define CONFIGURATION_SRC_WATERINGLOGIC_H_

#include "ILogicNode.h"

#include "Logger.h"

#include <chrono>
#include <iosfwd>

namespace balcony_watering_system {
namespace logic {

class Logic;
class HumidityMeasurement;
class Pump;
class SoilMoistureMeasurement;
class TemperatureMeasurement;

class WateringLogic : public ILogicNode {
public:
  WateringLogic(
      Logic& logic,
      SoilMoistureMeasurement const* soil,
      TemperatureMeasurement const* temperature,
      HumidityMeasurement const* humidity,
      Pump* pump,
      const std::chrono::seconds& timeToWater,
      const std::chrono::seconds& timeToNotWater);
  virtual ~WateringLogic() = default;

  virtual void control() override;

  enum class State {
    IDLE,
    WATERING,
    NOT_WATERING,
  };
  State getState() const;

private:
  bool handleIdle() const;
  bool handleWatering() const;
  bool handleNotWatering() const;

  SoilMoistureMeasurement const* soil;
  TemperatureMeasurement const* temperature;
  HumidityMeasurement const* humidity;
  Pump& pump;

  const std::chrono::seconds timeToWater;
  const std::chrono::seconds timeToNotWater;
  std::chrono::time_point<std::chrono::steady_clock> transitionTime;

  State state;

  platform::Logger logger;
};

std::ostream& operator<<(std::ostream& stream, const WateringLogic::State& state);

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_WATERINGLOGIC_H_ */
