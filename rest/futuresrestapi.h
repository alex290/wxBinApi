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

    // https://binance-docs.github.io/apidocs/futures/en/#order-book
    void orderBook(std::string symbols);  // Данные стакана (книга заявок)

    // https://binance-docs.github.io/apidocs/futures/en/#kline-candlestick-data
    void candlestickData(std::string symbols); // Свечные данные

private:
    DatGlobBinApi* dataGlobal;

    void fapiRet(Bapi::Json jsData, RestEventData::TypeRestEvent typeRest);
    void fapiRetErr(Bapi::Json jsData, std::string text, RestEventData::TypeRestEvent typeRest);
};

#endif