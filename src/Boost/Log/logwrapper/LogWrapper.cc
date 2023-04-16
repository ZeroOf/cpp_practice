//
// Created by God on 2021/4/29.
//

#include "LogWrapper.h"
#include <boost/log/common.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/thread.hpp>
#include <filesystem>

namespace logging = boost::log;
namespace attrs = logging::attributes;
namespace keywords = logging::keywords;
namespace expr = logging::expressions;

LogWrapper::LogWrapper() {
}

LogWrapper::~LogWrapper() {

}

void LogWrapper::Init(std::string logName) {
  ptr_log_ = std::make_unique<boost::log::sources::severity_logger<LogLevel>>();
  logging::add_common_attributes();
//    ConsoleLog();
  AddLogFile(logName);
  SetLevel(DEBUG);
}

void LogWrapper::ConsoleLog() const {
  logging::add_console_log(std::cout, keywords::format = (
      expr::stream << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
                   << " " << severity << " " << expr::smessage
  ));
}

void LogWrapper::SetLevel(LogLevel level) {
  logging::core::get()->set_filter(severity >= level);
}

boost::log::sources::severity_logger<LogLevel> &LogWrapper::GetLog() {
  return *ptr_log_;
}

void LogWrapper::AddLogFile(std::string logName) {
  std::filesystem::path logPath = std::filesystem::path("../log/");

  logging::add_file_log(
      keywords::file_name = "../log/" + logName + ".log",
      keywords::target_file_name = "../log/" + logName + "%Y%m%d-%N.log",
      keywords::rotation_size = 10 * 1024 * 1024,
      keywords::max_size = 100 * 1024 * 1024,
      keywords::max_files = 3,
      keywords::enable_final_rotation = true,
//      keywords::open_mode = std::ios_base::app,
      keywords::target = logPath,
      keywords::format = (
          expr::stream << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
                       << " " << severity << " " << expr::smessage
      ),
      keywords::auto_flush = true);
}

boost::log::formatting_ostream &
operator<<(boost::log::formatting_ostream &strm, const boost::log::to_log_manip<LogLevel, tag::severity> &manip) {
  static const char *strings[] = {
      "DEBUG",
      "INFO",
      "ERROR"
  };
  LogLevel level = manip.get();
  if (level < sizeof(strings) / sizeof(*strings)) {
    strm << std::setw(5) << strings[level];
  } else {
    strm << static_cast<int>(level);
  }
  return strm;
}
