#include "TextGui.h"

#include <menu.h>
#include <ncurses.h>
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

TextGui::TextGui() {
}

TextGui::~TextGui() {
}

void TextGui::run() {
  initscr();
  noecho();

  auto menuWindow = newwin(3, COLS-2, LINES-3, 1);
  box(menuWindow, 0, 0);
  keypad(menuWindow, true);

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

  printw("TextGuid");

  refresh();
  post_menu(menu);
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

void TextGui::doStartPump() {}
void TextGui::doStopPump() {}

} /* namespace ui */
} /* namespace balcony_watering_system */
