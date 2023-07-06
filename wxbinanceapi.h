#ifndef WXBINANCEAPI_H
#define WXBINANCEAPI_H

#include "rest/futuresrestapi.h"
#include "data/datglobbinapi.h"
#include "websocket/futureswebsocket.h"

class WxBinanceApi
{
public:
    WxBinanceApi();
    ~WxBinanceApi();

    FuturesRestApi* fapi;
    FuturesWebSocket* fWebsocket;

private:
    DatGlobBinApi* dataGlobal;
};

#endif