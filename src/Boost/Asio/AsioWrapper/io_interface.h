#ifndef CPP_PRACTICE_SRC_BOOST_ASIO_TCPCLIENT_IO_INTERFACE_H_
#define CPP_PRACTICE_SRC_BOOST_ASIO_TCPCLIENT_IO_INTERFACE_H_

#include <string>
#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>

namespace TcpIO {

    using buffer_iterator = boost::asio::buffers_iterator<boost::asio::dynamic_vector_buffer<char, std::allocator<char>>::const_buffers_type>;

    class IOInterface : public std::enable_shared_from_this<IOInterface> {
    public:
        virtual void OnRead(std::vector<char> msg) = 0;

        virtual void OnConnected() = 0;

        virtual void OnConnectFailed() = 0;

        virtual void OnSend(bool isSendSuccess, uint32_t msgType) = 0;

        virtual std::pair<buffer_iterator, bool> IsPackageComplete(buffer_iterator begin, buffer_iterator end) = 0;

        virtual void OnClose() = 0;

        virtual void Start() {}
    };
}

#endif //CPP_PRACTICE_SRC_BOOST_ASIO_TCPCLIENT_IO_INTERFACE_H_
