#ifndef LOADSTREAMDATA_H
#define LOADSTREAMDATA_H

#include "wsboostread.h"
#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include <queue>
#include <wx/event.h>
#include "../../data/events/wsreadevent.h"

wxDECLARE_EVENT(WSBAPI_RET_ERROR, WsReadEvent);
wxDECLARE_EVENT(WSBAPI_RET_CLOSE, WsReadEvent);
wxDECLARE_EVENT(WSBAPI_RET_CONNECT, WsReadEvent);

class LoadStreamData : public wxEvtHandler
{
public:
    LoadStreamData(int timeout);
    LoadStreamData();
    ~LoadStreamData();

    std::function<void(std::string)> streamData;

    void startSocket(std::string host, std::string port, std::string text);  // Запуск сокета
    void startSocket(std::string host, std::string text);                    // Запуск сокета

    void closeSocket();  // Закрытие сокета

    std::string idSocket = "Socket";

private:
    int timeoutGlob;
    net::io_context ioc;
    net::executor_work_guard<decltype(ioc.get_executor())> work{ ioc.get_executor() };

    void asyncStart(std::string host, std::string port, std::string text);  // Запуск асинхроного сокета
    std::string datGlobal;
    // queue<future<void>> q;
    std::future<void> q;
    std::queue<std::future<void>> qw;
    bool closed;

    void clearSocket();

    void eventData(std::string data);   // Отправка сигнала
    void eventClose();                  // Закрытие
    void eventError(std::string data);  // Отправка ошибки
    void eventConnect();                // Закрытие
};

#endif