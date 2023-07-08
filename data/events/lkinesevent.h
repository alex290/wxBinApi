#ifndef LKINESEVENT_H
#define LKINESEVENT_H

#include <wx/event.h>
#include <string>

class LKInesEvent : public wxEvent
{
public:
    struct Data
    {
        time_t startTime;      // Kline start time
        time_t closeTime;      // Kline close time
        double openPrice;      // Open price
        double closePrice;     // Close price
        double highPrice;      // High price
        double lowPrice;       // Low price
        double volume;         // Base asset volume
        double volumeQuote;    // Quote asset volume
        double deltaBuy;       // Taker buy base asset volume
        double deltaBuyQuote;  // Taker buy quote asset volume
    };

    LKInesEvent(wxEventType eventType, std::string interval, std::string symbol, size_t index, LKInesEvent::Data data) : wxEvent(wxID_ANY, eventType), interval_(interval), symbol_(symbol), index_(index), data_(data)
    {
    }

    std::string getInterval()
    {
        return interval_;
    };
    std::string getSymbol()
    {
        return symbol_;
    };
    size_t getIndex()
    {
        return index_;
    };
    LKInesEvent::Data getData()
    {
        return data_;
    };

    // implement the base class pure virtual
    virtual wxEvent* Clone() const
    {
        return new LKInesEvent(*this);
    }

private:
    std::string symbol_;
    std::string interval_;
    size_t index_;
    LKInesEvent::Data data_;
};

#endif