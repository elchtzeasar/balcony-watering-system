#ifndef IARDUINO_H_
#define IARDUINO_H_

namespace balcony_watering_system {
namespace hardware {

class IArduino {
public:
  virtual ~IArduino() = default;

  virtual bool isShutdownEnabled() const = 0;
  virtual void shutdown() = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif // IARDUINO_H_
