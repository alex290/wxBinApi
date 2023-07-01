#ifndef FORMATDOP_H
#define FORMATDOP_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string_view>

class FormatDop
{
public:
    FormatDop();
    ~FormatDop();

    static std::vector<std::string> splitStr(std::string str, std::string spl);  // Разделить строку по тексту

    static std::string str_toupper(std::string s);  // Верхний регистр
    static std::string str_tolower(std::string s);  // Нижний регистр

    // static std::size_t replace_all(std::string& inout, std::string_view what, std::string_view with);  // Заменить текст

private:
};

#endif