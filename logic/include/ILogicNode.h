#ifndef LOGIC_INCLUDE_ILOGICNODE_H_
#define LOGIC_INCLUDE_ILOGICNODE_H_

namespace balcony_watering_system::logic {

class ILogicNode {
public:
  virtual ~ILogicNode() = default;

  virtual void control() = 0;
};

}



#endif /* LOGIC_INCLUDE_ILOGICNODE_H_ */
