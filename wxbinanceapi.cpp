#include "wxbinanceapi.h"

WxBinanceApi::WxBinanceApi()
{
    fapi = new FuturesRestApi();
}

WxBinanceApi::~WxBinanceApi()
{
    delete fapi;
}