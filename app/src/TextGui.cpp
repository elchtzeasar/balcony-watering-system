#include "TextGui.h"

#include "IAnalogInput.h"
#include "IMotorController.h"
#include "IDistanceSensor.h"
#include "IHumiditySensor.h"
#include "ISoilMoistureSensor.h"
#include "ITemperatureSensor.h"
#include "LogicFactory.h"
#include "HWFactory.h"
#include "Pump.h"
#include "HumidityMeasurement.h"
#include "SoilMoistureMeasurement.h"
#include "TemperatureMeasurement.h"
#include "VolumeMeasurement.h"
#include "WateringLogic.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

namespace balcony_watering_system {
namespace app {

using ::balcony_watering_system::logic::LogicFactory;
using ::balcony_watering_system::logic::WateringLogic;
using ::balcony_watering_system::hardware::HWFactory;
using ::std::ios;
using ::std::max;
using ::std::ostringstream;
using ::std::round;
using ::std::string;
using ::std::vector;

static const int KEY_ENTER_ = 10;

static const std::string START_PUMPS_CMD = "start pumps";
static const std::string STOP_PUMPS_CMD = "stop pumps";
static const std::string EXIT_CMD = "exit";
static const vector<string> menuOptions = {START_PUMPS_CMD, STOP_PUMPS_CMD, EXIT_CMD};

static const int DATA_COLUMN = 3;
static const int FIRST_DATA_ROW = 2;

TextGui::TextGui(const LogicFactory& logicFactory, const HWFactory& hwFactory) :
    wateringLogic(logicFactory.getWateringLogic()),
    pumps(logicFactory.getPumps()),
    motors(hwFactory.getMotors()),
    humidityMeasurements(logicFactory.getHumidityMeasurements()),
    humiditySensors(hwFactory.getHumiditySensors()),
    soilMeasurements(logicFactory.getSoilMoistureMeasurements()),
    soilSensors(hwFactory.getSoilMoistureSensors()),
    temperatureMeasurements(logicFactory.getTemperatureMeasurements()),
    temperatureSensors(hwFactory.getTemperatureSensors()),
    volumeMeasurements(logicFactory.getVolumeMeasurements()),
    distanceSensors(hwFactory.getDistanceSensors()),
    analogInputs(hwFactory.getAnalogInputs()),
    dataWindow(NULL),
    menuWindow(NULL),
    menu(NULL),
    menuItems(NULL),
    nameEndColumn(0),
    logger("text.gui") {
  initscr();
  noecho();

  dataWindow = newwin(LINES-6, COLS-2, 3, 1);
  box(dataWindow, 0, 0);

  menuWindow = newwin(3, COLS-2, LINES-3, 1);
  box(menuWindow, 0, 0);
  keypad(menuWindow, true);

  nodelay(menuWindow, true);

  menuItems = (ITEM**) calloc(menuOptions.size() + 1, sizeof(ITEM*));
  for (int i = 0; i < menuOptions.size(); ++i) {
    const auto& option = menuOptions.at(i);
    menuItems[i] = new_item(option.c_str(), option.c_str());
  }
  menu = new_menu(menuItems);
  menu_opts_off(menu, O_SHOWDESC);
  set_menu_win(menu, menuWindow);
  set_menu_sub(menu, derwin(menuWindow, 1, COLS-4, 1, 2));
  set_menu_format(menu, 1, 3);

  auto nextDataRow = updateWateringLogicMessages(FIRST_DATA_ROW);
  nextDataRow = updatePumpMessages(nextDataRow);
  nextDataRow = updateMotorMessages(nextDataRow);
  nextDataRow = updateHumidityMeasurementMessages(nextDataRow);
  nextDataRow = updateHumiditySensorMessages(nextDataRow);
  nextDataRow = updateSoilMeasurementMessages(nextDataRow);
  nextDataRow = updateSoilSensorMessages(nextDataRow);
  nextDataRow = updateTemperatureMeasurementMessages(nextDataRow);
  nextDataRow = updateTemperatureSensorMessages(nextDataRow);
  nextDataRow = updateVolumeMeasurementMessages(nextDataRow);
  nextDataRow = updateDistanceSensorMessages(nextDataRow);

  refresh();
  post_menu(menu);
  wrefresh(dataWindow);
  wrefresh(menuWindow);
}

TextGui::~TextGui() {
  free(menuItems);
  unpost_menu(menu);
  for (int i = 0; i < menuOptions.size(); ++i) {
    free_item(menuItems[i]);
  }
  free_menu(menu);
  endwin();
}

bool TextGui::exec() {
  int c = wgetch(menuWindow);

  switch (c) {
  case KEY_LEFT:
    menu_driver(menu, REQ_LEFT_ITEM);
    wrefresh(menuWindow);
    break;
  case KEY_RIGHT:
    menu_driver(menu, REQ_RIGHT_ITEM);
    wrefresh(menuWindow);
    break;
  case ' ':
  case KEY_ENTER_: {
    ITEM* currentItem = current_item(menu);
    const string currentName = item_name(currentItem);

    if (currentName == START_PUMPS_CMD) {
      doStartPumps();
    }
    else if (currentName == STOP_PUMPS_CMD) {
      doStopPumps();;
    }
    else if (currentName == EXIT_CMD) {
      return false;
    }
  } break;
  case '+':
  case KEY_UP:
    doIncreasePumps();
    break;
  case '-':
  case KEY_DOWN:
    doDecreasePumps();
    break;
  case 'q':
    return false;
    break;
  }

  auto nextDataRow = updateWateringLogicMessages(FIRST_DATA_ROW);
  nextDataRow = updatePumpMessages(nextDataRow);
  nextDataRow = updateMotorMessages(nextDataRow);
  nextDataRow = updateHumidityMeasurementMessages(nextDataRow);
  nextDataRow = updateHumiditySensorMessages(nextDataRow);
  nextDataRow = updateSoilMeasurementMessages(nextDataRow);
  nextDataRow = updateSoilSensorMessages(nextDataRow);
  nextDataRow = updateTemperatureMeasurementMessages(nextDataRow);
  nextDataRow = updateTemperatureSensorMessages(nextDataRow);
  nextDataRow = updateVolumeMeasurementMessages(nextDataRow);
  nextDataRow = updateDistanceSensorMessages(nextDataRow);
  nextDataRow = updateAnalogInputMessages(nextDataRow);

  wrefresh(dataWindow);

  return true;
}

void TextGui::doStartPumps() {
  for (auto pump : pumps) {
    pump->start();
  }
}

void TextGui::doStopPumps() {
  for (auto pump : pumps) {
    pump->stop();
  }
}

void TextGui::doIncreasePumps() {
  for (auto pump : pumps) {
    pump->increase();
  }
}

void TextGui::doDecreasePumps() {
  for (auto pump : pumps) {
    pump->decrease();
  }
}

int TextGui::updateWateringLogicMessages(int nextRow) {
  const auto state = wateringLogic.getState();

  string message = "unknown";
  switch (state) {
  case WateringLogic::State::IDLE: message = "idle"; break;
  case WateringLogic::State::WATERING: message = "watering"; break;
  case WateringLogic::State::NOT_WATERING: message = "not watering"; break;
  }

  displayMessage(nextRow, "Watering Logic", message);
  nextRow++;
  return nextRow;
}

int TextGui::updatePumpMessages(int nextRow) {
  for (auto pump : pumps) {
    const bool isPumping = pump->isPumping();
    const string message = isPumping ? "pumping" : "not pumping";

    displayMessage(nextRow, "Pump", pump->getName(), message);
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateMotorMessages(int nextRow) {
  for (auto motor : motors) {
    displayProgressBar(nextRow,
                       "  Motor",
                       motor->getName(),
                       motor->getCurrentSpeedInPercentage());
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateHumidityMeasurementMessages(int nextRow) {
  for (auto measurement : humidityMeasurements) {
    displayProgressBar(nextRow,
                       "HumidityMeasurement",
                       measurement->getName(),
                       measurement->getHumidityInPercent());
    nextRow++;

    const string message = measurement->readyToWater() ? "ready" : "not ready";
    displayMessage(nextRow, "", message);
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateHumiditySensorMessages(int nextRow) {
  for (auto sensor : humiditySensors) {
    displayProgressBar(nextRow,
                       "  HumiditySensor",
                       sensor->getName(),
                       sensor->getHumidityInPercent());
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateSoilMeasurementMessages(int nextRow) {
  for (auto measurement : soilMeasurements) {
    displayProgressBar(nextRow,
                       "MoistureMeasurement",
                       measurement->getName(),
                       measurement->getMoistureInPercent());
    nextRow++;

    const string message = measurement->readyToWater() ? "ready" : "not ready";
    displayMessage(nextRow, "", message);
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateSoilSensorMessages(int nextRow) {
  for (auto sensor : soilSensors) {
    displayProgressBar(nextRow,
                       "  MoistureSensor",
                       sensor->getName(),
                       sensor->getMoistureInPercent());
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateTemperatureMeasurementMessages(int nextRow) {
  for (auto measurement : temperatureMeasurements) {
    displayProgressBar(nextRow,
                       "TemperatureMeasurement",
                       measurement->getName(),
                       measurement->getMin(),
                       measurement->getMax(),
                       measurement->getTemperatureInDegrees(),
                       "C");
    nextRow++;

    const string message = measurement->readyToWater() ? "ready" : "not ready";
    displayMessage(nextRow, "", message);
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateTemperatureSensorMessages(int nextRow) {
  for (auto sensor : temperatureSensors) {
    displayProgressBar(nextRow,
                       "  TemperatureSensor",
                       sensor->getName(),
                       sensor->getMin(),
                       sensor->getMax(),
                       sensor->getTemperatureInDegrees(),
                       "C");
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateVolumeMeasurementMessages(int nextRow) {
  for (auto measurement : volumeMeasurements) {
    displayProgressBar(nextRow,
                       "VolumeMeasurement",
                       measurement->getName(),
                       measurement->getMin(),
                       measurement->getMax(),
                       measurement->getVolumeInLiters(),
                       "l");
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateDistanceSensorMessages(int nextRow) {
  for (auto sensor : distanceSensors) {
    displayProgressBar(nextRow,
                       "  DistanceSensor",
                       sensor->getName(),
                       sensor->getMin(),
                       sensor->getMax(),
                       sensor->getDistanceInMillimeters(),
                       "mm");
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateAnalogInputMessages(int nextRow) {
  for (auto input : analogInputs) {
    displayProgressBar(nextRow,
                       "  AnalogInput",
                       input->getName(),
                       input->getMin(),
                       input->getMax(),
                       input->getCurrentVoltage(),
                       "V");
    nextRow++;
  }
  return nextRow;
}

void TextGui::displayMessage(int row,
                          const std::string& header,
                          const std::string& name,
                          const std::string& message) {
  ostringstream stream;
  stream << header << "[" << name << "]: ";
  displayMessage(row, stream.str(), message);
}

void TextGui::displayMessage(int row,
                             const string& header,
                             const string& message) {
  nameEndColumn = std::max<int>(nameEndColumn, int(header.size()));
  ostringstream stream;
  stream << header;

  const int headerFillSize = max<int>(0, nameEndColumn - header.size());
  const string headerFill(headerFillSize, ' ');
  stream << headerFill;

  const int lineFillSize = max<int>(0, COLS - nameEndColumn - headerFillSize - message.size() - 7);
  const string lineFill(lineFillSize, ' ');
  stream << message << lineFill;

  const string line = stream.str();
  mvwaddstr(dataWindow, row, DATA_COLUMN, line.c_str());

  LOG_DEBUG(logger, "displayMessage - row=" << row
      << ", header=" << header
      << ", message=" << message
      << " => nameFillSize=" << headerFillSize
      << ", lineFillSize=" << lineFillSize
      << " => nameFill='" << headerFill << "'"
      << "', lineFill='" << lineFill << "'"
      << " => line=" << line);
}

void TextGui::displayProgressBar(int row,
                                 const std::string& header,
                                 const std::string& name,
                                 int progressInPercent) {
  displayProgressBar(row, header, name, 0, 100, progressInPercent, "%");
}

void TextGui::displayProgressBar(int row,
                                 const std::string& header,
                                 const std::string& name,
                                 float progressInPercent) {
  displayProgressBar(row, header, name, 0.0f, 100.0f, progressInPercent, "%");
}

void TextGui::displayProgressBar(int row,
                                 const std::string& header,
                                 const std::string& name,
                                 int minValue,
                                 int maxValue,
                                 int value,
                                 const std::string& unit) {
  const int progressInPercent = round(100 * (value - minValue) / float(maxValue - minValue));

  ostringstream stream;
  stream << header << "[" << name << "]: ";

  nameEndColumn = max<int>(nameEndColumn, int(stream.str().size()));
  const int nameFillSize = max<int>(0, nameEndColumn - stream.str().size());
  const string nameFill(nameFillSize, ' ');
  stream << nameFill;

  const int UNIT_AND_VALUE_SIZE = 14 + unit.size();
  const int totalBarWidth = max<int>(0, COLS - nameEndColumn - UNIT_AND_VALUE_SIZE);
  const int filledBarWidth = max<int>(0, progressInPercent / 100.0 * totalBarWidth);
  const int blankBarWidth = max<int>(0, totalBarWidth - filledBarWidth);

  const string barFill = string(filledBarWidth, '=');
  const string blankBarFill = string(blankBarWidth, ' ');
  stream << "[" << barFill << blankBarFill << "] ";
  stream << std::setw(3) << std::setfill(' ') << value << ' ' << unit;

  const string line = stream.str();
  mvwaddstr(dataWindow, row, DATA_COLUMN, line.c_str());

  LOG_DEBUG(logger, "displayData[int] - row=" << row
      << ", header=" << header
      << ", name=" << name
      << ", minValue=" << minValue
      << ", maxValue=" << maxValue
      << ", value=" << value
      << " => progressInPercent=" << progressInPercent
      << " => totalBarWidth=" << totalBarWidth
      << ", filledBarWidth=" << filledBarWidth
      << ", blankBarWidth=" << blankBarWidth
      << " => nameFill='" << nameFill << "'"
      << "', barFill='" << barFill << "'"
      << "', blankBarFill='" << blankBarFill << "'"
      << " => line=" << line);
}

void TextGui::displayProgressBar(int row,
                                 const std::string& header,
                                 const std::string& name,
                                 float minValue,
                                 float maxValue,
                                 float value,
                                 const std::string& unit) {
  const float progressInPercent = 100 * (value - minValue) / float(maxValue - minValue);

  ostringstream stream;
  stream << header << "[" << name << "]: ";

  nameEndColumn = max<int>(nameEndColumn, int(stream.str().size()));
  const int nameFillSize = max<int>(0, nameEndColumn - stream.str().size());
  const string nameFill(nameFillSize, ' ');
  stream << nameFill;

  const int UNIT_AND_VALUE_SIZE = 17 + unit.size();
  const int totalBarWidth = max<int>(0, COLS - nameEndColumn - UNIT_AND_VALUE_SIZE);
  const int filledBarWidth = max<int>(0, round(progressInPercent / 100.0 * totalBarWidth));
  const int blankBarWidth = max<int>(0, totalBarWidth - filledBarWidth);
  const string barFill(filledBarWidth, '=');
  const string blankBarFill(blankBarWidth, ' ');
  stream << "[" << barFill << blankBarFill << "] ";

  stream.setf(ios::fixed, ios::floatfield );
  stream.precision(4);
  stream << std::setw(2) << std::setfill('0') << value << ' ' << unit;

  const string line = stream.str();
  mvwaddstr(dataWindow, row, DATA_COLUMN, line.c_str());


  LOG_DEBUG(logger, "displayData[float] - row=" << row
      << ", header=" << header
      << ", name=" << name
      << ", minValue=" << minValue
      << ", maxValue=" << maxValue
      << ", value=" << value
      << " => progressInPercent=" << progressInPercent
      << " => totalBarWidth=" << totalBarWidth
      << ", filledBarWidth=" << filledBarWidth
      << ", blankBarWidth=" << blankBarWidth
      << " => nameFill='" << nameFill << "'"
      << "', barFill='" << barFill << "'"
      << "', blankBarFill='" << blankBarFill << "'"
      << " => line=" << line);
}

} /* namespace ui */
} /* namespace balcony_watering_system */
