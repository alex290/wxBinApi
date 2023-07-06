#ifndef WSBOOSTREAD_H
#define WSBOOSTREAD_H

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <chrono>

namespace beast = boost::beast;  // from <boost/beast.hpp>
namespace http = beast::http;    // from <boost/beast/http.hpp>
// namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;       // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;  // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;  // from <boost/asio/ip/tcp.hpp>

class WsBoostRead : public std::enable_shared_from_this<WsBoostRead>
{
    tcp::resolver resolver_;
    beast::websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws_;

public:
    WsBoostRead(net::io_context& ioc, ssl::context& ctx);
    WsBoostRead(net::io_context& ioc, ssl::context& ctx, int timeout);
    ~WsBoostRead();

    std::function<void(std::string)> signalData;
    std::function<void()> signalClose;
    std::function<void(std::string)> signalError;
    std::function<void()> signalConnect;

    // Запускаем асинхронную операцию
    void run(std::string host, std::string port, std::string text);
    void runTwoo();
    void closeSock();

private:
    beast::flat_buffer buffer_;
    std::string host_;
    std::string text_;
    bool onlyRead;
    int timeoutGlob;

    bool closed;
    // Вывод ошибки
    void fail(beast::error_code ec, char const* what);
    void on_resolve(beast::error_code ec, tcp::resolver::results_type results);

    void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type);

    void on_ssl_handshake(beast::error_code ec);
    void on_handshake(beast::error_code ec);

    void on_write(beast::error_code ec, size_t bytes_transferred);
    void on_read(beast::error_code ec, size_t bytes_transferred);

    void on_close(beast::error_code ec);
};

#endif