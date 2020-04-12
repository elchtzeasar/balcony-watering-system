#include "Arduino.h"

#include "Master.h"

#include <cassert>
#include <sstream>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

namespace balcony_watering_system {
namespace hardware {

using std::string;

enum Commands {
  READ_COMMAND = 0xea,
  SHUTDOWN_COMMAND = 0xf,
};

static const int NR_OF_INPUTS = 6;

Arduino::Arduino(int address, int shutdownEnabledPin, const string& namePrefix, Master& master) :
  address(address),
  master(master),
  shutdownEnabled(shutdownEnabledPin),
  analogInputs(),
  logger("hardware.arduino", namePrefix) {
  LOG_TRACE(logger, "Arduino creating");
  master.registerReadNode(*this);

  shutdownEnabled.setup();

  for (int i = 0; i < NR_OF_INPUTS; i++) {
    std::ostringstream stream;
    stream << namePrefix << "." << i;
    analogInputs.push_back(AnalogInput(stream.str(), 0, 5));
  }
  LOG_TRACE(logger, "Arduino created");
}

Arduino::~Arduino() {
}

void Arduino::doSample() {
  LOG_TRACE(logger, "doSample");

  master.setNodeAddress(address);
  master.writeByte(uint8_t{READ_COMMAND});

  constexpr size_t expectedDataSize = 2 * NR_OF_INPUTS;
  master.setNodeAddress(address);
  uint8_t data[expectedDataSize];
  size_t actualDataSize = 0;
  do {
    actualDataSize = master.readData(data, expectedDataSize);
    LOG_TRACE(logger, "received " << actualDataSize << " bytes, expected " << expectedDataSize);

    if (actualDataSize != expectedDataSize) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  } while (actualDataSize != expectedDataSize);

  for (int i = 0; i < NR_OF_INPUTS; i++) {
    const uint16_t msb = data[2*i + 0];
    const uint16_t lsb = data[2*i + 1];
    const uint16_t voltageWord = ((msb << 8) & 0xff00) | (lsb & 0x00ff);
    const uint16_t WORD_MAX = 1024;
    const int VOLTAGE_MAX = 5.0;
    const float voltage = voltageWord <= WORD_MAX
        ? voltageWord / float(WORD_MAX) * VOLTAGE_MAX
        : VOLTAGE_MAX;

    analogInputs.at(i).setCurrentVoltage(voltage);

    LOG_TRACE(logger, "doSample[" << i << "] "
        << std::hex
        << "msb=0x" << msb
        << ", lsb=0x" << lsb
        << " => voltageWord=0x" << voltageWord
        << std::dec
        << " => voltage=" << voltage);
  }
}

bool Arduino::isShutdownEnabled() const {
  return shutdownEnabled.getValue();
}

void Arduino::shutdown() {
  LOG_TRACE(logger, "shutdown");

  master.setNodeAddress(address);
  master.writeByte(uint8_t{SHUTDOWN_COMMAND});
}

const std::vector<AnalogInput>& Arduino::getAnalogInputs() const {
  return analogInputs;
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
