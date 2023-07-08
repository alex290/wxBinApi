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
    symbols_ = symbols;
    inerval_ = inerval;
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
    Bapi::Json dataJsAll = BinJson::parse(data);
    Bapi::Json dataJs = dataJsAll["data"];
    std::string interval = BinJson::toString(dataJs["k"]["i"]);
    std::string symb = BinJson::toString(dataJs["s"]);
    // std::cout << dataJs.dump() << std::endl;
    size_t index = 0;
    for (size_t i = 0; i < symbols_.size(); i++)
    {
        if (symbols_[i] == symb)
        {
            index = i;
        }
    }

    LKInesEvent::Data dat;
    dat.startTime = BinJson::toULongLong(dataJs["k"]["t"]);  // Kline start time
    dat.closeTime = BinJson::toULongLong(dataJs["k"]["T"]);  // Kline close time

    dat.openPrice = BinJson::toDouble(dataJs["k"]["o"]);   // Open price
    dat.closePrice = BinJson::toDouble(dataJs["k"]["c"]);  // Close price
    dat.highPrice = BinJson::toDouble(dataJs["k"]["h"]);   // High price
    dat.lowPrice = BinJson::toDouble(dataJs["k"]["l"]);    // Low price

    dat.volume = BinJson::toDouble(dataJs["k"]["v"]);         // Base asset volume
    dat.volumeQuote = BinJson::toDouble(dataJs["k"]["q"]);    // Quote asset volume
    dat.deltaBuy = BinJson::toDouble(dataJs["k"]["V"]);       // Taker buy base asset volume
    dat.deltaBuyQuote = BinJson::toDouble(dataJs["k"]["Q"]);  // Taker buy quote asset volume

    LKInesEvent event(WSBAPI_KLINE_DATA, interval, symb, index, dat);
    event.SetEventObject(this);
    ProcessEvent(event);
    // wxPostEvent(this, event);
}
