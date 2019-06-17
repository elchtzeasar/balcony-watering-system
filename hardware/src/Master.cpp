#include "Master.h"

#include "IReadNode.h"
#include "IWriteNode.h"

namespace balcony_watering_system {
namespace hardware {

Master::Master() {
}

Master::~Master() {
}

void Master::registerReadNode(IReadNode& node) {
  readNodes.push_back(&node);
}

void Master::registerWriteNode(IWriteNode& node) {
  writeNodes.push_back(&node);
}

void Master::doSampleNodes() {
  for (auto node : readNodes) {
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
