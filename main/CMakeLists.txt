find_library (YAML_LIBRARY yaml)

include_directories (${PROJECT_SOURCE_DIR}/configuration/include)
include_directories (${PROJECT_SOURCE_DIR}/hardware/include)
include_directories (${PROJECT_SOURCE_DIR}/logic/include)
include_directories (${PROJECT_SOURCE_DIR}/ui/include)

add_library (main src/BalconyWateringSystem.cpp)
include_directories (${PROJECT_SOURCE_DIR}/../boost.di/include/)


add_executable (BalconyWateringSystem src/main.cpp)

target_link_libraries (BalconyWateringSystem LINK_PUBLIC
  main
  configuration
  hardware
  logic
  ui
  ${YAML_LIBRARY})

install (TARGETS BalconyWateringSystem DESTINATION bin)
