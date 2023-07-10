#include "diffbookdepthwebsocket.h"

DiffBookDepthWebSocket::DiffBookDepthWebSocket(DatGlobBinApi* data) : dataGlobal(data)
{
    ws = new LoadStreamData(15);
    startLoad = false;
    ws->Bind(WSBAPI_RET_ERROR, &DiffBookDepthWebSocket::Error, this);
    ws->Bind(WSBAPI_RET_CLOSE, &DiffBookDepthWebSocket::Close, this);
    ws->Bind(WSBAPI_RET_CONNECT, &DiffBookDepthWebSocket::Connect, this);
    ws->streamData = [this](std::string data) { ReadData(data); };
}

DiffBookDepthWebSocket::~DiffBookDepthWebSocket()
{
    if (startLoad)
        ws->closeSocket();
    removeData();
    delete ws;
}

void DiffBookDepthWebSocket::Start(std::vector<std::string>& symbols, int speed)
{
    symbols_ = symbols;
    removeData();
    diffData.resize(symbols_.size());
    std::string baseUrlFut = "/stream?streams=";
    for (size_t i = 0; i < symbols.size(); i++)
    {
        diffData[i] = new DiffBookDepthData(dataGlobal, i, symbols[i]);
        if (i > 0)
        {
            baseUrlFut = baseUrlFut + "/";
        }
        baseUrlFut = baseUrlFut + FormatDop::str_tolower(symbols[i]) + "@depth";
        if (speed > 0)
        {
            baseUrlFut = baseUrlFut + "@" + std::to_string(speed) + "ms";
        }
    }
    std::cout << "Start DiffBook - symbols: " << baseUrlFut << std::endl;
    ws->startSocket("fstream.binance.com", baseUrlFut);
    startLoad = true;
}

void DiffBookDepthWebSocket::ReadData(std::string data)
{
    // std::cout << data << std::endl;
    q.push(std::async(std::launch::async, [data, this] {
        Bapi::Json dataJsAll = BinJson::parse(data);
        Bapi::Json dataJs = dataJsAll["data"];
        std::string symb = BinJson::toString(dataJs["s"]);

        size_t index = 0;
        for (size_t i = 0; i < symbols_.size(); i++)
        {
            if (symbols_[i] == symb && diffData.size() > i)
            {
                diffData[i]->AddData(dataJs);
                break;
            }
        }
    }));
}

void DiffBookDepthWebSocket::Error(WsReadEvent& even)
{
}

void DiffBookDepthWebSocket::Close(WsReadEvent& even)
{
    std::cout << "Close" << std::endl;
}

void DiffBookDepthWebSocket::Connect(WsReadEvent& even)
{
}
void DiffBookDepthWebSocket::removeData()
{
    if (diffData.size() > 0)
    {
        for (size_t i = 0; i < diffData.size(); i++)
        {
            delete diffData[i];
        }
        diffData.clear();
    }
}
