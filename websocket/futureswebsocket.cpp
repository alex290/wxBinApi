#include "futureswebsocket.h"

FuturesWebSocket::FuturesWebSocket(DatGlobBinApi* data) : dataGlobal(data)
{
}

FuturesWebSocket::~FuturesWebSocket()
{
}

// https://binance-docs.github.io/apidocs/futures/en/#kline-candlestick-streams
void FuturesWebSocket::klines(std::vector<std::string> symbols)  // Запуск свечных данных Websocket
{
}

// https://binance-docs.github.io/apidocs/futures/en/#diff-book-depth-streams
void FuturesWebSocket::diffDepth(std::vector<std::string> symbols)  // Запуск данных стакана (книга заявок)
{
}
