#ifndef HARDWARE_SRC_MASTER_H_
#define HARDWARE_SRC_MASTER_H_

#include <vector>
#include <stddef.h>
#include <stdint.h>

namespace balcony_watering_system {
namespace hardware {

class IAdapterNode;
class IReadNode;
class IWriteNode;

class Master {
public:
  Master();
  virtual ~Master();

  void registerReadNode(IReadNode& node);
  void registerWriteNode(IWriteNode& node);
  void registerAdapterNode(IAdapterNode& node);

  void setNodeAddress(uint8_t address);
  void writeByte(const uint8_t data);
  void writeData(uint8_t const* data, size_t size);
  int readData(uint8_t* data, size_t size);

  void doSampleNodes();
  void doControlNodes();

private:
  std::vector<IReadNode*> readNodes;
  std::vector<IWriteNode*> writeNodes;
  std::vector<IAdapterNode*> adapterNodes;

  const int fd;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_MASTER_H_ */
