#ifndef FUTURESWEBSOCKET_H
#define FUTURESWEBSOCKET_H

#include "../data/datglobbinapi.h"

class FuturesWebSocket : public wxEvtHandler
{
public:
    FuturesWebSocket(DatGlobBinApi* data);
    ~FuturesWebSocket();

    // https://binance-docs.github.io/apidocs/futures/en/#kline-candlestick-streams
    void klines(std::vector<std::string> symbols);     // Запуск свечных данных Websocket

    // https://binance-docs.github.io/apidocs/futures/en/#diff-book-depth-streams
    void diffDepth(std::vector<std::string> symbols);  // Запуск данных стакана (книга заявок)

private:
    DatGlobBinApi* dataGlobal;
};

#endif