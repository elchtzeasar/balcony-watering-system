#ifndef MAIN_SRC_BALCONYWATERINGSYSTEM_H_
#define MAIN_SRC_BALCONYWATERINGSYSTEM_H_

#include "Pump.h"
#include "SoilMoistureSensor.h"
#include "TextGui.h"

namespace balcony_watering_system {
namespace main {

class BalconyWateringSystem {
public:
  BalconyWateringSystem();
  virtual ~BalconyWateringSystem();

  void run();

private:
  logic::Pump pump;
  logic::SoilMoistureSensor soilSensor;
  ui::TextGui gui;
};

} /* namespace main */
} /* namespace balcony_watering_system */

#endif /* MAIN_SRC_BALCONYWATERINGSYSTEM_H_ */
