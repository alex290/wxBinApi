#ifndef LKINESWEBSOCKET_H
#define LKINESWEBSOCKET_H

#include "../ws/loadstreamdata.h"
#include "../../data/datglobbinapi.h"

class LKInesWebSocket
{
public:
    LKInesWebSocket(DatGlobBinApi* data);
    ~LKInesWebSocket();

    void Start(std::vector<std::string> &symbols, std::string &inerval);

private:
    DatGlobBinApi* dataGlobal;
    LoadStreamData* ws;

    bool startLoad;
    std::vector<std::string> symbols_;
    std::string inerval_;

    void ReadData(WsReadEvent& even);
    void Error(WsReadEvent& even);
    void Close(WsReadEvent& even);
    void Connect(WsReadEvent& even);
};

#endif