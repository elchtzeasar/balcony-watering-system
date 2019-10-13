#include "AnalogSoilMoistureSensor.h"

#include "IAnalogInput.h"
#include "Master.h"

#include <algorithm>

namespace balcony_watering_system {
namespace hardware {

using ::std::max;
using ::std::min;
using ::std::string;

AnalogSoilMoistureSensor::AnalogSoilMoistureSensor(const string& name,
                                                   float waterVoltageInVolts,
                                                   float dryVoltageInVolts,
                                                   const IAnalogInput& analogInput,
                                                   Master& master) :
  name(name),
  waterVoltageInVolts(waterVoltageInVolts),
  dryVoltageInVolts(dryVoltageInVolts),
  analogInput(analogInput),
  currentPercentage(0) {
  master.registerAdapterNode(*this);
}

AnalogSoilMoistureSensor::~AnalogSoilMoistureSensor() {
}

const string& AnalogSoilMoistureSensor::getName() const {
  return name;
}

void AnalogSoilMoistureSensor::doSample() {
  const float currentVoltage = analogInput.getCurrentVoltage();

  const float currentDryFactor = (currentVoltage - waterVoltageInVolts) / (dryVoltageInVolts - waterVoltageInVolts);
  const float currentMoistureFactor = 1 - currentDryFactor;

  currentPercentage = max<float>(0, min<float>(100, currentMoistureFactor * 100.0));
}

int AnalogSoilMoistureSensor::getMoistureInPercent() const {
  return currentPercentage;
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
