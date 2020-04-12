#ifndef HARDWARE_SRC_ARDUINO_H_
#define HARDWARE_SRC_ARDUINO_H_

#include "IReadNode.h"
#include "IArduino.h"

#include "AnalogInput.h"
#include "InputPin.h"
#include "Logger.h"

#include <vector>

namespace balcony_watering_system {
namespace hardware {

class Master;

class Arduino : public IArduino, public IReadNode {
 public:
  Arduino(int address, int shutdownEnabledPin, const std::string& namePrefix, Master& master);
  virtual ~Arduino();

  virtual void doSample() override;
  virtual bool isShutdownEnabled() const override;
  virtual void shutdown() override;

  virtual const std::vector<AnalogInput>& getAnalogInputs() const;

 private:
  const int address;
  Master& master;

  InputPin shutdownEnabled;
  std::vector<AnalogInput> analogInputs;

  const platform::Logger logger;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif// HARDWARE_SRC_ARDUINO_H_
