#include "TextGui.h"

#include "LogicFactory.h"
#include "Pump.h"
#include "SoilMoistureSensor.h"

#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <vector>

namespace balcony_watering_system {
namespace ui {

using ::balcony_watering_system::logic::LogicFactory;
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

TextGui::TextGui(LogicFactory& logicFactory) :
    pumps(logicFactory.getPumps()),
    soilSensors(logicFactory.getSoilMoistureSensors()),
    dataWindow(NULL),
    menuWindow(NULL),
    menu(NULL),
    menuItems(NULL) {
  initscr();
  noecho();

  dataWindow = newwin(LINES-5, COLS-2, 3, 1);
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
  nextDataRow = updateSoilMessages(nextDataRow);

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
  nextDataRow = updateSoilMessages(nextDataRow);

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

    ostringstream stream;
    stream << "Pump[" << pump->getName() << "]: ";
    if (isPumping) {
      stream << "pumping    ";
    }
    else {
      stream << "not pumping";
    }

    mvwaddstr(dataWindow, nextRow, DATA_COLUMN, stream.str().c_str());
    nextRow++;
  }
  return nextRow;
}

int TextGui::updateSoilMessages(int nextRow) {
  for (auto sensor : soilSensors) {
    ostringstream stream;

    const int moistureLevel = sensor->getMoistureLevel();

    const int PROGRESS_BAR_WIDTH = COLS - 50;
    const int currentWidth = moistureLevel / 100.0 * PROGRESS_BAR_WIDTH;

    stream << "Soil moisture[" << sensor->getName() << "]: ";
    stream << string(currentWidth, '=') << string(PROGRESS_BAR_WIDTH - currentWidth, ' ');
    stream << "] " << std::setw(3) << std::setfill(' ') << moistureLevel << '%';

    mvwaddstr(dataWindow, nextRow, DATA_COLUMN, stream.str().c_str());
    nextRow++;
  }
  return nextRow;
}

} /* namespace ui */
} /* namespace balcony_watering_system */
