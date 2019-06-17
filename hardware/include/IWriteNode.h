#ifndef IWRITENODE_H_
#define IWRITENODE_H_

namespace balcony_watering_system {
namespace hardware {

class IWriteNode {
public:
  virtual ~IWriteNode() = default;

  virtual void doControl() const = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif // IWRITENODE_H_
