#include "datglobbinapi.h"

DatGlobBinApi::DatGlobBinApi()
{
    network = new BinApiNetwork();
    network->Bind(BinApi_RETURN_DATA, &DatGlobBinApi::returnData, this);
    network->Bind(BinApi_RETURN_ERROR, &DatGlobBinApi::returnError, this);
}

DatGlobBinApi::~DatGlobBinApi()
{
    delete network;
}
std::string DatGlobBinApi::hmacEncode(std::string param, std::string secret)  // Получаем HMAC кодировку
{
    const char* key = secret.c_str();
    const char* input = param.c_str();
    const EVP_MD* engine = NULL;
    engine = EVP_sha256();

    unsigned char* p = (unsigned char*)malloc(1024);
    char buf[1024] = { 0 };
    char tmp[3] = { 0 };
    unsigned int output_length = 0;
    p = (unsigned char*)malloc(EVP_MAX_MD_SIZE);

    HMAC_CTX* ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, key, strlen(key), engine, NULL);
    HMAC_Update(ctx, (unsigned char*)input, strlen(input));  // input is OK; &input is WRONG !!!

    HMAC_Final(ctx, p, &output_length);
    for (int i = 0; i < 32; i++)
    {
        sprintf(tmp, "%02x", p[i]);
        strcat(buf, tmp);
    }
    return std::string(buf);
}

void DatGlobBinApi::GetUrl(std::string idRequest, std::string url)
{
    std::cout << idRequest << std::endl;
    network->GetRequest(url, idRequest);
}

void DatGlobBinApi::returnData(BinApiNetworkEvent& event)
{
    std::vector<std::string> idReq = FormatDop::splitStr(event.getIdRequest(), "_");
    if (idReq.size() == 2)
    {
        if (idReq[0] == "FAPI")  // Возвращаем данные в класс FuturesRestApi
        {
            Bapi::Json data = BinJson::parse(event.getData());
            RestEventData::TypeRestEvent typeRest = static_cast<RestEventData::TypeRestEvent>(std::stoi(idReq[1]));
            fapiRet(data, typeRest);
        }
    }
}

void DatGlobBinApi::returnError(BinApiNetworkEvent& event)
{
    std::vector<std::string> idReq = FormatDop::splitStr(event.getIdRequest(), "_");
    if (idReq.size() == 2)
    {
        if (idReq[0] == "FAPI")  // Возвращаем данные в класс FuturesRestApi
        {
            Bapi::Json data = BinJson::parse(event.getData());
            RestEventData::TypeRestEvent typeRest = static_cast<RestEventData::TypeRestEvent>(std::stoi(idReq[1]));
            fapiRetErr(data, event.getData(), typeRest);
        }
    }
}
