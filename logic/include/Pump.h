#ifndef LOGIC_SRC_PUMP_H_
#define LOGIC_SRC_PUMP_H_

namespace balcony_watering_system {
namespace logic {

class Pump {
public:
  Pump();
  virtual ~Pump();

  void start();
  void stop();

  bool isPumping() const;

private:
  bool started;
};

} /* namespace logic */
} /* namespace balcony_watering_system */

#endif /* LOGIC_SRC_PUMP_H_ */
