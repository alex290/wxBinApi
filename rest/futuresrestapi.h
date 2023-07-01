#ifndef FUTURESRESTAPI_H
#define FUTURESRESTAPI_H

#include "../data/network/binapinetwork.h"
#include "../data/events/wxjsonevent.h"

wxDECLARE_EVENT(BAPI_RET_DATA, wxJsonEvent);
wxDECLARE_EVENT(BAPI_RET_ERROR, wxJsonEvent);

class FuturesRestApi : public wxEvtHandler
{
public:
    FuturesRestApi();
    ~FuturesRestApi();

    void exchangeInfo(); // https://binance-docs.github.io/apidocs/futures/en/#exchange-information

private:

};

#endif