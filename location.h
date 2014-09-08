#ifndef LOCATION_H_INCLUDED
#define LOCATION_H_INCLUDED

#include <cwchar>
#include <string>
#include <sstream>

struct Location
{
    std::wstring fileName;
    size_t line, column;
    Location(std::wstring fileName, size_t line, size_t column)
        : fileName(fileName), line(line), column(column)
    {
    }
    Location(std::wstring fileName)
        : fileName(fileName), line(1), column(1)
    {
    }
    explicit operator std::wstring() const
    {
        std::wostringstream ss;
        ss << fileName << L":" << line << ":" << column;
        return ss.str();
    }
    std::wstring getCLineDirective() const
    {
        std::wostringstream ss;
        ss << L"#line " << line << L" \"";
        for(wchar_t ch : fileName)
        {
            switch(ch)
            {
            case '\\':
            case '\'':
            case '\"':
                ss << L"\\" << ch;
                break;
            default:
                ss << ch;
                break;
            }
        }
        ss << L"\"\n";
        return ss.str();
    }
};

struct CodeSection
{
    Location location;
    std::wstring code;
    bool empty() const
    {
        return code.empty();
    }
    CodeSection()
        : location(L"")
    {
    }
    CodeSection(Location location, std::wstring code)
        : location(location), code(code)
    {
    }
};

#endif // LOCATION_H_INCLUDED
