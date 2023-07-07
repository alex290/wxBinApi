#ifndef FUTURESRESTAPI_H
#define FUTURESRESTAPI_H

#include "../data/network/binapinetwork.h"
#include "../data/datglobbinapi.h"

wxDECLARE_EVENT(BAPI_RET_DATA, RestEventData);
wxDECLARE_EVENT(BAPI_RET_ERROR, RestEventData);

class FuturesRestApi : public wxEvtHandler
{
public:
    FuturesRestApi(DatGlobBinApi* data);
    ~FuturesRestApi();

    void exchangeInfo();  // https://binance-docs.github.io/apidocs/futures/en/#exchange-information

    /*
     * https://binance-docs.github.io/apidocs/futures/en/#order-book
     * Default 500; Valid limits:[5, 10, 20, 50, 100, 500, 1000]
     */
    void orderBook(std::string symbols, int limit = 0);  // Данные стакана (книга заявок)

    /*
     * https://binance-docs.github.io/apidocs/futures/en/#kline-candlestick-data
     * Свечные данные
     * interval 1m, 3m, 5m, 15m, 30m, 1h, 2h, 4h, 6h, 8h, 12h, 1d, 3d, 1w, 1M
     * limit; Default 500; max 1500..
     */
    void candlestickData(std::string symbols,  // Название инструмента
                         std::string inerval,  // Период
                         int limit = 0);       // количество свечей

private:
    DatGlobBinApi* dataGlobal;

    void fapiRet(Bapi::Json jsData, RestEventData::TypeRestEvent typeRest);
    void fapiRetErr(Bapi::Json jsData, std::string text, RestEventData::TypeRestEvent typeRest);
};

#endif