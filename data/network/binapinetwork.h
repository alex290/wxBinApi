#ifndef BINAPINETWORK_H
#define BINAPINETWORK_H

#define WIN32_LEAN_AND_MEAN
#include <curl/curl.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/webrequest.h>
#include <string>
#include "../events/binapinetworkevent.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <future>
#include <queue>

class BinApiNetwork
{
public:
    BinApiNetwork();
    ~BinApiNetwork();

private:

};

#endif