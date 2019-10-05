include_directories (${PROJECT_SOURCE_DIR}/configuration/include)
include_directories (${PROJECT_SOURCE_DIR}/hardware/include)

add_library (hardware
  src/SimulatedHumiditySensor.cpp
  src/HWFactory.cpp
  src/SimulatedTemperatureSensor.cpp
  src/SimulatedSoilMoistureSensor.cpp
  src/SimulatedMotor.cpp
  src/SimulatedDistanceSensor.cpp
  src/Si7021Sensor.cpp
  src/ADS1015.cpp
  src/AnalogInput.cpp
  src/Master.cpp
  )
