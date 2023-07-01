#include "binjson.h"

BinJson::BinJson()
{
}

BinJson::~BinJson()
{
}
Bapi::Json BinJson::parse(std::string text)
{
    Bapi::Json json;
    if (text == "")
    {
        return Bapi::Json::parse("{}");
    }
    else
    {
        try
        {
            // parsing input with a syntax error
            json = Bapi::Json::parse(text);
        }
        catch (Bapi::Json::parse_error& e)
        {
            // output exception information
            std::cout << "message: " << e.what() << '\n' << "exception id: " << e.id << '\n' << "byte position of error: " << e.byte << std::endl;
        }
    }

    return json;
}

std::string BinJson::toString(Bapi::Json json)
{
    if (json.is_string())
        return json.get<std::string>();
    return "";
}

double BinJson::toDouble(Bapi::Json json)
{
    if (json.is_number())
        return json.get<double>();
    else if (json.is_string())
        return std::stod(json.get<std::string>());

    return 0;
}

unsigned long long BinJson::toULongLong(Bapi::Json json)
{
    if (json.is_number())
        return json.get<unsigned long long>();
    else if (json.is_string())
        return std::stoull(json.get<std::string>());

    return 0;
}

unsigned long BinJson::toULong(Bapi::Json json)
{
    if (json.is_number())
        return json.get<unsigned long>();
    else if (json.is_string())
        return std::stoul(json.get<std::string>());

    return 0;
}
long BinJson::toLong(Bapi::Json json)
{
    if (json.is_number())
        return json.get<long>();
    else if (json.is_string())
        return std::stol(json.get<std::string>());

    return 0;
}

int BinJson::toInt(Bapi::Json json)
{
    if (json.is_number())
        return json.get<int>();
    else if (json.is_string())
        return std::stoi(json.get<std::string>());

    return 0;
}

bool BinJson::toBool(Bapi::Json json) {
    if (json.is_boolean())
        return json.get<bool>();

    return false;
}
