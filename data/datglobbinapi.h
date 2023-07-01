#ifndef DATGLOBBINAPI_H
#define DATGLOBBINAPI_H

#include "marketdataendpoints.h"
#include <string>
#include <stdio.h>
#include <cstring>
#include <openssl/sha.h>
#include <openssl/hmac.h>

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

    static std::string hmacEncode(std::string param, std::string secret); // Получаем HMAC кодировку

private:
};

#endif