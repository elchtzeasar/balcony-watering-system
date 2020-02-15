#include "Master.h"

#include "IAdapterNode.h"
#include "IReadNode.h"
#include "IWriteNode.h"

#include <cassert>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <linux/i2c-dev.h>
#include <pigpio.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

namespace balcony_watering_system {
namespace hardware {

using ::balcony_watering_system::platform::Logger;

int openDevice(const Logger& logger);

Master::Master() : logger("master"), readNodes(), writeNodes(), adapterNodes(), fd(openDevice(logger)) {
}

Master::~Master() {
  close(fd);
  gpioTerminate();
}

void Master::registerReadNode(IReadNode& node) {
  readNodes.push_back(&node);
}

void Master::registerWriteNode(IWriteNode& node) {
  writeNodes.push_back(&node);
}

void Master::registerAdapterNode(IAdapterNode& node) {
  adapterNodes.push_back(&node);
}

int openDevice(const Logger& logger) {
  const char* device = "/dev/i2c-1";
  const int fd = open(device, O_RDWR);
  if (fd < 0) {
    LOG_FATAL(logger, "Failed to open the bus: " << strerror(errno));
    exit(1);
  }

  assert(gpioInitialise() >= 0 && "could not initialize");

  return fd;
}

void Master::setNodeAddress(uint8_t address) {
  const auto result = ioctl(fd, I2C_SLAVE, address);
  if (result == -1) {
    LOG_ERROR(logger, "failed to set node address for address=" << address
              << ": " << strerror(errno));
    assert(false && "see log file");
  }
}

void Master::writeByte(const uint8_t data) {
  const auto nrOfBytesWritten = write(fd, &data, sizeof(data));
  if (nrOfBytesWritten != sizeof(data)) {
    LOG_WARN(logger, nrOfBytesWritten << " bytes written, expected " << sizeof(data)
             << ": " << strerror(errno));
  }
}

void Master::writeData(uint8_t const* data, size_t size) {
  const auto nrOfBytesWritten = write(fd, data, size);
  if (nrOfBytesWritten != size) {
    LOG_WARN(logger, nrOfBytesWritten << " bytes written, expected " << size
             << ": " << strerror(errno));
  }
}

int Master::readData(uint8_t* data, size_t size) {
  const auto nrOfBytesRead = read(fd, data, size);
  if (nrOfBytesRead <= 0) {
    LOG_WARN(logger, nrOfBytesRead << " bytes read, expected " << size
             << ": " << strerror(errno));
  }

  for (int i = 0; i < size; i++) {
    if (data[i] == 0xff) {
      LOG_WARN(logger, "packet contained 0xff at i=" << i << " => discarding packet");
      return 0;
    }
  }

  return nrOfBytesRead;
}

void Master::doSampleNodes() {
  for (auto node : readNodes) {
    node->doSample();
  }
  for (auto node : adapterNodes) {
    node->doSample();
  }
}

void Master::doControlNodes() {
  for (auto node : writeNodes) {
    node->doControl();
  }
}

void Master::doShutdownNodes() {
  for (auto node : writeNodes) {
    node->doShutdown();
  }
}

} /* namespace hardware */
} /* namespace balcony_watering_system */
