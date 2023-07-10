#ifndef DIFFBOOKDEPTHDATA_H
#define DIFFBOOKDEPTHDATA_H

#include "../../ws/loadstreamdata.h"
#include "../../../data/datglobbinapi.h"
#include "../../../data/events/diffdepthevent.h"
#include <thread>

wxDECLARE_EVENT(mEVT_TR_DATA, wxCommandEvent);

class DiffBookDepthData : public wxEvtHandler
{
public:
    DiffBookDepthData(DatGlobBinApi* data, size_t index, std::string symbol);
    ~DiffBookDepthData();

    size_t getIndex();

    void AddData(Bapi::Json data);  // Добавляем текущие данные
    void LoadDiffDepth();           // Запрсо на загрузку стакана
    bool getFull();                 // Проверка заполнен ли стакан

    DiffDepthEvent::Data dataOrd;  // Стакан
    std::string symbol_;

private:
    DatGlobBinApi* dataGlobal;
    size_t index_;
    

    DiffDepthEvent::Data bufferData[4];  // Кольцевой буфер
    bool loadFull;

    int readIndex;   // Индекс чтения буфера
    int writeIndex;  // Индекс записи буфера

    bool lock;  // Активная запись

    BinApiNetwork* network;
    void returnData(BinApiNetworkEvent& event);
    void returnError(BinApiNetworkEvent& event);
};

#endif