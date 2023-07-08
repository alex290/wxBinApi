#include "futureswebsocket.h"

wxDEFINE_EVENT(WSBAPI_KLINE_DATA, LKInesEvent);

FuturesWebSocket::FuturesWebSocket(DatGlobBinApi* data) : dataGlobal(data)
{
    kLineWs = nullptr;
}

FuturesWebSocket::~FuturesWebSocket()
{
    delete kLineWs;
}

// https://binance-docs.github.io/apidocs/futures/en/#kline-candlestick-streams
void FuturesWebSocket::klines(std::vector<std::string> symbols, std::string inerval)  // Запуск свечных данных Websocket
{
    delete kLineWs;
    kLineWs = new LKInesWebSocket(dataGlobal);
    kLineWs->streamData = [this](std::string data) { StreamDataKline(data); };
    kLineWs->Start(symbols, inerval);
}

// https://binance-docs.github.io/apidocs/futures/en/#diff-book-depth-streams
void FuturesWebSocket::diffDepth(std::vector<std::string> symbols, int speed)  // Запуск данных стакана (книга заявок)
{
    q.push(std::async(std::launch::async, [symbols, speed, this] { diffDepthAsync(symbols, speed); }));
}

void FuturesWebSocket::diffDepthAsync(std::vector<std::string> symbols, int speed)
{
}

void FuturesWebSocket::StreamDataKline(std::string data)
{
    Bapi::Json dataJs = BinJson::parse(data);
    std::cout << dataJs.dump() << std::endl;
}
