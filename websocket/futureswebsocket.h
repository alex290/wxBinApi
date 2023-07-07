#ifndef FUTURESWEBSOCKET_H
#define FUTURESWEBSOCKET_H

#include "../data/datglobbinapi.h"

class FuturesWebSocket : public wxEvtHandler
{
public:
    FuturesWebSocket(DatGlobBinApi* data);
    ~FuturesWebSocket();

    // https://binance-docs.github.io/apidocs/futures/en/#kline-candlestick-streams
    // interval 1m, 3m, 5m, 15m, 30m, 1h, 2h, 4h, 6h, 8h, 12h, 1d, 3d, 1w, 1M
    void klines(std::vector<std::string> symbols, std::string inerval);     // Запуск свечных данных Websocket

    // https://binance-docs.github.io/apidocs/futures/en/#diff-book-depth-streams
    // Update Speed: 250ms, 500ms, 100ms
    void diffDepth(std::vector<std::string> symbols, int speed = 0);  // Запуск данных стакана (книга заявок)

private:
    DatGlobBinApi* dataGlobal;
};

#endif