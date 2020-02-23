#include "AppConfiguration.h"

#include "LexicalCast.h"

#include <cassert>

namespace std {
ostream& operator<<(ostream& stream, const chrono::milliseconds& seconds);
}

namespace balcony_watering_system {
namespace configuration {

using ::balcony_watering_system::platform::lexical_cast;
using ::std::chrono::milliseconds;
using ::std::string;

AppConfiguration::AppConfiguration() : logger("logic.app.configuration"), mode(Mode::NO_APP), cycleTime(milliseconds(0)) {
}

AppConfiguration::~AppConfiguration() {
}

std::ostream& operator<<(std::ostream& stream, const IAppConfiguration::Mode& mode) {
  switch (mode) {
  case IAppConfiguration::Mode::NO_APP: stream << "NO_APP"; break;
  case IAppConfiguration::Mode::TEXT_GUI: stream << "TEXT_GUI"; break;
  case IAppConfiguration::Mode::SINGLE_RUN: stream << "SINGLE_RUN"; break;
  default: stream << "UNKNOWN (" << int(mode) << ")"; break;
  }

  return stream;
}

IAppConfiguration::Mode toMode(const std::string& string) {
  if (string == "text-gui") {
    return IAppConfiguration::Mode::TEXT_GUI;
  }
  else if (string == "single-run") {
    return IAppConfiguration::Mode::SINGLE_RUN;
  }

  return IAppConfiguration::Mode::NO_APP;
}

void AppConfiguration::setField(
    const string& fieldName, const string& value) {
  if (fieldName == "mode") {
    mode = toMode(value);
    LOG_DEBUG(logger, "fieldName=" << fieldName << " => mode=" << mode);
  }
  else if (fieldName == "cycle-time-in-millis") {
    cycleTime = milliseconds(lexical_cast<int>(value));
    LOG_DEBUG(logger, "fieldName=" << fieldName << ", value=" << value << " => cycleTime=" << cycleTime);
  }
  else {
    assert(false && "unknown field");
  }
}

IAppConfiguration::Mode AppConfiguration::getMode() const {
  return mode;
}

const milliseconds& AppConfiguration::getCycleTime() const {
  assert(cycleTime > milliseconds(0) && "cycle time must be set");
  return cycleTime;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */

namespace std {

ostream& operator<<(ostream& stream, const chrono::milliseconds& seconds) {
  stream << seconds.count() << "ms";
  return stream;
}

}
