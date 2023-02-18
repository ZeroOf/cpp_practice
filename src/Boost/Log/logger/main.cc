//
// Created by god on 2021/3/31.
//

#include <boost/log/core.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;

int main() {
    src::logger lg;
    logging::record rec = lg.open_record();
    if (rec) {
        logging::record_ostream strm(rec);
        strm << "Hello, World!";
        strm.flush();
        lg.push_record(boost::move(rec));
    }
}