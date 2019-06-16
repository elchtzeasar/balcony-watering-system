#include "TextGui.h"

#include "Pump.h"
#include "SoilMoistureSensor.h"

#include <iomanip>
#include <menu.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

namespace balcony_watering_system {
namespace ui {

using ::std::string;
using ::std::vector;

static const int KEY_ENTER_ = 10;

static const std::string START_PUMP_CMD = "start pump";
static const std::string STOP_PUMP_CMD = "stop pump";
static const std::string EXIT_CMD = "exit";

static const int DATA_COLUMN = 3;
static const int PUMP_ROW = 2;
static const int SOIL_ROW = 3;

TextGui::TextGui(logic::Pump& pump, logic::SoilMoistureSensor& soilSensor) :
    pump(pump), soilSensor(soilSensor), dataWindow(NULL) {
}

TextGui::~TextGui() {
}

void TextGui::run() {
  initscr();
  noecho();

  dataWindow = newwin(LINES-5, COLS-2, 3, 1);
  box(dataWindow, 0, 0);

  auto menuWindow = newwin(3, COLS-2, LINES-3, 1);
  box(menuWindow, 0, 0);
  keypad(menuWindow, true);

  nodelay(stdscr, true);
  nodelay(dataWindow, true);
  nodelay(menuWindow, true);

  vector<string> menuOptions = {START_PUMP_CMD, STOP_PUMP_CMD, EXIT_CMD};
  ITEM** menuItems = (ITEM**) calloc(menuOptions.size() + 1, sizeof(ITEM*));
  for (int i = 0; i < menuOptions.size(); ++i) {
    const auto& option = menuOptions.at(i);
    menuItems[i] = new_item(option.c_str(), option.c_str());
  }
  auto menu = new_menu(menuItems);
  menu_opts_off(menu, O_SHOWDESC);
  set_menu_win(menu, menuWindow);
  set_menu_sub(menu, derwin(menuWindow, 1, COLS-4, 1, 1));
  set_menu_format(menu, 1, 3);

  updatePumpMessage();
  updateSoilMessage();

  refresh();
  post_menu(menu);
  wrefresh(dataWindow);
  wrefresh(menuWindow);

  bool keepRunning = true;
  while (keepRunning) {
    int c = wgetch(menuWindow);

    switch (c) {
    case KEY_LEFT:
      menu_driver(menu, REQ_LEFT_ITEM);
      break;
    case KEY_RIGHT:
      menu_driver(menu, REQ_RIGHT_ITEM);
      break;
    case KEY_ENTER_: {
      ITEM* currentItem = current_item(menu);
      string currentName = item_name(currentItem);

      if (currentName == START_PUMP_CMD) {
        doStartPump();
      }
      else if (currentName == STOP_PUMP_CMD) {
        doStopPump();;
      }
      else if (currentName == EXIT_CMD) {
        keepRunning = false;
      }
    } break;
    case 'q':
      keepRunning = false;
      break;
    }

    updatePumpMessage();
    updateSoilMessage();

    wrefresh(dataWindow);
    wrefresh(menuWindow);
  }

  free(menuItems);
  unpost_menu(menu);
  free_menu(menu);
  for (int i = 0; i < menuOptions.size(); ++i) {
    free_item(menuItems[i]);
  }
  endwin();
}

void TextGui::doStartPump() {
  pump.start();
}
void TextGui::doStopPump() {
  pump.stop();
}

void TextGui::updatePumpMessage() {
  std::ostringstream stream;
  stream << "Pump: ";

  if (pump.isPumping()) {
    stream << "pumping    ";
  }
  else {
    stream << "not pumping";
  }
  mvwaddstr(dataWindow, PUMP_ROW, DATA_COLUMN, stream.str().c_str());
}

void TextGui::updateSoilMessage() {
  std::ostringstream stream;

  const int moistureLevel = soilSensor.getMoistureLevel();
  const int PROGRESS_BAR_WIDTH = COLS - 50;
  const int currentWidth = moistureLevel / 100.0 * PROGRESS_BAR_WIDTH;

  stream << "Soil moisture: [";
  stream << string(currentWidth, '=') << string(PROGRESS_BAR_WIDTH - currentWidth, ' ');
  stream << "] " << std::setw(3) << std::setfill(' ') << moistureLevel << '%';

  mvwaddstr(dataWindow, SOIL_ROW, DATA_COLUMN, stream.str().c_str());
}

} /* namespace ui */
} /* namespace balcony_watering_system */
