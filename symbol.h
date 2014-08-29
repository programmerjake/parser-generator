#ifndef SYMBOL_H
#define SYMBOL_H

#include <cwchar>
#include <string>
#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct TerminalSymbol;

typedef unordered_set<shared_ptr<TerminalSymbol>> TerminalSet;

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
    typedef unordered_map<wstring, shared_ptr<TerminalSymbol>> TerminalsType;
    static TerminalsType & terminals()
    {
        static shared_ptr<TerminalsType> retval = nullptr;
        if(retval == nullptr)
        {
            retval = make_shared<TerminalsType>();
        }
        return *retval;
    }
    TerminalSymbol(const wstring &name)
        : Symbol(name)
    {
    }
public:
    static shared_ptr<TerminalSymbol> make(const wstring &name)
    {
        shared_ptr<TerminalSymbol> &retval = terminals()[name];
        if(retval == nullptr)
        {
            retval = shared_ptr<TerminalSymbol>(new TerminalSymbol(name));
        }
        return retval;
    }
    static shared_ptr<TerminalSymbol> makeEmpty()
    {
        static shared_ptr<TerminalSymbol> retval;
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
    NonterminalSymbol(const wstring &name)
        : Symbol(name)
    {
    }
    virtual bool isTerminal() const override
    {
        return false;
    }
    TerminalSet firstSet;
};

typedef vector<shared_ptr<Symbol>> SymbolList;
typedef unordered_set<shared_ptr<Symbol>> SymbolSet;

#endif // SYMBOL_H