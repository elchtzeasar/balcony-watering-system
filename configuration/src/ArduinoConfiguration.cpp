#include "ArduinoConfiguration.h"

#include "LexicalCast.h"

#include <cassert>

namespace balcony_watering_system {
namespace configuration {

using ::std::string;
using ::balcony_watering_system::platform::lexical_cast;

static const int NO_ADDRESS = -1;
static const int NO_PIN = -1;

ArduinoConfiguration::ArduinoConfiguration() :
    logger("hardware.arduino.configuration"),
    address(NO_ADDRESS),
    shutdownEnabledPin(NO_PIN),
    namePrefix("") {
}

ArduinoConfiguration::~ArduinoConfiguration() {
}

void ArduinoConfiguration::setField(
    const string& fieldName, const string& value) {
  if (fieldName == "name-prefix") {
    namePrefix = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => namePrefix=" << namePrefix);
  }
  else if (fieldName == "address") {
    address = lexical_cast<int>(value);
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => address=" << address);
  }
  else if (fieldName == "shutdownEnabledPin") {
    shutdownEnabledPin = lexical_cast<int>(value);
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => shutdownEnabledPin=" << shutdownEnabledPin);
  }
  else {
    assert(false && "unknown field");
  }
}

int ArduinoConfiguration::getAddress() const {
  assert(address != NO_ADDRESS && "address must be set");
  return address;
}

int ArduinoConfiguration::getShutdownEnabledPin() const {
  assert(shutdownEnabledPin > NO_PIN && "shutdownEnabledPin must be set");
  return shutdownEnabledPin;
}

const string& ArduinoConfiguration::getNamePrefix() const {
  assert(namePrefix != "" && "namePrefix must be set");
  return namePrefix;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
