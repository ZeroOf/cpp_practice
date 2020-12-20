#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <fstream>
#include <boost/log/attributes/mutable_constant.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;

//BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT( lg, src::severity_logger_mt<severity_level>);

#if 0

//[ example_tutorial_file_simple
void init()
{
    logging::add_file_log("sample.log");

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
}
//]

#else

//[ example_tutorial_file_advanced
void init() {
    logging::add_file_log
            (
                    keywords::file_name = "sample_%N.log",                                        /*< file name pattern >*/
                    keywords::rotation_size =
                            10 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
                    keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0,
                                                                                        0), /*< ...or at midnight >*/
                    keywords::format = "[%ThreadID%][%TimeStamp%][%Severity%]: %Message%"                                 /*< log record format >*/
            );

    logging::core::get()->set_filter
            (
                    logging::trivial::severity >= logging::trivial::info
            );
}
//]

void init1() {
    using text_sink = sinks::synchronous_sink<sinks::text_ostream_backend>;
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();
    sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>("sample.log"));

    logging::core::get()->add_sink(sink);
}

#endif

void test() {
    init();
    logging::add_common_attributes();

    using namespace logging::trivial;
    src::severity_logger_mt<severity_level> lg;

    BOOST_LOG_SEV(lg, trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, debug) << "A debug severity message";
    BOOST_LOG_SEV(lg, info) << "An informational severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";
}

void test1() {
    init1();
    src::logger lg;
    BOOST_LOG(lg) << "Hello world!";
}

enum severity_level {
    normal,
    notification,
    warning,
    error,
    critical
};

void init3() {
    logging::core::get()->add_global_attribute("Scope", logging::attributes::named_scope());
}

void named_scope_logging() {
    BOOST_LOG_NAMED_SCOPE("named_scope_logging");

    src::severity_logger<severity_level> slg;

    BOOST_LOG_SEV(slg, normal) << "Hello from the function named_scope_logging!";
}

void test2() {
    src::severity_logger<severity_level> slg;

    BOOST_LOG_SEV(slg, normal) << "A regular message";
    BOOST_LOG_SEV(slg, warning) << "Something bad is going on but I can handle it";
    BOOST_LOG_SEV(slg, critical) << "Everything crumbles, shoot me now!";
}

void foo() {
    src::logger lg;

    // Register a mutable constant attribute that always yields value -5
    attrs::mutable_constant<int> attr(-5);
    lg.add_attribute("MyInteger", attr);
    BOOST_LOG(lg) << "This record has MyInteger == -5";

    // Change the attribute value
    attr.set(100);
    BOOST_LOG(lg) << "This record has MyInteger == 100";
}

int main(int, char *[]) {
    test();
    return 0;
}