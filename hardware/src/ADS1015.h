#ifndef HARDWARE_SRC_ADS1015_H_
#define HARDWARE_SRC_ADS1015_H_

#include "IReadNode.h"
#include "AnalogInput.h"

#include <vector>

namespace balcony_watering_system {
namespace hardware {

class Master;

class ADS1015 : public IReadNode {
 public:
  ADS1015(const std::string& namePrefix, Master& master);
  virtual ~ADS1015();

  virtual void doSample() override;

  virtual const std::vector<AnalogInput>& getAnalogInputs() const;

 private:
  Master& master;

  std::vector<AnalogInput> analogInputs;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif// HARDWARE_SRC_ADS1015_H_
