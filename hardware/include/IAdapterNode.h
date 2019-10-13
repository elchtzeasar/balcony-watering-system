#ifndef IADAPTERNODE_H_
#define IADAPTERNODE_H_

namespace balcony_watering_system {
namespace hardware {

class IAdapterNode {
public:
  virtual ~IAdapterNode() = default;

  virtual void doSample() = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif // IADAPTERNODE_H_
