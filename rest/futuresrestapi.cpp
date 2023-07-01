#include "futuresrestapi.h"

wxDEFINE_EVENT(BAPI_RET_DATA, RestEventData);
wxDEFINE_EVENT(BAPI_RET_ERROR, RestEventData);

FuturesRestApi::FuturesRestApi(DatGlobBinApi* data) : dataGlobal(data)
{
    dataGlobal->fapiRet = [&, this](Bapi::Json jsData, RestEventData::TypeRestEvent typeRest) { this->fapiRet(jsData, typeRest); };
    dataGlobal->fapiRetErr = [&, this](Bapi::Json jsData, std::string text, RestEventData::TypeRestEvent typeRest) { this->fapiRetErr(jsData, text, typeRest); };
}

FuturesRestApi::~FuturesRestApi()
{
}

void FuturesRestApi::exchangeInfo()  // https://binance-docs.github.io/apidocs/futures/en/#exchange-information
{
    std::string url = "https://fapi.binance.com/fapi/v1/exchangeInfo";
    std::string idReq = "FAPI_" + std::to_string(static_cast<int>(RestEventData::TypeRestEvent::ExchangeInformation));
    dataGlobal->GetUrl(idReq, url);
}

void FuturesRestApi::fapiRet(Bapi::Json jsData, RestEventData::TypeRestEvent typeRest)
{
}

void FuturesRestApi::fapiRetErr(Bapi::Json jsData, std::string text, RestEventData::TypeRestEvent typeRest)
{
}
