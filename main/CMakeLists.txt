find_library (YAML_LIBRARY yaml)
find_library (PIGPIO_LIBRARY pigpio)
find_package (Threads REQUIRED)

include_directories (${PROJECT_SOURCE_DIR}/platform/include)
include_directories (${PROJECT_SOURCE_DIR}/configuration/include)
include_directories (${PROJECT_SOURCE_DIR}/hardware/include)
include_directories (${PROJECT_SOURCE_DIR}/logic/include)
include_directories (${PROJECT_SOURCE_DIR}/ui/include)

include_directories (${PROJECT_SOURCE_DIR}/../boost.di/include/)

add_library (main src/BalconyWateringSystem.cpp)

add_executable (BalconyWateringSystem src/main.cpp)

target_link_libraries (BalconyWateringSystem LINK_PUBLIC
  main
  configuration
  hardware
  logic
  ui
  platform
  Threads::Threads
  ${PIGPIO_LIBRARY}
  ${YAML_LIBRARY})

install (TARGETS BalconyWateringSystem DESTINATION bin)
