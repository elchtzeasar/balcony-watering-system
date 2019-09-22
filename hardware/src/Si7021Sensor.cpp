#include "Si7021Sensor.h"

#include "Master.h"

#include <cerrno>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdlib.h>

namespace balcony_watering_system {
namespace hardware {

using ::std::cerr;
using ::std::endl;
using ::std::strerror;
using ::std::string;

enum Commands {
  MEASURE_RELATIVE_HUMIDITY_HOLD_MASTER = 0xE5,
  MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER = 0xF5,
  MEASURE_TEMPERATURE_HOLD_MASTER = 0xE3,
  MEASURE_TEMPERATURE_NO_HOLD_MASTER = 0xF3,
  READ_TEMPERATURE_FROM_PREVIOUS_TEMPERATURE_MEASUREMENT = 0xE0,
  RESET = 0xFE,
  WRITE_USER_REGISTER_1 = 0xE6,
  READ_USER_REGISTER_1 = 0xE7,
  WRITE_HEATER_CONTROL_REGISTER = 0x51,
  READ_HEATER_CONTROL_REGISTER = 0x11,
};

Si7021Sensor::Si7021Sensor(const string& name, Master& master) :
  name(name),
  master(master),
  temperatureInDegrees(0),
  humidityInPercent(0) {
  master.registerReadNode(*this);
}

Si7021Sensor::~Si7021Sensor() {
}

const string& Si7021Sensor::getName() const {
  return name;
}

void Si7021Sensor::doSample() {
  master.setNodeAddress(0x40);

  master.writeData(MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER);

  constexpr size_t expectedDataSize = 2;
  uint8_t data[expectedDataSize] = {0};
  size_t actualDataSize = 0;
  do {
    actualDataSize = master.readData(data, expectedDataSize);
  } while (actualDataSize != expectedDataSize);

  const uint16_t msb = data[0];
  const uint16_t lsb = data[1];
  const uint16_t sensorWord = msb << 8 | lsb;
  const float humidity = sensorWord * 125 / 65536.0 - 6;

  humidityInPercent = humidity;

  master.writeData(READ_TEMPERATURE_FROM_PREVIOUS_TEMPERATURE_MEASUREMENT);

  if (master.readData(data, expectedDataSize) != expectedDataSize) {
    cerr << "Error : Input/output Error" << endl;
  }
  else {
    const uint16_t msb = data[0];
    const uint16_t lsb = data[1];
    const uint16_t sensorWord = msb << 8 | lsb;
    float temperature = (sensorWord * 175.72) / 65536.0 - 46.85;

    temperatureInDegrees = temperature;
  }
}

float Si7021Sensor::getMin() const {
  return 0;
}

float Si7021Sensor::getMax() const {
  return 100;
}

float Si7021Sensor::getTemperatureInDegrees() const {
  return temperatureInDegrees;
}

float Si7021Sensor::getHumidityInPercent() const {
  return humidityInPercent;
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
