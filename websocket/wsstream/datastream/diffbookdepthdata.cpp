#include "diffbookdepthdata.h"

DiffBookDepthData::DiffBookDepthData(DatGlobBinApi* data, size_t index, std::string symbol) : dataGlobal(data), index_(index), symbol_(symbol)
{
}

DiffBookDepthData::~DiffBookDepthData()
{
}
void DiffBookDepthData::AddData(Bapi::Json data) {
    std::cout << symbol_ << "; " << index_ << std::endl;
}
