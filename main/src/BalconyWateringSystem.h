#ifndef MAIN_SRC_BALCONYWATERINGSYSTEM_H_
#define MAIN_SRC_BALCONYWATERINGSYSTEM_H_

namespace balcony_watering_system {
namespace ui {
class TextGui;
}
}

namespace balcony_watering_system {
namespace main {

class BalconyWateringSystem {
public:
  BalconyWateringSystem(ui::TextGui& gui);
  virtual ~BalconyWateringSystem();

  void run();

private:
  ui::TextGui& gui;
};

} /* namespace main */
} /* namespace balcony_watering_system */

#endif /* MAIN_SRC_BALCONYWATERINGSYSTEM_H_ */
