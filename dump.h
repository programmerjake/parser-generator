#ifndef DUMP_H_INCLUDED
#define DUMP_H_INCLUDED

#include "symbol.h"
#include "rule.h"
#include "item.h"
#include <cwchar>
#include <string>

using namespace std;

struct FormattingOptions
{
    bool useEscapeSequences = true;
    bool useExtendedCharacters = true;
    enum CodeFormatType
    {
        Code
    };
    FormattingOptions()
    {
    }
    explicit FormattingOptions(CodeFormatType)
        : useEscapeSequences(false), useExtendedCharacters(false)
    {
    }
};

inline wstring dumpSymbol(gc_pointer<Symbol> symbol, FormattingOptions formatting)
{
    wstring retval;
    if(formatting.useEscapeSequences && symbol->isTerminal())
        retval = L"\x1b[23;4m";
    else if(formatting.useEscapeSequences)
        retval = L"\x1b[24;3m";
    retval += symbol->name;
    if(formatting.useEscapeSequences)
        retval += L"\x1b[24;23m";
    return retval;
}

inline wstring dumpSymbols(const SymbolSet &symbols, FormattingOptions formatting)
{
    wstring retval = L"{";
    bool isFirst = true;
    for(auto symbol : symbols)
    {
        if(isFirst)
            isFirst = false;
        else
            retval += L" ";
        retval += dumpSymbol(symbol, formatting);
    }
    retval += L"}";
    return retval;
}

inline wstring dumpSymbols(const TerminalSet &symbols, FormattingOptions formatting)
{
    wstring retval = L"{";
    bool isFirst = true;
    for(auto symbol : symbols)
    {
        if(isFirst)
            isFirst = false;
        else
            retval += L" ";
        retval += dumpSymbol(symbol, formatting);
    }
    retval += L"}";
    return retval;
}

inline wstring dumpSymbols(const SymbolList &symbols, FormattingOptions formatting, bool useBrackets = true)
{
    wstring retval = useBrackets ? L"[" : L"";
    bool isFirst = true;
    for(auto symbol : symbols)
    {
        if(isFirst)
            isFirst = false;
        else
            retval += L" ";
        retval += dumpSymbol(symbol, formatting);
    }
    if(useBrackets)
        retval += L"]";
    return retval;
}

inline wstring dumpRule(gc_pointer<Rule> rule, FormattingOptions formatting)
{
    wstring retval;
    retval = dumpSymbol(rule->lhs, formatting);
    retval += L" : ";
    retval += dumpSymbols(rule->rhs, formatting, false);
    retval += L" ";
    retval += rule->code.code;
    retval += L";";
    return retval;
}

inline wstring dumpItem(const Item &item, FormattingOptions formatting)
{
    wstring marker = L"";
    if(formatting.useEscapeSequences)
        marker += L"\x1b[1m";
    marker += formatting.useExtendedCharacters ? L"\u2022" : L"*";
    if(formatting.useEscapeSequences)
        marker += L"\x1b[22m";

    wstring retval = L"[";
    retval += dumpSymbol(item.rule->lhs, formatting);
    retval += formatting.useExtendedCharacters ? L" \u2192 " : L" -> ";
    for(size_t i = 0; i < item.rule->rhs.size(); i++)
    {
        if(i == item.currentLocation)
        {
            retval += marker;
            retval += L" ";
        }
        retval += dumpSymbol(item.rule->rhs[i], formatting);
        retval += L" ";
    }
    if(item.currentLocation >= item.rule->rhs.size())
    {
        retval += marker;
        retval += L" ";
    }
    retval += L": ";
    retval += dumpSymbol(item.lookahead, formatting);
    retval += L"]";
    return retval;
}

inline wstring dumpItemSet(const ItemSet &items, FormattingOptions formatting)
{
    wstring retval = L"{\n";
    for(const Item &item : items)
    {
        retval += dumpItem(item, formatting);
        retval += L"\n";
    }
    retval += L"}";
    return retval;
}

#endif // DUMP_H_INCLUDED
