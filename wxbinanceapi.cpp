#include "wxbinanceapi.h"

WxBinanceApi::WxBinanceApi()
{
    dataGlobal = new DatGlobBinApi;
    fapi = new FuturesRestApi(dataGlobal);
    fWebsocket = new FuturesWebSocket(dataGlobal);
}

WxBinanceApi::~WxBinanceApi()
{
    delete fWebsocket;
    delete fapi;
    delete dataGlobal;
}