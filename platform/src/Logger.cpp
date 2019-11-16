/*
 *  Created on: Oct 13, 2019
 *      Author: peter
 */

#include "Logger.h"

#include <fstream>

namespace balcony_watering_system {
namespace platform {

using ::std::ofstream;
using ::std::ostream;
using ::std::string;

Logger::Logger(const string& name) : name(name) {}
Logger::Logger(const string& prefix, const string& name) :
    name(string(prefix).append(".").append(name)) {}
Logger::Logger(const string& prefix, const string& name, const string& postfix) :
    name(string(prefix).append(".").append(name).append(".").append(postfix)) {}

void Logger::log(LogLevel level, const string& msg) const {
  ofstream stream{"log.txt", std::ios_base::out | std::ios_base::app};

  stream << level << " " << name << " - " << msg << std::endl;
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
