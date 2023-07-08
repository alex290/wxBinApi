#include "lkineswebsocket.h"

LKInesWebSocket::LKInesWebSocket(DatGlobBinApi* data) : dataGlobal(data)
{
    ws = new LoadStreamData(15);
    startLoad = false;
    ws->Bind(WSBAPI_RET_DATA, &LKInesWebSocket::ReadData, this);
    ws->Bind(WSBAPI_RET_ERROR, &LKInesWebSocket::Error, this);
    ws->Bind(WSBAPI_RET_CLOSE, &LKInesWebSocket::Close, this);
    ws->Bind(WSBAPI_RET_CONNECT, &LKInesWebSocket::Connect, this);
}

LKInesWebSocket::~LKInesWebSocket()
{
    if (startLoad)
        ws->closeSocket();

    delete ws;
}

void LKInesWebSocket::Start(std::vector<std::string>& symbols, std::string& inerval)  // Запуск свечных данных Websocket
{
    symbols_ = symbols;
    inerval_ = inerval;

    if (startLoad) // Если уже идет загрузка то закрываем
    {
        ws->closeSocket();
    }
    else
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
        ws->startSocket("fstream.binance.com", baseUrlFut);
        startLoad = true;
        std::cout << "Start klines - symbols: " << baseUrlFut << std::endl;
    }
}
void LKInesWebSocket::ReadData(WsReadEvent& even)
{
    Bapi::Json data = BinJson::parse(even.getData());
    std::cout << data.dump() << std::endl;
}

void LKInesWebSocket::Error(WsReadEvent& even)
{
}

void LKInesWebSocket::Close(WsReadEvent& even)
{
    std::cout << "Close" << std::endl;
    startLoad = false;
}

void LKInesWebSocket::Connect(WsReadEvent& even)
{
}
