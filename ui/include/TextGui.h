#ifndef UI_SRC_TEXTGUI_H_
#define UI_SRC_TEXTGUI_H_

#include <menu.h>
#include <ncurses.h>
#include <vector>

namespace balcony_watering_system::logic {
  class LogicFactory;
  class Pump;
  class SoilMoistureSensor;
}

namespace balcony_watering_system {
namespace ui {

class TextGui {
public:
  TextGui(logic::LogicFactory& logicFactory);
  virtual ~TextGui();

  bool exec();

private:
  int updatePumpMessages(int nextRow);
  int updateSoilMessages(int nextRow);

  void doStartPumps();
  void doStopPumps();

  std::vector<logic::Pump*> pumps;
  std::vector<logic::SoilMoistureSensor*> soilSensors;

  WINDOW* dataWindow;
  WINDOW* menuWindow;
  MENU* menu;
  ITEM** menuItems;
};

} /* namespace ui */
} /* namespace balcony_watering_system */

#endif /* UI_SRC_TEXTGUI_H_ */
