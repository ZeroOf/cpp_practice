
#ifndef CPP_PRACTICE_SRC_COMPONENT_UTIL_LOGGER_INTERFACE_H_
#define CPP_PRACTICE_SRC_COMPONENT_UTIL_LOGGER_INTERFACE_H_

#include <string_view>

#define LOG_DEBUG(message) ILogger::GetLogger()->Log(LogLevel::DEBUG, message)

enum LogLevel {
  DEBUG,
  INFO,
  WARNING,
  ERROR
};

class ILogger {
 public:
  virtual ~ILogger() = default;

  virtual void Log(LogLevel level, const std::string_view &message) = 0;
};

#endif //CPP_PRACTICE_SRC_COMPONENT_UTIL_LOGGER_INTERFACE_H_
