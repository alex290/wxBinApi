#ifndef FUTURESRESTAPI_H
#define FUTURESRESTAPI_H

#include "../data/network/binapinetwork.h"
// #include "../data/events/bapijsonevent.h"
#include "../data/datglobbinapi.h"

// wxDECLARE_EVENT(BAPI_RET_DATA, bapiJsonEvent);
// wxDECLARE_EVENT(BAPI_RET_ERROR, bapiJsonEvent);

class FuturesRestApi : public wxEvtHandler
{
public:
    FuturesRestApi(DatGlobBinApi* data);
    ~FuturesRestApi();

    void exchangeInfo();  // https://binance-docs.github.io/apidocs/futures/en/#exchange-information

private:
    DatGlobBinApi* dataGlobal;

    void fapiRet(Bapi::Json jsData);
};

#endif