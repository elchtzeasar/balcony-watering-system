#include "ADS1015.h"

#include "Master.h"

#include <cassert>
#include <sstream>
#include <unistd.h>

#include <iostream>

namespace balcony_watering_system {
namespace hardware {

using std::string;

enum RegisterAddrss {
  CONVERSION_REGISTER = 0x0,
  CONFIG_REGISTER = 0x1,
  LOW_THRESH_REGISTER = 0x2,
  HIGH_THRESH_REGISTER = 0x3,
};
enum OperationStatusRegister {
  START_SINGLE_CONVERSION = 0x1 << 15,
};
enum InputMultiplexRegister {
  INPUT0_VS_INPUT1 = 0x0 << 12,
  INPUT0_VS_INPUT3 = 0x1 << 12,
  INPUT1_VS_INPUT3 = 0x2 << 12,
  INPUT2_VS_INPUT3 = 0x3 << 12,
  INPUT0_VS_GROUND = 0x4 << 12,
  INPUT1_VS_GROUND = 0x5 << 12,
  INPUT2_VS_GROUND = 0x6 << 12,
  INPUT3_VS_GROUND = 0x7 << 12,
};
enum AmplifierRegister {
  AMPLIFIER_6_144V = 0x0 << 9,
  AMPLIFIER_4_096V = 0x1 << 9,
  AMPLIFIER_2_048V = 0x2 << 9,
  AMPLIFIER_1_024V = 0x3 << 9,
  AMPLIFIER_0_512V = 0x4 << 9,
  AMPLIFIER_0_256V = 0x5 << 9,
};
enum ModeRegister {
  CONTINUOUS_CONVERSION_MODE = 0x0 << 8,
  SINGLE_SHOT_CONVERSION_MODE = 0x1 << 8,
};
enum DataRateRegister {
  DATA_RATE_128SPS = 0x0 << 5,
  DATA_RATE_250SPS = 0x1 << 5,
  DATA_RATE_490SPS = 0x2 << 5,
  DATA_RATE_920SPS = 0x3 << 5,
  DATA_RATE_1600SPS = 0x4 << 5,
  DATA_RATE_2400SPS = 0x5 << 5,
  DATA_RATE_3300SPS = 0x6 << 5,
};
enum ComparatorModeRegister {
  TRADITIONAL_COMPARATOR = 0x0 << 4,
  WINDOW_COMPARATOR = 0x1 << 4,
};
enum ComparatorPolarityRegister {
  COMPARATOR_POLARITY_ACTIVE_LOW = 0x0 << 3,
  COMPARATOR_POLARITY_ACTIVE_HIGH = 0x1 << 3,
};
enum ComparatorLatchRegister {
  NON_LATCHING_COMPARATOR = 0x0 << 2,
  LATCHING_COMPARATOR = 0x1 << 2,
};
enum ComparatorQueRegister {
  COMPARATOR_DISABLE = 0x3 << 0,
  COMPARATOR_ASSERT_AFTER_4_CONVERSIONS = 0x2 << 0,
  COMPARATOR_ASSERT_AFTER_2_CONVERSIONS = 0x1 << 0,
  COMPARATOR_ASSERT_AFTER_1_CONVERSIONS = 0x0 << 0,
};

const uint16_t DEFAULT_COMMAND =
    START_SINGLE_CONVERSION | AMPLIFIER_6_144V | SINGLE_SHOT_CONVERSION_MODE | DATA_RATE_3300SPS;

ADS1015::ADS1015(const string& namePrefix, Master& master) :
  master(master),
  analogInputs() {
  master.registerReadNode(*this);

  for (int i = 0; i < 4; i++) {
    std::ostringstream stream;
    stream << namePrefix << "." << i;
    analogInputs.push_back(AnalogInput(stream.str(), -6.144, 6.144));
  }
}

ADS1015::~ADS1015() {
}

void ADS1015::doSample() {
  for (int i = 0; i < 4; i++) {
    master.setNodeAddress(0x48);

    uint16_t input;
    switch (i) {
    case 0: input = INPUT0_VS_GROUND; break;
    case 1: input = INPUT1_VS_GROUND; break;
    case 2: input = INPUT2_VS_GROUND; break;
    case 3: input = INPUT3_VS_GROUND; break;
    default: assert(false && "bad index");
    }
    const uint16_t command = DEFAULT_COMMAND | input;

    const uint8_t commandMsb = static_cast<uint8_t>((command >> 8) & 0xff);
    const uint8_t commandLsb = static_cast<uint8_t>((command >> 0) & 0xff);
    const uint8_t writeData[3] = { CONFIG_REGISTER, commandMsb, commandLsb };
    master.writeData(writeData, 3);

    bool dataReady;
    do {
      constexpr size_t expectedResponseSize = 2;
      master.setNodeAddress(0x48);
      uint8_t status[expectedResponseSize];
      const size_t actualResponseSize = master.readData(status, 2);
      assert(actualResponseSize == expectedResponseSize);
      dataReady = (status[0] & 0x80) == 0x80;
      usleep(100);
    } while (!dataReady);

    master.setNodeAddress(0x48);
    master.writeData(uint8_t{CONVERSION_REGISTER});
    usleep(10000);

    constexpr size_t expectedDataSize = 2;
    uint8_t data[expectedDataSize] = {0};

    master.setNodeAddress(0x48);
    const size_t actualDataSize = master.readData(data, expectedDataSize);
    assert(actualDataSize == expectedDataSize);


    const int16_t msb = data[0];
    const int16_t lsb = data[1];
    const int16_t voltageWord = ((msb << 8) & 0xff00) | (lsb & 0x00ff);
    const int VDD = 6.144;
    const float voltage = voltageWord / float(0x7ff0) * VDD;

    analogInputs.at(i).setCurrentVoltage(voltage);
  }
}

const std::vector<AnalogInput>& ADS1015::getAnalogInputs() const {
  return analogInputs;
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
