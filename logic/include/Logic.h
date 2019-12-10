#ifndef LOGIC_INCLUDE_LOGIC_H_
#define LOGIC_INCLUDE_LOGIC_H_

#include <vector>

namespace balcony_watering_system {
namespace logic {

class ILogicNode;

class Logic {
public:
  Logic();
  virtual ~Logic() = default;

  void control();
  void registerNode(ILogicNode& node);

private:
  std::vector<ILogicNode*> nodes;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_INCLUDE_LOGIC_H_ */
