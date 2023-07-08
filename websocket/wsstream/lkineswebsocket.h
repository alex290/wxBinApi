#ifndef LKINESWEBSOCKET_H
#define LKINESWEBSOCKET_H

#include "../ws/loadstreamdata.h"
#include "../../data/datglobbinapi.h"

class LKInesWebSocket
{
public:
    LKInesWebSocket(DatGlobBinApi* data);
    ~LKInesWebSocket();

    std::function<void(std::string)> streamData;

    void Start(std::vector<std::string> &symbols, std::string &inerval);

private:
    DatGlobBinApi* dataGlobal;
    LoadStreamData* ws;

    bool startLoad;

    void ReadData(std::string data);
    void Error(WsReadEvent& even);
    void Close(WsReadEvent& even);
    void Connect(WsReadEvent& even);

};

#endif