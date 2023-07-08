#ifndef DIFFDEPTHEVENT_H
#define DIFFDEPTHEVENT_H

#include <wx/event.h>
#include <string>
#include <vector>
#include <algorithm>

class DiffDepthEvent : public wxEvent
{
public:
    struct Price
    {
        double price;     // Price level
        double quantity;  // Quantity
    };
    struct Data
    {
        time_t time;  // Event time
        std::vector<DiffDepthEvent::Price> bids; // Bids levels
        std::vector<DiffDepthEvent::Price> asks; // Asks levels
    };

    DiffDepthEvent(wxEventType eventType, std::string symbol, size_t index, DiffDepthEvent::Data data) : wxEvent(wxID_ANY, eventType), symbol_(symbol), index_(index), data_(data)
    {
    }

    std::string getSymbol()
    {
        return symbol_;
    };
    size_t getIndex()
    {
        return index_;
    };
    DiffDepthEvent::Data getData()
    {
        return data_;
    };

    // implement the base class pure virtual
    virtual wxEvent* Clone() const
    {
        return new DiffDepthEvent(*this);
    }

private:
    std::string symbol_;
    size_t index_;
    DiffDepthEvent::Data data_;
};

#endif