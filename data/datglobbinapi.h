#ifndef DATGLOBBINAPI_H
#define DATGLOBBINAPI_H

#include "bapimarketdata.h"
#include <string>
#include <stdio.h>
#include <cstring>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include "network/binapinetwork.h"
#include <functional>
#include "dopformat/binjson.h"

class DatGlobBinApi
{
public:
    enum class TypeHash
    {
        SHA256 = 0, /**< Использовать SHA256 */
        SHA512 = 1, /**< Использовать SHA512 */
    };
    DatGlobBinApi();
    ~DatGlobBinApi();

    std::function<void(Bapi::Json)> fapiRet;

    static std::string hmacEncode(std::string param, std::string secret);  // Получаем HMAC кодировку

private:
    BinApiNetwork* network;
    void returnData(BinApiNetworkEvent& event);
    void returnError(BinApiNetworkEvent& event);
};

#endif