#ifndef FUTURESWEBSOCKET_H
#define FUTURESWEBSOCKET_H

#include "../data/datglobbinapi.h"
#include "wsstream/lkineswebsocket.h"
#include "../data/events/lkinesevent.h"
#include "../data/events/diffdepthevent.h"
#include "wsstream/diffbookdepthwebsocket.h"

wxDECLARE_EVENT(WSBAPI_KLINE_DATA, LKInesEvent);
wxDECLARE_EVENT(WSBAPI_DIFF_DEPTH_DATA, DiffDepthEvent);

class FuturesWebSocket : public wxEvtHandler
{
public:
    FuturesWebSocket(DatGlobBinApi* data);
    ~FuturesWebSocket();

    /*
     * Запуск свечных данных Websocket
     * https://binance-docs.github.io/apidocs/futures/en/#kline-candlestick-streams
     * interval 1m, 3m, 5m, 15m, 30m, 1h, 2h, 4h, 6h, 8h, 12h, 1d, 3d, 1w, 1M
     */
    void klines(std::vector<std::string> symbols, std::string inerval);

    /*
     * Запуск данных стакана (книга заявок)
     * https://binance-docs.github.io/apidocs/futures/en/#diff-book-depth-streams
     * Update Speed: 250ms, 500ms, 100ms
     */
    void diffDepth(std::vector<std::string> symbols, int speed = 0);

private:
    DatGlobBinApi* dataGlobal;
    std::queue<std::future<void>> q;
    LKInesWebSocket *kLineWs;
    DiffBookDepthWebSocket *diffDepthWs;

    std::vector<std::string> symbols_;
    std::string inerval_;

    void StreamDataKline(std::string sym);
    void StreamDataDiffDept(std::string symbol, size_t index, DiffDepthEvent::Data data);

};

#endif