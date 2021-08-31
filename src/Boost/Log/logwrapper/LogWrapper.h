//
// Created by God on 2021/4/29.
//

#ifndef CPP_PRACTICE_LOGWRAPPER_H
#define CPP_PRACTICE_LOGWRAPPER_H

#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/expressions.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>

enum LogLevel {
    DEBUG,
    INFO,
    ERROR
};

BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", LogLevel)

class LogWrapper : public boost::serialization::singleton<LogWrapper> {
public:
    LogWrapper();

    void Init();

    void SetLevel(LogLevel level);

    boost::log::sources::severity_logger_mt<LogLevel> &GetLog();

    virtual ~LogWrapper();

private:
    boost::log::sources::severity_logger_mt<LogLevel> m_log;

    void ConsoleLog() const;
};


boost::log::formatting_ostream &
operator<<(boost::log::formatting_ostream &strm, boost::log::to_log_manip<LogLevel, tag::severity> const &manip);


#define LOG(level, MSG) { \
    BOOST_LOG_SEV(LogWrapper::get_mutable_instance().GetLog(), level) << boost::filesystem::path( __FILE__ ).filename().string() << ":" << __LINE__ << " [" << __func__ << "] "<< MSG; \
}

#define LOG_DEBUG(MSG) LOG(DEBUG, MSG)
#define LOG_INFO(MSG) LOG(INFO, MSG)
#define LOG_ERROR(MSG) LOG(ERROR, MSG)


#endif //CPP_PRACTICE_LOGWRAPPER_H
