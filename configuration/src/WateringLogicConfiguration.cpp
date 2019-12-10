#include "WateringLogicConfiguration.h"

#include "LexicalCast.h"

#include <cassert>

namespace std {
ostream& operator<<(ostream& stream, const chrono::seconds& seconds);
}

namespace balcony_watering_system {
namespace configuration {

using ::balcony_watering_system::platform::lexical_cast;
using ::std::chrono::minutes;
using ::std::chrono::seconds;
using ::std::string;

WateringLogicConfiguration::WateringLogicConfiguration() : logger("logic.watering-logic.configuration"), timeToWater(minutes(0)) {
}

WateringLogicConfiguration::~WateringLogicConfiguration() {
}

void WateringLogicConfiguration::setField(
    const string& fieldName, const string& value) {
  if (fieldName == "pump-controller") {
    pumpController = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => pumpController=" << pumpController);
  }
  else if (fieldName == "soil-moisture") {
    soilMoistureMeasurement = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => soilMoistureMeasurement=" << soilMoistureMeasurement);
  }
  else if (fieldName == "humidity") {
    humidityMeasurement = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => humidityMeasurement=" << humidityMeasurement);
  }
  else if (fieldName == "temperature") {
    temperatureMeasurement = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => temperatureMeasurement=" << temperatureMeasurement);
  }
  else if (fieldName == "minutes-to-water") {
    timeToWater = seconds(lexical_cast<int>(value) * 60);
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => timeToWater=" << timeToWater);
  }
  else if (fieldName == "seconds-to-water") {
    timeToWater = seconds(lexical_cast<int>(value));
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => timeToWater=" << timeToWater);
  }
  else if (fieldName == "minutes-to-not-water") {
    timeToNotWater = seconds(lexical_cast<int>(value) * 60);
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => timeToNotWater=" << timeToWater);
  }
  else if (fieldName == "seconds-to-not-water") {
    timeToNotWater = seconds(lexical_cast<int>(value));
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => timeToNotWater=" << timeToWater);
  }
  else {
    assert(false && "unknown field");
  }
}

const string& WateringLogicConfiguration::getPumpController() const  {
  assert(pumpController != "" && "name must be set");
  return pumpController;
}

const string& WateringLogicConfiguration::getSoilMoistureMeasurement() const  {
  return soilMoistureMeasurement;
}

const string& WateringLogicConfiguration::getHumidityMeasurement() const  {
  return humidityMeasurement;
}

const string& WateringLogicConfiguration::getTemperatureMeasurement() const {
  return temperatureMeasurement;
}

const seconds& WateringLogicConfiguration::getTimeToWater() const {
  assert(timeToWater > minutes(0) && "time to water must be set");
  return timeToWater;
}

const seconds& WateringLogicConfiguration::getTimeToNotWater() const {
  assert(timeToNotWater > minutes(0) && "time to not water must be set");
  return timeToNotWater;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */

namespace std {

ostream& operator<<(ostream& stream, const chrono::seconds& seconds) {
  stream << seconds.count() << "s";
  return stream;
}

}
