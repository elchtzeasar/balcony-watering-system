find_package (Curses REQUIRED)
find_library (MENU_LIBRARY menu)

include_directories (${PROJECT_SOURCE_DIR}/platform/include)
include_directories (${PROJECT_SOURCE_DIR}/hardware/include)
include_directories (${PROJECT_SOURCE_DIR}/logic/include)
include_directories (${PROJECT_SOURCE_DIR}/app/include)

add_library (app
  src/App.cpp
  src/TextGui.cpp)

target_link_libraries (app LINK_PUBLIC
  ${CURSES_LIBRARIES}
  ${MENU_LIBRARY})
