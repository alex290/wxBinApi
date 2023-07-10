#ifndef DIFFBOOKDEPTHDATA_H
#define DIFFBOOKDEPTHDATA_H

#include "../../ws/loadstreamdata.h"
#include "../../../data/datglobbinapi.h"

class DiffBookDepthData
{
public:
    DiffBookDepthData(DatGlobBinApi* data, size_t index, std::string symbol);
    ~DiffBookDepthData();

    size_t getIndex();

    void AddData(Bapi::Json data);

private:
    DatGlobBinApi* dataGlobal;
    size_t index_;
    std::string symbol_;
};

#endif