#ifndef SYMBOL_H
#define SYMBOL_H

#include <cwchar>
#include <string>
#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "gc.h"
#include "location.h"

using namespace std;

struct TerminalSymbol;

typedef unordered_set<gc_pointer<TerminalSymbol>> TerminalSet;

struct Symbol
{
    const wstring name;
    Symbol(const wstring &name)
        : name(name)
    {
    }
    virtual ~Symbol()
    {
    }
    virtual bool isTerminal() const = 0;
};

class TerminalSymbol final : public Symbol
{
    typedef unordered_map<wstring, gc_pointer<TerminalSymbol>> TerminalsType;
    static TerminalsType & terminals()
    {
        static gc_pointer<TerminalsType> retval = nullptr;
        if(retval == nullptr)
        {
            retval = make_gc_ptr<TerminalsType>();
        }
        return *retval;
    }
    TerminalSymbol(const wstring &name)
        : Symbol(name)
    {
    }
public:
    static gc_pointer<TerminalSymbol> make(const wstring &name)
    {
        gc_pointer<TerminalSymbol> &retval = terminals()[name];
        if(retval == nullptr)
        {
            retval = gc_pointer<TerminalSymbol>(new TerminalSymbol(name));
        }
        return retval;
    }
    static gc_pointer<TerminalSymbol> makeEmpty()
    {
        static gc_pointer<TerminalSymbol> retval;
        if(retval == nullptr)
            retval = make(L"");
        return retval;
    }
    virtual bool isTerminal() const override
    {
        return true;
    }
    bool isEmpty() const
    {
        return name == L"";
    }
};

class NonterminalSymbol final : public Symbol
{
public:
    NonterminalSymbol(Location location, const wstring &name)
        : Symbol(name), location(location)
    {
    }
    virtual bool isTerminal() const override
    {
        return false;
    }
    TerminalSet firstSet;
    size_t lhsUseCount = 0;
    size_t rhsUseCount = 0;
    Location location;
};

typedef vector<gc_pointer<Symbol>> SymbolList;
typedef unordered_set<gc_pointer<Symbol>> SymbolSet;

#endif // SYMBOL_H