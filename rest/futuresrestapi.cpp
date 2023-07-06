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

// https://binance-docs.github.io/apidocs/futures/en/#order-book
void FuturesRestApi::orderBook(std::string symbols)  // Данные стакана (книга заявок)
{
}

// https://binance-docs.github.io/apidocs/futures/en/#kline-candlestick-data
void FuturesRestApi::candlestickData(std::string symbols)  // Свечные данные
{
}

void FuturesRestApi::fapiRet(Bapi::Json jsData, RestEventData::TypeRestEvent typeRest)
{
    // std::cout << typeRest << std::endl;
    // std::cout << jsData.dump() << std::endl;
    RestEventData event(BAPI_RET_DATA, "", jsData, typeRest);
    event.SetEventObject(this);
    // ProcessEvent(event);
    wxPostEvent(this, event);
}

void FuturesRestApi::fapiRetErr(Bapi::Json jsData, std::string text, RestEventData::TypeRestEvent typeRest)
{
    RestEventData event(BAPI_RET_ERROR, text, jsData, typeRest);
    event.SetEventObject(this);
    // ProcessEvent(event);
    wxPostEvent(this, event);
}
