#ifndef WSREADEVENT_H
#define WSREADEVENT_H

#include <wx/event.h>
#include <string>

class WsReadEvent : public wxEvent
{
public:
    WsReadEvent(wxEventType eventType, std::string idRequest, std::string data) : wxEvent(wxID_ANY, eventType), idRequest_(idRequest), data_(data)
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
        return new WsReadEvent(*this);
    }

private:
    std::string idRequest_;
    std::string data_;
};

#endif