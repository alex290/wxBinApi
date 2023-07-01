#include "wxbinanceapi.h"

WxBinanceApi::WxBinanceApi()
{
    dataGlobal = new DatGlobBinApi;
    fapi = new FuturesRestApi(dataGlobal);
}

WxBinanceApi::~WxBinanceApi()
{
    delete fapi;
    delete dataGlobal;
}