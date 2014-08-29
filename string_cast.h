#ifndef STRING_CAST_H_INCLUDED
#define STRING_CAST_H_INCLUDED

#include <cwchar>
#include <string>
#include <cstring>
#include <cstdint>

using namespace std;

#if WCHAR_MAX == 0xFFFFFFFFU && WCHAR_MIN == 0U
#define WCHAR_BITS (32)
#define WCHAR_SIGN unsigned
#define UNSIGNED_WCHAR wchar_t
#elif WCHAR_MAX == 0x7FFFFFFF && WCHAR_MIN == -0x80000000
#define WCHAR_BITS (32)
#define WCHAR_SIGN signed
#define UNSIGNED_WCHAR uint_least32_t
#elif WCHAR_MAX == 0xFFFFU && WCHAR_MIN == 0U
#define WCHAR_BITS (16)
#define WCHAR_SIGN unsigned
#define UNSIGNED_WCHAR wchar_t
#elif WCHAR_MAX == 0x7FFF && WCHAR_MIN == -0x8000
#define WCHAR_BITS (16)
#define WCHAR_SIGN signed
#define UNSIGNED_WCHAR uint_least16_t
#else
#error can not detect number of bits in wchar_t
#endif

template <typename T>
T string_cast(string);

template <typename T>
T string_cast(wstring);

template <>
inline string string_cast<string>(string str)
{
    return str;
}

template <>
inline wstring string_cast<wstring>(wstring str)
{
    return str;
}

template <>
inline string string_cast<string>(wstring wstr)
{
#if 1
    string retval;
    for(size_t i = 0; i < wstr.size(); i++)
    {
        unsigned value = static_cast<unsigned>(static_cast<UNSIGNED_WCHAR>(wstr[i]));
#if WCHAR_BITS == 16
        if(value >= 0xD800U && value <= 0xDBFFU && i + 1 < wstr.size())
        {
            unsigned nextValue = static_cast<unsigned>(static_cast<UNSIGNED_WCHAR>(wstr[i]));
            if(nextValue >= 0xDC00U && nextValue <= 0xDFFFU)
            {
                i++;
                value -= 0xD800U;
                nextValue -= 0xDC00U;
                value <<= 10;
                value += nextValue;
            }
        }
#endif
        value &= 0x1FFFFFU;
        if(value <= 0x7FU)
        {
            retval += (char)value;
        }
        else if(value <= 0x7FFU)
        {
            retval += (char)((value >> 6) | 0xC0U);
            retval += (char)((value & 0x3FU) | 0x80U);
        }
        else if(value <= 0xFFFFU)
        {
            retval += (char)((value >> 12) | 0xE0U);
            retval += (char)(((value >> 6) & 0x3FU) | 0x80U);
            retval += (char)((value & 0x3FU) | 0x80U);
        }
        else
        {
            retval += (char)((value >> 18) | 0xF0U);
            retval += (char)(((value >> 12) & 0x3FU) | 0x80U);
            retval += (char)(((value >> 6) & 0x3FU) | 0x80U);
            retval += (char)((value & 0x3FU) | 0x80U);
        }
    }
    return retval;
#warning finish implementing new code for string_cast<wstring>(string)
#else
    size_t destLen = wstr.length() * 4 + 1 + 32/*for extra buffer space*/;
    char *str = new char[destLen];
    for(size_t i = 0; i < destLen; i++)
        str[i] = 0;
    const wchar_t *ptr = wstr.c_str();
    mbstate_t mbstate;
    memset((void *)&mbstate, 0, sizeof(mbstate));
    size_t v = wcsrtombs(str, &ptr, destLen - 1, &mbstate);

    if(v == (size_t) - 1)
    {
        delete []str;
        throw runtime_error("can't convert wide character string to multi-byte string");
    }

    str[v] = '\0';
    string retval = str;
    delete []str;
    return retval;
#endif
}

template <>
inline wstring string_cast<wstring>(string str)
{
    size_t destLen = str.length() + 1 + 32/* for extra buffer space*/;
    wchar_t *wstr = new wchar_t[destLen];
    for(size_t i = 0; i < destLen; i++)
        wstr[i] = 0;
    const char *ptr = str.c_str();
    mbstate_t mbstate;
    memset((void *)&mbstate, 0, sizeof(mbstate));
    size_t v = mbsrtowcs(wstr, &ptr, destLen - 1, &mbstate);

    if(v == (size_t) - 1)
    {
        delete []wstr;
        throw runtime_error("can't convert multi-byte string to wide character string");
    }

    wstr[v] = '\0';
    wstring retval = wstr;
    delete []wstr;
    return retval;
}

#endif // STRING_CAST_H_INCLUDED
