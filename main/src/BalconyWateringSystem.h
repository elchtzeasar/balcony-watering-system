#ifndef MAIN_SRC_BALCONYWATERINGSYSTEM_H_
#define MAIN_SRC_BALCONYWATERINGSYSTEM_H_

namespace balcony_watering_system::hardware {
class Master;
}

namespace balcony_watering_system::logic {
class Logic;
}

namespace balcony_watering_system::ui {
class TextGui;
}

namespace balcony_watering_system {
namespace main {

class BalconyWateringSystem {
public:
  BalconyWateringSystem(logic::Logic& logic, hardware::Master& master, ui::TextGui& gui);
  virtual ~BalconyWateringSystem();

  BalconyWateringSystem& operator=(BalconyWateringSystem&) = delete;
  BalconyWateringSystem& operator=(BalconyWateringSystem&&) = delete;

  void run();

private:
  hardware::Master& master;
  logic::Logic& logic;
  ui::TextGui& gui;
};

} /* namespace main */
} /* namespace balcony_watering_system */

#endif /* MAIN_SRC_BALCONYWATERINGSYSTEM_H_ */
