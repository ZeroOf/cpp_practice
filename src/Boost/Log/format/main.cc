//
// Created by god on 2021/4/3.
//

#include <boost/log/core.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/support/exception.hpp>

namespace logging = boost::log;

void init() {
    logging::core::get()->add_global_attribute("TimeStamp", logging::attributes::local_clock());
    logging::core::get()->add_global_attribute("Scope", logging::attributes::named_scope());
    logging::add_console_log(
            std::cout,
            logging::keywords::format="[%TimeStamp%][%Scope%]:%Message%"
    );
}

int main() {
    init();
    BOOST_LOG_NAMED_SCOPE( __FILE__ );
    logging::sources::logger lg;
    BOOST_LOG(lg) << "Hello world";
}