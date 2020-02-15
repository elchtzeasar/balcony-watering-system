#ifndef HARDWARE_SRC_ARDUINO_H_
#define HARDWARE_SRC_ARDUINO_H_

#include "IReadNode.h"
#include "AnalogInput.h"

#include "Logger.h"

#include <vector>

namespace balcony_watering_system {
namespace hardware {

class Master;

class Arduino : public IReadNode {
 public:
  Arduino(int address, const std::string& namePrefix, Master& master);
  virtual ~Arduino();

  virtual void doSample() override;

  virtual const std::vector<AnalogInput>& getAnalogInputs() const;

 private:
  const int address;
  Master& master;

  std::vector<AnalogInput> analogInputs;

  const platform::Logger logger;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif// HARDWARE_SRC_ARDUINO_H_
