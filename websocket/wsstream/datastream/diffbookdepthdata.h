#ifndef DIFFBOOKDEPTHDATA_H
#define DIFFBOOKDEPTHDATA_H

#include "../../ws/loadstreamdata.h"
#include "../../../data/datglobbinapi.h"

class DiffBookDepthData
{
public:
    DiffBookDepthData(DatGlobBinApi* data, size_t index);
    ~DiffBookDepthData();

    size_t getIndex();

private:
    DatGlobBinApi* dataGlobal;
    size_t index_;
};

#endif