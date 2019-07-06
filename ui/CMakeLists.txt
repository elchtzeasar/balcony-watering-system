find_package (Curses REQUIRED)
find_library (MENU_LIBRARY menu)

include_directories (${PROJECT_SOURCE_DIR}/hardware/include)
include_directories (${PROJECT_SOURCE_DIR}/logic/include)
include_directories (${PROJECT_SOURCE_DIR}/ui/include)

add_library (ui src/TextGui.cpp)

target_link_libraries (ui LINK_PUBLIC
  ${CURSES_LIBRARIES}
  ${MENU_LIBRARY})
