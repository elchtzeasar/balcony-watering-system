find_library (YAML_LIBRARY yaml)

include_directories (${PROJECT_SOURCE_DIR}/configuration/include)
include_directories (${PROJECT_SOURCE_DIR}/hardware/include)
include_directories (${PROJECT_SOURCE_DIR}/logic/include)
include_directories (${PROJECT_SOURCE_DIR}/ui/include)

add_library (main src/BalconyWateringSystem.cpp)

add_executable (BalconyWateringSystem src/main.cpp)

target_link_libraries (BalconyWateringSystem LINK_PUBLIC
  ${YAML_LIBRARY}
  main
  configuration
  hardware
  logic
  ui)

install (TARGETS BalconyWateringSystem DESTINATION bin)
