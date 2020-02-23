include_directories (${PROJECT_SOURCE_DIR}/configuration/include)

include_directories (${PROJECT_SOURCE_DIR}/platform/include)

add_library (configuration 
  src/AppConfiguration.cpp
  src/WateringLogicConfiguration.cpp
  src/PwmMotorControllerConfiguration.cpp
  src/PumpConfiguration.cpp
  src/TemperatureMeasurementConfiguration.cpp
  src/VolumeMeasurementConfiguration.cpp
  src/Si7021SensorConfiguration.cpp
  src/SimulationConfiguration.cpp
  src/SoilMoistureMeasurementConfiguration.cpp
  src/HumidityMeasurementConfiguration.cpp
  src/ADS1015Configuration.cpp
  src/ArduinoConfiguration.cpp
  src/GroveSoilMoistureSensorConfiguration.cpp
  src/ConfigurationFile.cpp
  )
