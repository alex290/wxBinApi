#ifndef BAPIMARKETDATA_H
#define BAPIMARKETDATA_H

#include <wx/wx.h>

class BapiMarketData
{
public:
    struct CandlestickDataMarket  // Kline/candlestick bars for a symbol. Klines are uniquely identified by their open time
    {
        time_t openTime;             // Open time
        double iOpen;                // Open
        double iHigh;                // High
        double iLow;                 // Low
        double iClose;               // Close
        double iVolume;              // Volume
        time_t closeTime;            // Close time
        double quoteAssetVolume;     // Quote asset volume
        size_t numberTrades;         // Number of trades
        double buyAssetVolume;       // Taker buy base asset volume
        double buyQuoteAssetVolume;  // Taker buy quote asset volume
    };
    BapiMarketData();
    ~BapiMarketData();

private:
};

#endif