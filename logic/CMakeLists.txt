include_directories (${PROJECT_SOURCE_DIR}/platform/include)
include_directories (${PROJECT_SOURCE_DIR}/configuration/include)
include_directories (${PROJECT_SOURCE_DIR}/hardware/include)
include_directories (${PROJECT_SOURCE_DIR}/logic/include)

add_library (logic
  src/Logic.cpp
  src/HumidityMeasurement.cpp
  src/Pump.cpp
  src/SoilMoistureMeasurement.cpp
  src/LogicFactory.cpp
  src/VolumeMeasurement.cpp
  src/TemperatureMeasurement.cpp
  src/WateringLogic.cpp
  )
