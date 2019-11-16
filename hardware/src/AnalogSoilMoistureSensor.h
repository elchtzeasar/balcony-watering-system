#ifndef HARDWARE_SRC_ANALOGSOILMOISTURESENSOR_H_
#define HARDWARE_SRC_ANALOGSOILMOISTURESENSOR_H_

#include "IAdapterNode.h"
#include "ISoilMoistureSensor.h"

#include "Logger.h"

namespace balcony_watering_system {
namespace hardware {

class IAnalogInput;
class Master;

class AnalogSoilMoistureSensor : public IAdapterNode, public ISoilMoistureSensor {
public:
  AnalogSoilMoistureSensor(const std::string& name,
                           float waterVoltageInVolts,
                           float dryVoltageInVolts,
                           const IAnalogInput& analogInput,
                           Master& master);
  virtual ~AnalogSoilMoistureSensor();

  virtual const std::string& getName() const override;

  virtual void doSample() override;
  virtual int getMoistureInPercent() const override;

private:
  const std::string name;
  const float waterVoltageInVolts;
  const float dryVoltageInVolts;

  const IAnalogInput& analogInput;

  float currentPercentage;

  const platform::Logger logger;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_ANALOGSOILMOISTURESENSOR_H_ */
