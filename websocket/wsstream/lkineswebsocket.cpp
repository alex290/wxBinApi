#include "lkineswebsocket.h"

LKInesWebSocket::LKInesWebSocket(DatGlobBinApi* data) : dataGlobal(data)
{
    ws = new LoadStreamData(15);
    startLoad = false;
    ws->Bind(WSBAPI_RET_ERROR, &LKInesWebSocket::Error, this);
    ws->Bind(WSBAPI_RET_CLOSE, &LKInesWebSocket::Close, this);
    ws->Bind(WSBAPI_RET_CONNECT, &LKInesWebSocket::Connect, this);
    ws->streamData = [this](std::string data) { ReadData(data); };
}

LKInesWebSocket::~LKInesWebSocket()
{
    if (startLoad)
        ws->closeSocket();

    delete ws;
}

void LKInesWebSocket::Start(std::vector<std::string>& symbols, std::string& inerval)  // Запуск свечных данных Websocket
{
    std::string baseUrlFut = "/stream?streams=";
    for (size_t i = 0; i < symbols.size(); i++)
    {
        if (i > 0)
        {
            baseUrlFut = baseUrlFut + "/";
        }
        baseUrlFut = baseUrlFut + FormatDop::str_tolower(symbols[i]) + "@kline_" + inerval;
    }
    std::cout << "Start klines - symbols: " << baseUrlFut << std::endl;
    ws->startSocket("fstream.binance.com", baseUrlFut);
    startLoad = true;
}
void LKInesWebSocket::ReadData(std::string data)
{
    streamData(data);
}

void LKInesWebSocket::Error(WsReadEvent& even)
{
}

void LKInesWebSocket::Close(WsReadEvent& even)
{
    std::cout << "Close" << std::endl;
}

void LKInesWebSocket::Connect(WsReadEvent& even)
{
}
