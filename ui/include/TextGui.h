#ifndef UI_SRC_TEXTGUI_H_
#define UI_SRC_TEXTGUI_H_

#include <menu.h>
#include <ncurses.h>
#include <string>
#include <vector>

namespace balcony_watering_system::logic {
  class LogicFactory;
  class Pump;
  class SoilMoistureMeasurement;
}

namespace balcony_watering_system::hardware {
  class HWFactory;
  class IMotorController;
  class ISoilMoistureSensor;
}

namespace balcony_watering_system {
namespace ui {

class TextGui {
public:
  TextGui(const logic::LogicFactory& logicFactory,
          const hardware::HWFactory& hwFactory);
  virtual ~TextGui();

  bool exec();

private:
  int updatePumpMessages(int nextRow);
  int updateMotorMessages(int nextRow);
  int updateLogicSoilMessages(int nextRow);
  int updateSensorSoilMessages(int nextRow);

  void displayData(int row,
                   const std::string& header,
                   const std::string& name,
                   const std::string& message);
  void displayProgressBar(int row,
                          const std::string& header,
                          const std::string& name,
                          int progressInPercent);

  void doStartPumps();
  void doStopPumps();

  const std::vector<logic::Pump*> pumps;
  const std::vector<hardware::IMotorController*> motors;

  const std::vector<logic::SoilMoistureMeasurement*> soilMeasurements;
  const std::vector<hardware::ISoilMoistureSensor*> soilSensors;

  WINDOW* dataWindow;
  WINDOW* menuWindow;
  MENU* menu;
  ITEM** menuItems;

  int nameEndColumn;
};

} /* namespace ui */
} /* namespace balcony_watering_system */

#endif /* UI_SRC_TEXTGUI_H_ */
