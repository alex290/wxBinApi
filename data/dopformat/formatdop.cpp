#include "formatdop.h"

FormatDop::FormatDop()
{
}

FormatDop::~FormatDop()
{
}
std::vector<std::string> FormatDop::splitStr(std::string str, std::string spl)  // Разделить строку по тексту
{
    std::vector<std::string> ret;
    unsigned int size = str.size();
    unsigned int sizeSpl = spl.size();

    // Если текст меньше разделителя
    if (sizeSpl > size)
        ret.push_back(str);
    else
    {
        std::string newStr = str;
        std::string strVect = "";
        bool endd = false;
        int split = 0;
        for (size_t i = 0; i < (size - (sizeSpl - 1)); i++)
        {
            if (split > 0)  // Пропускаем текст по разделителю
                split--;
            else
            {
                std::string newSstrLoc = newStr;
                newSstrLoc.erase(newSstrLoc.begin() + sizeSpl, newSstrLoc.end());
                if (newSstrLoc == spl)  // Если найдено совпадение
                {
                    ret.push_back(strVect);
                    strVect = "";
                    split = sizeSpl - 1;

                    // Если последние
                    if (sizeSpl == newStr.size())
                        newStr = newStr[newStr.size() - 1];
                }
                else
                    strVect = strVect + str[i];
            }
            newStr.erase(newStr.begin());
        }

        if (ret.size() > 0)
        {
            // Вставляем последний кусок текста после разделителя
            newStr = "";

            for (size_t i = 0; i < ret.size(); i++)
                newStr = newStr + ret[i] + spl;

            std::string newSstrLoc = str;
            int endSize = newSstrLoc.size() - newStr.size();
            newSstrLoc.erase(newSstrLoc.begin(), newSstrLoc.end() - endSize);
            ret.push_back(newSstrLoc);
            // ===========================================
        }
        else  // Иначе вставяем весь текст
            ret.push_back(str);
    }

    return ret;
}

std::string FormatDop::str_toupper(std::string s)  // Верхний регистр
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::toupper(c); });
    return s;
}

std::string FormatDop::str_tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return s;
}
