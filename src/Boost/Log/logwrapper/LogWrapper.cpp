//
// Created by God on 2021/4/29.
//

#include "LogWrapper.h"
#include <boost/log/common.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>

namespace logging = boost::log;
namespace attrs = logging::attributes;
namespace keywords = logging::keywords;
namespace expr = logging::expressions;

LogWrapper::LogWrapper() {
    Init();
}

LogWrapper::~LogWrapper() {

}

void LogWrapper::Init() {
    logging::add_common_attributes();
    ConsoleLog();
    SetLevel(DEBUG);
}

void LogWrapper::ConsoleLog() const {
    logging::add_console_log(std::cout, keywords::format = (
            expr::stream << boost::log::v2s_mt_posix::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
                         << " " << severity << " " << expr::smessage
    ));
}

void LogWrapper::SetLevel(LogLevel level) {
    logging::core::get()->set_filter(severity >= level);
}

boost::log::sources::severity_logger_mt<LogLevel> &LogWrapper::GetLog() {
    return m_log;
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
        strm << strings[level];
    } else {
        strm << static_cast<int>(level);
    }
    return strm;
}
