#include "datglobbinapi.h"

DatGlobBinApi::DatGlobBinApi()
{
    network = new BinApiNetwork();
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
