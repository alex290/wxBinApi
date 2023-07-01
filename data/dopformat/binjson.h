#ifndef BINJSON_H
#define BINJSON_H

#include "json.hpp"
#include <string>
#include <iostream>

using Json = nlohmann::json;

class BinJson
{
public:
    BinJson();
    ~BinJson();

    static Json parse(std::string text);
    static std::string toString(Json json);
    static double toDouble(Json json);
    static unsigned long long toULongLong(Json json);
    static unsigned long toULong(Json json);
    static long toLong(Json json);
    static int toInt(Json json);
    static bool toBool(Json json);

private:
    // Json json;
};

#endif