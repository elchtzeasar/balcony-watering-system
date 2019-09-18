
include_directories (${PROJECT_SOURCE_DIR}/configuration/include)

add_library (configuration 
  src/PumpConfiguration.cpp
  src/TemperatureMeasurementConfiguration.cpp
  src/VolumeMeasurementConfiguration.cpp
  src/Si7021SensorConfiguration.cpp
  src/SimulationConfiguration.cpp
  src/SoilMoistureMeasurementConfiguration.cpp
  src/HumidityMeasurementConfiguration.cpp
  src/ConfigurationFile.cpp
  )
