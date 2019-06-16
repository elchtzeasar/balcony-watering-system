#ifndef UI_SRC_TEXTGUI_H_
#define UI_SRC_TEXTGUI_H_

#include <ncurses.h>

namespace balcony_watering_system::logic {
  class Pump;
  class SoilMoistureSensor;
}

namespace balcony_watering_system {
namespace ui {

class TextGui {
public:
  TextGui(logic::Pump& pump, logic::SoilMoistureSensor& soilSensor);
  virtual ~TextGui();

  void run();

private:
  bool updatePumpMessage(bool force = false);
  bool updateSoilMessage(bool force = false);

  void doStartPump();
  void doStopPump();

  int oldSoilMoistureLevel;
  bool oldIsPumping;

  logic::Pump& pump;
  logic::SoilMoistureSensor& soilSensor;

  WINDOW* dataWindow;
};

} /* namespace ui */
} /* namespace balcony_watering_system */

#endif /* UI_SRC_TEXTGUI_H_ */
