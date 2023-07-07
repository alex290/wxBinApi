#include "loadstreamdata.h"

wxDEFINE_EVENT(WSBAPI_RET_DATA, WsReadEvent);
wxDEFINE_EVENT(WSBAPI_RET_ERROR, WsReadEvent);
wxDEFINE_EVENT(WSBAPI_RET_CLOSE, WsReadEvent);
wxDEFINE_EVENT(WSBAPI_RET_CONNECT, WsReadEvent);

LoadStreamData::LoadStreamData(int timeout) : timeoutGlob(timeout)
{
    closed = false;
}

LoadStreamData::LoadStreamData()
{
    timeoutGlob = 30;
    datGlobal = "";
    closed = false;
}

LoadStreamData::~LoadStreamData()
{
}

void LoadStreamData::startSocket(std::string host, std::string port, std::string text)
{
    q = std::async(std::launch::async, [host, port, text, this] { this->asyncStart(host, port, text); });
}

void LoadStreamData::startSocket(std::string host, std::string text)
{
    startSocket(host, "443", text);
}

void LoadStreamData::closeSocket()
{
    closed = true;
    // net::io_context::work

    work.reset();
    ioc.stop();
}

void LoadStreamData::asyncStart(std::string host, std::string port, std::string text) {
    ssl::context ctx{ ssl::context::sslv23 };
    ctx.set_verify_mode(ssl::verify_none);

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    std::shared_ptr link = std::make_shared<WsBoostRead>(ioc, ctx, timeoutGlob);
    // Подключаем сигнал к фукции
    link->signalData = [&, this](std::string dat) { this->eventData(dat); };
    // Подключаем сигнал к фукции
    link->signalClose = [this]() { this->eventClose(); };
    // Подключаем сигнал к фукции
    link->signalError = [&, this](std::string dat) { this->eventError(dat); };

    // Подключаем сигнал к фукции
    link->signalConnect = [this]() { this->eventConnect(); };

    link->run(host, port, text);

    // Run the I/O service. The call will return when
    // the socket is closed.
    bool first = true;
    bool exit = true;

    // ioc.run();

    while (exit)
    {
        if (!first)
            ioc.restart();
        if (closed)
        {
            link->closeSock();
            ioc.run();
            exit = false;
        }
        else if (first)
        {
            first = false;
            ioc.run();
        }
        else
        {
            link->runTwoo();
            ioc.run();
        }
    }

    work.reset();
}

void LoadStreamData::eventData(std::string data) {
     WsReadEvent event(WSBAPI_RET_DATA, idSocket, data);
    event.SetEventObject(this);
    ProcessEvent(event);
    // wxPostEvent(this, event);
}

void LoadStreamData::eventClose() {
    // std::cout << "CloSSE" << std::endl;
    WsReadEvent event(WSBAPI_RET_CLOSE, idSocket, "CLOSE");
    event.SetEventObject(this);
    ProcessEvent(event);
    // wxPostEvent(this, event);
}

void LoadStreamData::eventError(std::string data) {
    WsReadEvent event(WSBAPI_RET_ERROR, idSocket, data);
    event.SetEventObject(this);
    ProcessEvent(event);
    // wxPostEvent(this, event);
}

void LoadStreamData::eventConnect() {
    WsReadEvent event(WSBAPI_RET_CONNECT, idSocket, "CONNECT");
    event.SetEventObject(this);
    ProcessEvent(event);
    // wxPostEvent(this, event);
}
