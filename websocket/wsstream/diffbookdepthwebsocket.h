#ifndef DIFFBOOKDEPTHWEBSOCKET_H
#define DIFFBOOKDEPTHWEBSOCKET_H

#include "../ws/loadstreamdata.h"
#include "../../data/datglobbinapi.h"

class DiffBookDepthWebSocket
{
public:
    DiffBookDepthWebSocket(DatGlobBinApi* data);
    ~DiffBookDepthWebSocket();
    std::function<void(std::string)> streamData;

    void Start(std::vector<std::string> &symbols, int speed);

private:
    DatGlobBinApi* dataGlobal;
    LoadStreamData* ws;
};

#endif