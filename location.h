#ifndef LOCATION_H_INCLUDED
#define LOCATION_H_INCLUDED

#include <cwchar>
#include <string>
#include <sstream>

struct Location
{
    wstring fileName;
    size_t line, column;
    Location(wstring fileName, size_t line, size_t column)
        : fileName(fileName), line(line), column(column)
    {
    }
    Location(wstring fileName)
        : fileName(fileName), line(1), column(1)
    {
    }
    explicit operator wstring() const
    {
        wostringstream ss;
        ss << fileName << L":" << line << ":" << column;
        return ss.str();
    }
    wstring getCLineDirective() const
    {
        wostringstream ss;
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
    wstring code;
    bool empty() const
    {
        return code.empty();
    }
    CodeSection()
        : location(L"")
    {
    }
    CodeSection(Location location, wstring code)
        : location(location), code(code)
    {
    }
};

#endif // LOCATION_H_INCLUDED
