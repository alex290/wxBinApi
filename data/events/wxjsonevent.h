#ifndef WXJSONEVENT_H
#define WXJSONEVENT_H

#include <wx/event.h>
#include <string>
#include "../dopformat/binjson.h"

class wxJsonEvent : public wxEvent
{
public:
    wxJsonEvent(wxEventType eventType, std::string text, Json data) : wxEvent(wxID_ANY, eventType), text_(text), data_(data)
    {
    }
    std::string getText()
    {
        return text_;
    };
    Json getData()
    {
        return data_;
    };

    // implement the base class pure virtual
    virtual wxEvent* Clone() const
    {
        return new wxJsonEvent(*this);
    }

private:
    Json data_;
    std::string text_;
};

#endif