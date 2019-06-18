#include "TextGui.h"

#include "IMotorController.h"
#include "ISoilMoistureSensor.h"
#include "LogicFactory.h"
#include "HWFactory.h"
#include "Pump.h"
#include "SoilMoistureMeasurement.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

namespace balcony_watering_system {
namespace ui {

using ::balcony_watering_system::logic::LogicFactory;
using ::balcony_watering_system::hardware::HWFactory;
using ::std::ostringstream;
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
    pumps(logicFactory.getPumps()),
    motors(hwFactory.getMotors()),
    soilMeasurements(logicFactory.getSoilMoistureMeasurements()),
    soilSensors(hwFactory.getSoilMoistureSensors()),
    dataWindow(NULL),
    menuWindow(NULL),
    menu(NULL),
    menuItems(NULL),
    nameEndColumn(0) {
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

  auto nextDataRow = updatePumpMessages(FIRST_DATA_ROW);
  nextDataRow = updateMotorMessages(nextDataRow);
  nextDataRow = updateLogicSoilMessages(nextDataRow);
  nextDataRow = updateSensorSoilMessages(nextDataRow);

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
  case 'q':
    return false;
    break;
  }

  auto nextDataRow = updatePumpMessages(FIRST_DATA_ROW);
  nextDataRow = updateMotorMessages(nextDataRow);
  nextDataRow = updateLogicSoilMessages(nextDataRow);
  nextDataRow = updateSensorSoilMessages(nextDataRow);

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

int TextGui::updatePumpMessages(int nextRow) {
  for (auto pump : pumps) {
    const bool isPumping = pump->isPumping();
    const string message = isPumping ? "pumping" : "not pumping";

    displayData(nextRow, "Pump", pump->getName(), message);
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

int TextGui::updateLogicSoilMessages(int nextRow) {
  for (auto measurement : soilMeasurements) {
    displayProgressBar(nextRow,
                       "MoistureMeasurement",
                       measurement->getName(),
                       measurement->getMoistureLevelInPercent());
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateSensorSoilMessages(int nextRow) {
  for (auto sensor : soilSensors) {
    displayProgressBar(nextRow,
                       "  MoistureSensor",
                       sensor->getName(),
                       sensor->getMoistureLevelInPercent());
    nextRow++;
  }
  return nextRow;
}

void TextGui::displayData(int row,
                          const std::string& header,
                          const std::string& name,
                          const std::string& message) {
  ostringstream stream;
  stream << header << "[" << name << "]: ";
  nameEndColumn = std::max(nameEndColumn, int(stream.str().size()));

  const int nameFillSize = nameEndColumn - stream.str().size();
  stream << string(nameFillSize, ' ');

  int lineFillSize = COLS - nameEndColumn - nameFillSize - message.size() - 7;
  stream << message << string(lineFillSize, ' ');

  mvwaddstr(dataWindow, row, DATA_COLUMN, stream.str().c_str());
}

void TextGui::displayProgressBar(int row,
                                 const std::string& header,
                                 const std::string& name,
                                 int progressInPercent) {
  ostringstream stream;
  stream << header << "[" << name << "]: ";

  nameEndColumn = std::max(nameEndColumn, int(stream.str().size()));
  const int nameFillSize = nameEndColumn - stream.str().size();
  stream << string(nameFillSize, ' ');

  const int UNIT_AND_VALUE_SIZE = 14;
  const int totalBarWidth = COLS - nameEndColumn - UNIT_AND_VALUE_SIZE;
  const int filledBarWidth = progressInPercent / 100.0 * totalBarWidth;
  const int blankBarWidth = totalBarWidth - filledBarWidth;

  stream << "[" << string(filledBarWidth, '=') << string(blankBarWidth, ' ');
  stream << "] " << std::setw(3) << std::setfill(' ') << progressInPercent << '%';

  mvwaddstr(dataWindow, row, DATA_COLUMN, stream.str().c_str());
}


} /* namespace ui */
} /* namespace balcony_watering_system */
