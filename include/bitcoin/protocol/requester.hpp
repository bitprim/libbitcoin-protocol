//code simple_req_connect(const config::endpoint& address);
//
//code simple_req_send(const google::protobuf::MessageLite& request,
//                     google::protobuf::MessageLite& reply);


#ifndef LIBBITCOIN_PROTOCOL_REQUESTER_HPP
#define LIBBITCOIN_PROTOCOL_REQUESTER_HPP

#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <boost/optional.hpp>
#include <google/protobuf/message_lite.h>
#include <bitcoin/bitcoin/config/endpoint.hpp>
#include <bitcoin/bitcoin/utility/asio.hpp>
#include <bitcoin/bitcoin/utility/thread.hpp>
#include <bitcoin/protocol/zmq/context.hpp>
#include <bitcoin/protocol/zmq/socket.hpp>

namespace libbitcoin {
namespace protocol {

class BCP_API requester
{
public:

    requester(zmq::context& context);

    requester(zmq::context& context, const config::endpoint& address);

    requester(const requester&) = delete;
    void operator=(const requester&) = delete;

    ~requester();

    operator const bool() const;

    code connect(const config::endpoint& address);

    code disconnect();

    code send(const google::protobuf::MessageLite& request,
              google::protobuf::MessageLite& reply);

    template <typename Message, typename Arg, typename Handler>
    std::string make_handler(Arg const& arg, Handler const& handler)
    {
        handler_type h;
        h.single = true;
        h.function =
            [=] (const data_chunk& payload) -> code
            {
                Message message;
                const void* data = payload.data();
                const int size = static_cast<int>(payload.size());
                if (!message.ParseFromArray(data, size))
                    return error::bad_stream;

                handler(arg, message);
                return error::success;
            };

        return add_handler(Message{}.GetTypeName(), std::move(h));
    }

    template <typename Message, typename Arg, typename Handler>
    std::string make_subscription(Arg const& arg, Handler const& handler)
    {
        handler_type h;
        h.single = false;
        h.function =
            [=] (const data_chunk& payload) -> code
            {
                Message message;
                const void* data = payload.data();
                const int size = static_cast<int>(payload.size());
                if (!message.ParseFromArray(data, size))
                    return error::bad_stream;

                handler(arg, message);
                return error::success;
            };

        return add_handler(Message{}.GetTypeName(), std::move(h));

    }


    code simple_req_connect(const config::endpoint& address);

    code simple_req_send(const google::protobuf::MessageLite& request,
                         google::protobuf::MessageLite& reply);

private:
    struct handler_type
    {
        bool single = true;
        std::function<code(const data_chunk&)> function;
    };

    code do_connect(const config::endpoint& address);

    code do_send(const google::protobuf::MessageLite& request,
                 google::protobuf::MessageLite& reply);

    std::string add_handler(const std::string& message_name,
                            handler_type handler);

    void call_handler(const std::string& id,
        const data_chunk& payload);

    zmq::context& _context;
    asio::service _io_service;
    asio::service::work _io_work;
    boost::optional<zmq::socket> _socket;
    asio::thread _io_thread;

    mutable std::mutex _handlers_mutex;
    uint64_t _next_handler_id = 0;
    
    // std::map<std::string, handler_type> _handlers;

    using handlers_value_t = std::pair<std::string, handler_type>;
    std::vector<handlers_value_t> _handlers;

    bc::threadpool _handlers_threadpool;
    boost::optional<zmq::socket> _subscriber_socket;
    std::string _subscriber_endpoint;
};

} // namespace protocol
} // namespace libbitcoin

#endif