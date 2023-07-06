#ifndef RESTEVENTDATA_H
#define RESTEVENTDATA_H

#include <wx/event.h>
#include <string>
#include "../dopformat/binjson.h"

class RestEventData : public wxEvent
{
public:
    enum TypeRestEvent
    {
        NONE,
        PING,
        CheckServerTime,
        ExchangeInformation,
        CandlestickData,
        OrderBook
    };
    RestEventData(wxEventType eventType, std::string text, Bapi::Json data, RestEventData::TypeRestEvent typeRest) : wxEvent(wxID_ANY, eventType), text_(text), data_(data), typeRest_(typeRest)
    {
    }
    std::string getText()
    {
        return text_;
    };
    Bapi::Json getData()
    {
        return data_;
    };
    RestEventData::TypeRestEvent GetTypeREST()
    {
        return typeRest_;
    }

    // implement the base class pure virtual
    virtual wxEvent* Clone() const
    {
        return new RestEventData(*this);
    }

private:
    Bapi::Json data_;
    std::string text_;
    RestEventData::TypeRestEvent typeRest_;
};

#endif