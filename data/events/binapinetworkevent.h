#ifndef BINAPINETWORKEVENT_H
#define BINAPINETWORKEVENT_H

#include <wx/event.h>
#include <string>

class BinApiNetworkEvent : public wxEvent
{
public:
    BinApiNetworkEvent(wxEventType eventType, std::string idRequest, std::string data) : wxEvent(wxID_ANY, eventType), idRequest_(idRequest), data_(data)
    {
    }
    std::string getIdRequest()
    {
        return idRequest_;
    };
    std::string getData()
    {
        return data_;
    };

    // implement the base class pure virtual
    virtual wxEvent* Clone() const
    {
        return new BinApiNetworkEvent(*this);
    }

private:
    std::string idRequest_;
    std::string data_;
};

#endif