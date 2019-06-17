#ifndef IREADNODE_H_
#define IREADNODE_H_

namespace balcony_watering_system {
namespace hardware {

class IReadNode {
public:
  virtual ~IReadNode() = default;

  virtual void doSample() = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif // IREADNODE_H_
