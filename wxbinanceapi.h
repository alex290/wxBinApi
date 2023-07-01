#ifndef WXBINANCEAPI_H
#define WXBINANCEAPI_H

#include "rest/futuresrestapi.h"
#include "data/datglobbinapi.h"

class WxBinanceApi
{
public:
    WxBinanceApi();
    ~WxBinanceApi();

    FuturesRestApi* fapi;

private:
    DatGlobBinApi* dataGlobal;
};

#endif