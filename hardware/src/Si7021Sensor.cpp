#include "Si7021Sensor.h"

#include "Master.h"

#include <cerrno>
#include <cmath>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

namespace balcony_watering_system {
namespace hardware {

using ::std::cerr;
using ::std::endl;
using ::std::strerror;
using ::std::string;

Si7021Sensor::Si7021Sensor(const string& name, Master& master) :
  name(name),
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
  // Create I2C bus
  const char* bus = "/dev/i2c-1";
  const int file = open(bus, O_RDWR);
  if (file < 0) {
    cerr << "Failed to open the bus: " << strerror(errno) << endl;
    exit(1);
  }
  // Get I2C device, SI7021 I2C address is 0x40(64)
  ioctl(file, I2C_SLAVE, 0x40);

  // Send humidity measurement command(0xF5)
  char command = 0xF5;
  write(file, &command, sizeof(command));
  sleep(1);

  // Read 2 bytes of humidity data
  // humidity msb, humidity lsb
  constexpr size_t data_size = 2;
  char data[data_size] = {0};
  if (read(file, data, data_size) != data_size) {
    cerr << "Error : Input/output Error" << std::endl;
  }
  else {
    const uint16_t msb = data[0];
    const uint16_t lsb = data[1];
    const uint16_t data = msb << 8 | lsb;
    const float humidity = data * 125 / 65536.0 - 6;

    humidityInPercent = round(humidity);
  }

  // Send temperature measurement command(0xF3)
  command = 0xF3;
  write(file, &command, sizeof(command));
  sleep(1);

  // Read 2 bytes of temperature data
  // temp msb, temp lsb
  if(read(file, data, data_size) != data_size) {
    cerr << "Error : Input/output Error" << endl;
  }
  else {
    const uint16_t msb = data[0];
    const uint16_t lsb = data[1];
    const uint16_t data = msb << 8 | lsb;
    float temperature = (data * 175.72) / 65536.0 - 46.85;

    // Output data to screen
    //cout << ", temperature=" << temperature << " C" << endl;
    temperatureInDegrees = temperature;
  }
}

int Si7021Sensor::getMin() const {
  return 0;
}

int Si7021Sensor::getMax() const {
  return 100;
}

int Si7021Sensor::getTemperatureInDegrees() const {
  return temperatureInDegrees;
}

int Si7021Sensor::getHumidityInPercent() const {
  return humidityInPercent;
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
