#ifndef BINJSON_H
#define BINJSON_H

#include "json.hpp"
#include <string>
#include <iostream>

namespace Bapi
{
using Json = nlohmann::json;
}

class BinJson
{
public:
    BinJson();
    ~BinJson();

    static Bapi::Json parse(std::string text);
    static std::string toString(Bapi::Json json);
    static double toDouble(Bapi::Json json);
    static unsigned long long toULongLong(Bapi::Json json);
    static unsigned long toULong(Bapi::Json json);
    static long toLong(Bapi::Json json);
    static int toInt(Bapi::Json json);
    static bool toBool(Bapi::Json json);

private:
    // Json json;
};

#endif