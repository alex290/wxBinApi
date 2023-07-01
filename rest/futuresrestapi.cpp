#include "futuresrestapi.h"

// wxDEFINE_EVENT(BAPI_RET_DATA, bapiJsonEvent);
// wxDEFINE_EVENT(BAPI_RET_ERROR, bapiJsonEvent);

FuturesRestApi::FuturesRestApi(DatGlobBinApi* data) : dataGlobal(data)
{
    dataGlobal->fapiRet = [&, this](Bapi::Json jsData) { this->fapiRet(jsData); };
}

FuturesRestApi::~FuturesRestApi()
{
}

void FuturesRestApi::exchangeInfo()  // https://binance-docs.github.io/apidocs/futures/en/#exchange-information
{
    std::string url = "https://fapi.binance.com/fapi/v1/exchangeInfo";
}

void FuturesRestApi::fapiRet(Bapi::Json jsData)
{
}
