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

wxDECLARE_EVENT(BinApi_RETURN_DATA, BinApiNetworkEvent);
wxDECLARE_EVENT(BinApi_RETURN_ERROR, BinApiNetworkEvent);

class BinApiNetwork : public wxEvtHandler
{
public:
    struct NetPostData
    {
        wxString nameField;
        wxString dataField;
    };

    enum TypeProxy
    {
        NONE,
        HTTP,
        HTTPS,
        SOCKS4,
        SOCKS5
    };

    BinApiNetwork();
    ~BinApiNetwork();

    void SetTimeout(long timeout);  // Установка таймоута соединения

    static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp);

    void SetProxy(std::string addres, BinApiNetwork::TypeProxy type, std::string proxyUser = "", std::string proxyPass = "");

    void GetRequest(std::string url, std::string idRequest, std::vector<std::string> header);  // Отправка GET запроса
    void GetRequest(std::string url, std::string idRequest);                                   // Отправка GET запроса

    void PostRequest(std::string url, std::string idRequest, std::vector<NetPostData> postData, std::vector<std::string> header);  // Отправка POST запроса
    void PostRequest(std::string url, std::string idRequest, std::vector<NetPostData> postData);                                   // Отправка POST запроса

    void PutRequest(std::string url, std::string idRequest, std::vector<NetPostData> putData, std::vector<std::string> header);  // Отправка PUT запроса
    void PutRequest(std::string url, std::string idRequest, std::vector<NetPostData> putData);                                   // Отправка PUT запроса

    void DeleteRequest(std::string url, std::string idRequest, std::vector<NetPostData> delData, std::vector<std::string> header);  // Отправка DELETE запроса
    void DeleteRequest(std::string url, std::string idRequest, std::vector<NetPostData> delData);                                   // Отправка DELETE запроса

    std::string idRequest = "Request";

private:
    enum TypeRequest
    {
        GET_R,
        POST_R,
        PUT_R,
        DELETE_R
    };

    BinApiNetwork::TypeProxy type_;
    std::string proxyAddres;
    std::string proxyUser;
    std::string proxyPass;

    long timeout_ = 5L;

    std::queue<std::future<void>> q;

    std::string getPostField(std::vector<BinApiNetwork::NetPostData> data);

    void startReqest(CURL* curl, std::string url, std::string idRequest, std::string postfields, BinApiNetwork::TypeRequest type, std::vector<std::string> header);
    void retData(std::string data, std::string idRequest);
    void retError(std::string error, std::string idRequest);
};

#endif