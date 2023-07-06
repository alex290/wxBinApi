#include "wsboostread.h"

WsBoostRead::WsBoostRead(net::io_context& ioc, ssl::context& ctx) : resolver_(net::make_strand(ioc)), ws_(net::make_strand(ioc), ctx)
{
    timeoutGlob = 30;
}

WsBoostRead::WsBoostRead(net::io_context& ioc, ssl::context& ctx, int timeout) : resolver_(net::make_strand(ioc)), ws_(net::make_strand(ioc), ctx), timeoutGlob(timeout)
{
}


WsBoostRead::~WsBoostRead()
{

}


// Запускаем асинхронную операцию
void WsBoostRead::run(std::string host, std::string port, std::string text)
{
    // Сохраните их на потом
    host_ = host;
    text_ = text;

    onlyRead = false;

    closed = false;

    // Look up the domain name
    resolver_.async_resolve(host, port, beast::bind_front_handler(&WsBoostRead::on_resolve, shared_from_this()));
}

void WsBoostRead::runTwoo()
{
    // Read a message into our buffer
    ws_.async_read(buffer_, beast::bind_front_handler(&WsBoostRead::on_read, shared_from_this()));
}

// Закрытие сокета
void WsBoostRead::closeSock()
{
    closed = true;
    // Close the WebSocket connection
    ws_.async_close(beast::websocket::close_code::normal, beast::bind_front_handler(&WsBoostRead::on_close, shared_from_this()));
}

// Вывод ошибки
void WsBoostRead::fail(beast::error_code ec, char const* what)
{
    std::cout << std::string(what) + std::string(":") + std::string(ec.message()) << std::endl;
    signalError(std::string(what) + std::string(":") + std::string(ec.message()));
    // cerr << what << ": " << ec.message() << "\n";
}

void WsBoostRead::on_resolve(beast::error_code ec, tcp::resolver::results_type results)
{
    if (ec)
        return fail(ec, "resolve");

    // cout << "On  resolve" << endl;

    // Set a timeout on the operation
    beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(timeoutGlob));

    // Make the connection on the IP address we get from a lookup
    beast::get_lowest_layer(ws_).async_connect(results, beast::bind_front_handler(&WsBoostRead::on_connect, shared_from_this()));
}

void WsBoostRead::on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
{
    if (ec)
        return fail(ec, "connect");
    // cout << "On  connect" << endl;

    // Set a timeout on the operation
    beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(timeoutGlob));

    // Perform the SSL handshake
    ws_.next_layer().async_handshake(ssl::stream_base::client, beast::bind_front_handler(&WsBoostRead::on_ssl_handshake, shared_from_this()));
}

void WsBoostRead::on_ssl_handshake(beast::error_code ec)
{
    if (ec)
        return fail(ec, "ssl_handshake");

    // cout << "On  ssl_handshake" << endl;

    // Turn off the timeout on the tcp_stream, because
    // the websocket stream has its own timeout system.
    beast::get_lowest_layer(ws_).expires_never();

    // Set suggested timeout settings for the websocket
    ws_.set_option(beast::websocket::stream_base::timeout::suggested(beast::role_type::client));

    // Set a decorator to change the User-Agent of the handshake
    ws_.set_option(beast::websocket::stream_base::decorator([](beast::websocket::request_type& req) { req.set(http::field::user_agent, std::string(BOOST_BEAST_VERSION_STRING) + " websocket-client-async-ssl"); }));

    // Perform the websocket handshake
    ws_.async_handshake(host_, text_, beast::bind_front_handler(&WsBoostRead::on_handshake, shared_from_this()));
}

void WsBoostRead::on_handshake(beast::error_code ec)
{
    if (ec)
        return fail(ec, "handshake");

    signalConnect();

    // cout << "On  handshake" << endl;

    // Send the message
    // ws_.async_write(net::buffer(text_), beast::bind_front_handler(&WsBoostRead::on_write, shared_from_this()));

    // Read a message into our buffer
    ws_.async_read(buffer_, beast::bind_front_handler(&WsBoostRead::on_read, shared_from_this()));
}

void WsBoostRead::on_write(beast::error_code ec, size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return fail(ec, "write");

    // cout << "On  write" << endl;

    // Read a message into our buffer
    ws_.async_read(buffer_, beast::bind_front_handler(&WsBoostRead::on_read, shared_from_this()));
}

void WsBoostRead::on_read(beast::error_code ec, size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (!closed)
    {
        if (ec)
            return fail(ec, "read");

        std::string d = beast::buffers_to_string(buffer_.data());
        // cout << "On  read " << d << endl;

        signalData(d);
        buffer_.clear();
        // Read a message into our buffer
        ws_.async_read(buffer_, beast::bind_front_handler(&WsBoostRead::on_read, shared_from_this()));
        // Close the WebSocket connection
        // ws_.async_close(beast::websocket::close_code::normal, beast::bind_front_handler(&WsBoostRead::on_close, shared_from_this()));
    }
}

void WsBoostRead::on_close(beast::error_code ec)
{
    signalClose();
    // if (ec)
    //     return fail(ec, "close");

    // std::cout << "CloSSE" << std::endl;

    // If we get here then the connection is closed gracefully

    // The make_printable() function helps print a ConstBufferSequence
    // cout << beast::make_printable(buffer_.data()) << endl;
}