#include "binapinetwork.h"

wxDEFINE_EVENT(BinApi_RETURN_DATA, BinApiNetworkEvent);
wxDEFINE_EVENT(BinApi_RETURN_ERROR, BinApiNetworkEvent);

BinApiNetwork::BinApiNetwork()
{
    SetProxy("", BinApiNetwork::NONE);
}

BinApiNetwork::~BinApiNetwork()
{
}

void BinApiNetwork::SetTimeout(long timeout)
{
    timeout_ = timeout;
}

size_t BinApiNetwork::WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void BinApiNetwork::SetProxy(std::string addres, BinApiNetwork::TypeProxy type, std::string proxyUser, std::string proxyPass)
{
    type_ = type;
    proxyAddres = addres;
    this->proxyUser = proxyUser;
    this->proxyPass = proxyPass;
}

void BinApiNetwork::GetRequest(std::string url, std::string idRequest, std::vector<std::string> header)
{
    this->idRequest = idRequest;
    q.push(std::async(std::launch::async, [url, idRequest, header, this] {
        CURL* curl = curl_easy_init();

        if (curl)
            startReqest(curl, url, idRequest, "", BinApiNetwork::TypeRequest::GET_R, header);
    }));
}

void BinApiNetwork::GetRequest(std::string url, std::string idRequest)
{
    std::vector<std::string> header;
    GetRequest(url, idRequest, header);
}

void BinApiNetwork::PostRequest(std::string url, std::string idRequest, std::vector<NetPostData> postData, std::vector<std::string> header)
{
    this->idRequest = idRequest;
    q.push(std::async(std::launch::async, [url, idRequest, postData, header, this] {
        CURL* curl = curl_easy_init();

        if (curl)
            startReqest(curl, url, idRequest, getPostField(postData), BinApiNetwork::TypeRequest::POST_R, header);
    }));
}

void BinApiNetwork::PostRequest(std::string url, std::string idRequest, std::vector<NetPostData> postData)
{
    std::vector<std::string> header;
    PostRequest(url, idRequest, postData, header);
}

void BinApiNetwork::PutRequest(std::string url, std::string idRequest, std::vector<NetPostData> putData, std::vector<std::string> header)
{
    this->idRequest = idRequest;
    q.push(std::async(std::launch::async, [url, idRequest, putData, header, this] {
        CURL* curl = curl_easy_init();

        if (curl)
            startReqest(curl, url, idRequest, getPostField(putData), BinApiNetwork::TypeRequest::PUT_R, header);
    }));
}

void BinApiNetwork::PutRequest(std::string url, std::string idRequest, std::vector<NetPostData> putData)
{
    std::vector<std::string> header;
    PutRequest(url, idRequest, putData, header);
}

void BinApiNetwork::DeleteRequest(std::string url, std::string idRequest, std::vector<NetPostData> delData, std::vector<std::string> header)
{
    this->idRequest = idRequest;
    q.push(std::async(std::launch::async, [url, idRequest, delData, header, this] {
        CURL* curl = curl_easy_init();

        if (curl)
            startReqest(curl, url, idRequest, getPostField(delData), BinApiNetwork::TypeRequest::DELETE_R, header);
    }));
}

void BinApiNetwork::DeleteRequest(std::string url, std::string idRequest, std::vector<NetPostData> delData)
{
    std::vector<std::string> header;
    DeleteRequest(url, idRequest, delData, header);
}

std::string BinApiNetwork::getPostField(std::vector<BinApiNetwork::NetPostData> data)
{
    std::string postfields = "";
    if (!data.empty())
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (i > 0)
                postfields = postfields + "&";
            postfields = postfields + data[i].nameField.ToStdString() + "=" + data[i].dataField.ToStdString();
        }
    }

    return postfields;
}

void BinApiNetwork::startReqest(CURL* curl, std::string url, std::string idRequest, std::string postfields, BinApiNetwork::TypeRequest type, std::vector<std::string> header)
{
    std::string str_response;
    CURLcode res;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);  // Включаем HTTPS

    // POST Поля
    if (postfields.size() > 1 || type == TypeRequest::POST_R)
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields.c_str());

    if (type_ == BinApiNetwork::HTTP)
    {
        curl_easy_setopt(curl, CURLOPT_PROXY, proxyAddres.c_str());
        curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
    }
    else if (type_ == BinApiNetwork::HTTPS)
    {
        curl_easy_setopt(curl, CURLOPT_PROXY, proxyAddres.c_str());
        curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTPS);
    }
    else if (type_ == BinApiNetwork::SOCKS4)
    {
        curl_easy_setopt(curl, CURLOPT_PROXY, proxyAddres.c_str());
        curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
    }
    else if (type_ == BinApiNetwork::SOCKS5)
    {
        curl_easy_setopt(curl, CURLOPT_PROXY, proxyAddres.c_str());
        curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
    }

    if (type_ != BinApiNetwork::NONE && proxyUser.size() > 2 && proxyPass.size() > 0)
    {
        std::string userpwd = proxyUser + ":" + proxyPass;
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, userpwd.c_str());
    }

    if (type == TypeRequest::PUT_R)
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    else if (type == TypeRequest::DELETE_R)
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    /* отправьте все данные в эту функцию  */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    /* завершено в течение 20 секунд */
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout_);

    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str_response);

    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    struct curl_slist* headers = NULL;
    if (!header.empty())
    {
        for (std::string itemHead : header)
        {
            // std::cout << itemHead << std::endl;
            headers = curl_slist_append(headers, itemHead.c_str());
        }

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK)
    {
        retError(curl_easy_strerror(res), idRequest);
    }
    else
    {
        retData(str_response, idRequest);
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
}

void BinApiNetwork::retData(std::string data, std::string idRequest)
{
    BinApiNetworkEvent event(BinApi_RETURN_DATA, idRequest, data);
    event.SetEventObject(this);
    // ProcessEvent(event);
    wxPostEvent(this, event);
}

void BinApiNetwork::retError(std::string error, std::string idRequest)
{
    BinApiNetworkEvent event(BinApi_RETURN_ERROR, idRequest, error);
    event.SetEventObject(this);
    // ProcessEvent(event);
    wxPostEvent(this, event);
}
