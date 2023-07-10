#ifndef DIFFBOOKDEPTHWEBSOCKET_H
#define DIFFBOOKDEPTHWEBSOCKET_H

#include "../ws/loadstreamdata.h"
#include "../../data/datglobbinapi.h"
#include "datastream/diffbookdepthdata.h"

class DiffBookDepthWebSocket
{
public:
    DiffBookDepthWebSocket(DatGlobBinApi* data);
    ~DiffBookDepthWebSocket();
    std::function<void (std::string, size_t, DiffDepthEvent::Data)> streamData;

    void Start(std::vector<std::string> &symbols, int speed);

private:
    DatGlobBinApi* dataGlobal;
    LoadStreamData* ws;

    std::vector<std::string> symbols_;

    std::vector<DiffBookDepthData *> diffData;

    bool startLoad;

    std::queue<std::future<void>> q;

    void ReadData(std::string data);
    void Error(WsReadEvent& even);
    void Close(WsReadEvent& even);
    void Connect(WsReadEvent& even);
    void removeData();

    void AddNewData(wxCommandEvent& event);
};

#endif