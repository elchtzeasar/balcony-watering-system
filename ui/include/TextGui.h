#ifndef UI_SRC_TEXTGUI_H_
#define UI_SRC_TEXTGUI_H_

#include "Logger.h"

#include <menu.h>
#include <ncurses.h>
#include <string>
#include <vector>

namespace balcony_watering_system::logic {
  class LogicFactory;
  class Pump;
  class HumidityMeasurement;
  class SoilMoistureMeasurement;
  class TemperatureMeasurement;
  class VolumeMeasurement;
}

namespace balcony_watering_system::hardware {
  class HWFactory;
  class IMotorController;
  class IDistanceSensor;
  class IHumiditySensor;
  class ISoilMoistureSensor;
  class ITemperatureSensor;
  class IAnalogInput;
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
  int updateSoilMeasurementMessages(int nextRow);
  int updateSoilSensorMessages(int nextRow);
  int updateHumidityMeasurementMessages(int nextRow);
  int updateHumiditySensorMessages(int nextRow);
  int updateTemperatureMeasurementMessages(int nextRow);
  int updateTemperatureSensorMessages(int nextRow);
  int updateVolumeMeasurementMessages(int nextRow);
  int updateDistanceSensorMessages(int nextRow);
  int updateAnalogInputMessages(int nextRow);

  void displayData(int row,
                   const std::string& header,
                   const std::string& name,
                   const std::string& message);
  void displayProgressBar(int row,
                          const std::string& header,
                          const std::string& name,
                          int progressInPercent);
  void displayProgressBar(int row,
                          const std::string& header,
                          const std::string& name,
                          float progressInPercent);
  void displayProgressBar(int row,
                          const std::string& header,
                          const std::string& name,
                          int min,
                          int max,
                          int value,
                          const std::string& unit);
  void displayProgressBar(int row,
                          const std::string& header,
                          const std::string& name,
                          float min,
                          float max,
                          float value,
                          const std::string& unit);

  void doStartPumps();
  void doStopPumps();
  void doIncreasePumps();
  void doDecreasePumps();

  const std::vector<logic::Pump*> pumps;
  const std::vector<hardware::IMotorController*> motors;

  const std::vector<logic::HumidityMeasurement*> humidityMeasurements;
  const std::vector<hardware::IHumiditySensor*> humiditySensors;
  const std::vector<logic::SoilMoistureMeasurement*> soilMeasurements;
  const std::vector<hardware::ISoilMoistureSensor*> soilSensors;
  const std::vector<logic::TemperatureMeasurement*> temperatureMeasurements;
  const std::vector<hardware::ITemperatureSensor*> temperatureSensors;
  const std::vector<logic::VolumeMeasurement*> volumeMeasurements;
  const std::vector<hardware::IDistanceSensor*> distanceSensors;
  const std::vector<hardware::IAnalogInput const*> analogInputs;

  WINDOW* dataWindow;
  WINDOW* menuWindow;
  MENU* menu;
  ITEM** menuItems;

  int nameEndColumn;
  const platform::Logger logger;
};

} /* namespace ui */
} /* namespace balcony_watering_system */

#endif /* UI_SRC_TEXTGUI_H_ */
