#include "Logic.h"

#include "ILogicNode.h"

namespace balcony_watering_system {
namespace logic {

Logic::Logic() : nodes() {
}

void Logic::control() {
  for (auto* node : nodes) {
    node->control();
  }
}

void Logic::registerNode(ILogicNode& node) {
  nodes.push_back(&node);
}

} /* namespace logic */
} /* namespace balcony_watering_system */
