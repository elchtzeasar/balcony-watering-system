/*
 *  Created on: Oct 13, 2019
 *      Author: peter
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <sstream>

#define LOG_LEVEL(logger, msg, lvl) {                  \
 do {                                                  \
    std::ostringstream stream;                         \
    stream << msg;                                     \
    logger.log(platform::LogLevel::lvl, stream.str()); \
  } while(false);                                      \
}

#define LOG_TRACE(logger, msg) { \
  LOG_LEVEL(logger, msg, TRACE); \
}
#define LOG_DEBUG(logger, msg) { \
  LOG_LEVEL(logger, msg, DEBUG); \
}
#define LOG_INFO(logger, msg) { \
  LOG_LEVEL(logger, msg, INFO); \
}
#define LOG_WARN(logger, msg) { \
  LOG_LEVEL(logger, msg, WARN); \
}
#define LOG_ERROR(logger, msg) { \
  LOG_LEVEL(logger, msg, ERROR); \
}
#define LOG_FATAL(logger, msg) { \
  LOG_LEVEL(logger, msg, FATAL); \
}

namespace balcony_watering_system {
namespace platform {

enum class LogLevel {
  TRACE,
  DEBUG,
  INFO,
  WARN,
  ERROR,
  FATAL,
};
std::ostream& operator<<(std::ostream& stream, const LogLevel& level);

class Logger {
public:
  Logger(const std::string& name);
  Logger(const std::string& prefix, const std::string& name);
  Logger(const std::string& prefix, const std::string& name, const std::string& postfix);
  virtual ~Logger() = default;

  Logger() = delete;

  void log(LogLevel level, const std::string& msg) const;

private:
  const std::string name;
};

} /* namespace platform */
} /* namespace balcony_watering_system */

#endif /* LOGGER_H_ */
