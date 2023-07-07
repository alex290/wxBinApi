#include "futureswebsocket.h"

FuturesWebSocket::FuturesWebSocket(DatGlobBinApi* data) : dataGlobal(data)
{
}

FuturesWebSocket::~FuturesWebSocket()
{
}

// https://binance-docs.github.io/apidocs/futures/en/#kline-candlestick-streams
void FuturesWebSocket::klines(std::vector<std::string> symbols, std::string inerval)  // Запуск свечных данных Websocket
{
}

// https://binance-docs.github.io/apidocs/futures/en/#diff-book-depth-streams
void FuturesWebSocket::diffDepth(std::vector<std::string> symbols,  int speed)  // Запуск данных стакана (книга заявок)
{
}
