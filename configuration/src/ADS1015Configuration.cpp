#include "ADS1015Configuration.h"

#include <cassert>

namespace balcony_watering_system {
namespace configuration {

ADS1015Configuration::ADS1015Configuration() : logger("hardware.ads1015.configuration") {
}

ADS1015Configuration::~ADS1015Configuration() {
}

void ADS1015Configuration::setField(
    const std::string& fieldName, const std::string& value) {
  if (fieldName == "name-prefix") {
    namePrefix = value;
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => namePrefix=" << namePrefix);
  }
  else {
    assert(false && "unknown field");
  }
}

const std::string& ADS1015Configuration::getNamePrefix() const {
  assert(namePrefix != "" && "namePrefix must be set");
  return namePrefix;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
