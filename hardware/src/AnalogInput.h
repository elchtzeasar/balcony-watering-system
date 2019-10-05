#ifndef HARDWARE_SRC_ANALOGINPUT_H_
#define HARDWARE_SRC_ANALOGINPUT_H_

#include "IAnalogInput.h"

namespace balcony_watering_system {
namespace hardware {

class AnalogInput : public IAnalogInput {
public:
  AnalogInput(const std::string& name, float min, float max);
  virtual ~AnalogInput() = default;

  void setCurrentVoltage(float voltage);

  virtual const std::string& getName() const override;
  virtual float getMin() const override;
  virtual float getMax() const override;
  virtual float getCurrentVoltage() const override;

private:
  const std::string name;
  const float min;
  const float max;
  float currentVoltage;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_ANALOGINPUT_H_ */
