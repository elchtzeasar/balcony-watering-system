#include "Master.h"

#include "IAdapterNode.h"
#include "IReadNode.h"
#include "IWriteNode.h"

#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

namespace balcony_watering_system {
namespace hardware {

using ::std::cerr;
using ::std::endl;

int openDevice();

Master::Master() : readNodes(), writeNodes(), adapterNodes(), fd(openDevice()) {
}

Master::~Master() {
  close(fd);
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

int openDevice() {
  const char* device = "/dev/i2c-1";
  const int fd = open(device, O_RDWR);
  if (fd < 0) {
    cerr << "Failed to open the bus: " << strerror(errno) << endl;
    exit(1);
  }

  return fd;
}

void Master::setNodeAddress(uint8_t address) {
  ioctl(fd, I2C_SLAVE, address);
}

void Master::writeByte(const uint8_t data) {
  write(fd, &data, sizeof(data));
}

void Master::writeData(uint8_t const* data, size_t size) {
  write(fd, data, size);
}

int Master::readData(uint8_t *data, size_t size) {
  return read(fd, data, size);
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


} /* namespace hardware */
} /* namespace balcony_watering_system */
