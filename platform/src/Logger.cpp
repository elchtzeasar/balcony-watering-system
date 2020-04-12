#include "Logger.h"

#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>

namespace balcony_watering_system {
namespace platform {

using ::std::ofstream;
using ::std::ostream;
using ::std::string;
using ::std::localtime;
using ::std::put_time;

Logger::Logger(const string& name) : name(name) {}
Logger::Logger(const string& prefix, const string& name) :
    name(string(prefix).append(".").append(name)) {}
Logger::Logger(const string& prefix, const string& name, const string& postfix) :
    name(string(prefix).append(".").append(name).append(".").append(postfix)) {}

void Logger::log(LogLevel level, const string& msg) const {
  ofstream stream{"log.txt", std::ios_base::out | std::ios_base::app};

  const auto now = std::chrono::system_clock::now();
  const auto now_t = std::chrono::system_clock::to_time_t(now);
  const auto format = "%F %T";

  stream << put_time(localtime(&now_t), format) << " " << level << " " << name << " - " << msg << std::endl;
}

ostream& operator<<(ostream& stream, const LogLevel& level) {
  switch (level) {
  case LogLevel::TRACE: stream << "TRACE"; break;
  case LogLevel::DEBUG: stream << "DEBUG"; break;
  case LogLevel::INFO: stream << "INFO"; break;
  case LogLevel::WARN: stream << "WARN"; break;
  case LogLevel::ERROR: stream << "ERROR"; break;
  case LogLevel::FATAL: stream << "FATAL"; break;
  default: stream << "UNKNOWN"; break;
  }

  return stream;
}

} /* namespace platform */
} /* namespace balcony_watering_system */
