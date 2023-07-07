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
void FuturesRestApi::orderBook(std::string symbols, int limit)  // Данные стакана (книга заявок)
{
    std::string url = "https://fapi.binance.com/fapi/v1/depth?symbol=" + symbols;
    std::string idReq = "FAPI_" + std::to_string(static_cast<int>(RestEventData::TypeRestEvent::OrderBook)) + "_" + symbols;
    if (limit > 0)
    {
        url += "&limit=" + std::to_string(limit);
        idReq += "_" + std::to_string(limit);
    }
    else
    {
        idReq += "_0";
    }

    dataGlobal->GetUrl(idReq, url);
}

// https://binance-docs.github.io/apidocs/futures/en/#kline-candlestick-data
void FuturesRestApi::candlestickData(std::string symbols,  // Название инструмента
                                     std::string inerval,  // Период
                                     int limit)            // количество свечей
{
    std::string url = "https://fapi.binance.com/fapi/v1/klines?symbol=" + symbols + "&interval=" + inerval;
    std::string idReq = "FAPI_" + std::to_string(static_cast<int>(RestEventData::TypeRestEvent::CandlestickData)) + "_" + symbols + "_" + inerval;

    if (limit > 0)
    {
        url += "&limit=" + std::to_string(limit);
        idReq += "_" + std::to_string(limit);
    }
    else
    {
        idReq += "_0";
    }

    dataGlobal->GetUrl(idReq, url);
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
