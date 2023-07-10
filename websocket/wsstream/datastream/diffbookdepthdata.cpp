#include "diffbookdepthdata.h"

wxDEFINE_EVENT(mEVT_TR_DATA, wxCommandEvent);

DiffBookDepthData::DiffBookDepthData(DatGlobBinApi* data, size_t index, std::string symbol) : dataGlobal(data), index_(index), symbol_(symbol)
{
    loadFull = false;
    network = nullptr;
    lock = false;
    
}

DiffBookDepthData::~DiffBookDepthData()
{
    delete network;
}
void DiffBookDepthData::AddData(Bapi::Json data)
{
    if (dataOrd.asks.size() > 0 || dataOrd.bids.size() > 0)
    {
        dataOrd.bids.reserve(data["b"].size() + dataOrd.asks.size());
        dataOrd.asks.reserve(data["a"].size() + dataOrd.asks.size());
        if (data["b"].size() > 0)
        {
            for (size_t i = 0; i < data["b"].size(); i++)
            {
                DiffDepthEvent::Price bid;
                double price = BinJson::toDouble(data["b"][i][0]);
                bid.price = price;
                bid.quantity = BinJson::toDouble(data["b"][i][1]);

                auto link = std::find_if(dataOrd.bids.begin(), dataOrd.bids.end(), [&price](DiffDepthEvent::Price& a) { return a.price == price; });
                if (link != dataOrd.bids.end())
                {
                    if (bid.quantity == 0)
                    {
                        dataOrd.bids.erase(link, dataOrd.bids.end());
                    }
                    else
                    {
                        link->quantity = bid.quantity;
                    }
                }
                else
                {
                    dataOrd.bids.push_back(bid);
                }
            }
        }

        if (data["a"].size() > 0)
        {
            for (size_t i = 0; i < data["a"].size(); i++)
            {
                DiffDepthEvent::Price ask;
                double price = BinJson::toDouble(data["a"][i][0]);
                ask.price = price;
                ask.quantity = BinJson::toDouble(data["a"][i][1]);

                auto link = std::find_if(dataOrd.asks.begin(), dataOrd.asks.end(), [&price](DiffDepthEvent::Price& a) { return a.price == price; });
                if (link != dataOrd.asks.end())
                {
                    if (ask.quantity == 0)
                    {
                        dataOrd.asks.erase(link, dataOrd.asks.end());
                    }
                    else
                    {
                        link->quantity = ask.quantity;
                    }
                }
                else
                {
                    dataOrd.asks.push_back(ask);
                }
            }
        }
        dataOrd.time = BinJson::toULongLong(data["T"]);

        wxCommandEvent event(mEVT_TR_DATA);
        event.SetInt(index_);
        event.SetEventObject(this);
        // ProcessEvent(event);
        wxPostEvent(this, event);
    }
}

void DiffBookDepthData::LoadDiffDepth()
{
    if (!loadFull)
    {
        loadFull = true;
        network = new BinApiNetwork();
        network->Bind(BinApi_RETURN_DATA, &DiffBookDepthData::returnData, this);
        network->Bind(BinApi_RETURN_ERROR, &DiffBookDepthData::returnError, this);

        int limit = 1000;

        std::string url = "https://fapi.binance.com/fapi/v1/depth?symbol=" + symbol_;
        std::string idReq = "load";
        if (limit > 0)
        {
            url += "&limit=" + std::to_string(limit);
            idReq += "_" + std::to_string(limit);
        }
        else
        {
            idReq += "_0";
        }

        network->GetRequest(url, idReq);
    }
}

bool DiffBookDepthData::getFull()
{
    // if (dataOrd.bids.size() > 0 || dataOrd.asks.size() > 0)
    // {
    //     return true;
    // }

    return loadFull;
}

void DiffBookDepthData::returnData(BinApiNetworkEvent& event)
{
    // std::cout << event.getData() << std::endl;
    Bapi::Json data = BinJson::parse(event.getData());
    dataOrd.bids.reserve(data["bids"].size());
    dataOrd.bids.reserve(data["asks"].size());
    if (data["bids"].size() > 0)
    {
        for (size_t i = 0; i < data["bids"].size(); i++)
        {
            DiffDepthEvent::Price bid;
            bid.price = BinJson::toDouble(data["bids"][i][0]);
            bid.quantity = BinJson::toDouble(data["bids"][i][1]);
            dataOrd.bids.push_back(bid);
        }
    }

    if (data["asks"].size() > 0)
    {
        for (size_t i = 0; i < data["asks"].size(); i++)
        {
            DiffDepthEvent::Price ask;
            ask.price = BinJson::toDouble(data["asks"][i][0]);
            ask.quantity = BinJson::toDouble(data["asks"][i][1]);
            dataOrd.asks.push_back(ask);
        }
    }
    dataOrd.time = BinJson::toULongLong(data["T"]);

    network->Unbind(BinApi_RETURN_DATA, &DiffBookDepthData::returnData, this);
    network->Unbind(BinApi_RETURN_ERROR, &DiffBookDepthData::returnError, this);
    delete network;
    network = nullptr;
}

void DiffBookDepthData::returnError(BinApiNetworkEvent& event)
{
    loadFull = false;
}


