#ifndef HARDWARE_SRC_MASTER_H_
#define HARDWARE_SRC_MASTER_H_

#include <vector>

namespace balcony_watering_system {
namespace hardware {

class IReadNode;
class IWriteNode;

class Master {
public:
  Master();
  virtual ~Master();

  void registerReadNode(IReadNode& node);
  void registerWriteNode(IWriteNode& node);

  void doSampleNodes();
  void doControlNodes();

private:
  std::vector<IReadNode*> readNodes;
  std::vector<IWriteNode*> writeNodes;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_MASTER_H_ */
