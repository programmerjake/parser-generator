#include <cwchar>
#include <iostream>
#include <string>
#include <unordered_set>
#include <tuple>
#include <vector>
#include <unordered_map>
#include "symbol.h"
#include "rule.h"
#include "item.h"
#include "generate.h"
#include "string_cast.h"
#include "dump.h"

using namespace std;

wstring errorActionString()
{
    return L"error";
}

wstring reduceActionString(shared_ptr<Rule> rule)
{
    return L"reduce : " + dumpRule(rule, FormattingOptions());
}

struct ItemSetProperties
{
    static constexpr size_t NoIndex = ~(size_t)0;
    size_t index;
    unordered_map<shared_ptr<Symbol>, size_t> gotoTable;
    ItemSetProperties(size_t index = NoIndex)
        : index(index)
    {
    }
};

int main()
{
    FormattingOptions formatting;
    SymbolSet symbols;
    shared_ptr<NonterminalSymbol> startSymbol = make_shared<NonterminalSymbol>(L"Start");
    symbols.insert(startSymbol);
    shared_ptr<NonterminalSymbol> listSymbol = make_shared<NonterminalSymbol>(L"List");
    symbols.insert(listSymbol);
    shared_ptr<NonterminalSymbol> pairSymbol = make_shared<NonterminalSymbol>(L"Pair");
    symbols.insert(pairSymbol);
    shared_ptr<TerminalSymbol> lparenSymbol = TerminalSymbol::make(L"(");
    symbols.insert(lparenSymbol);
    shared_ptr<TerminalSymbol> rparenSymbol = TerminalSymbol::make(L")");
    symbols.insert(rparenSymbol);

    cout << string_cast<string>(dumpSymbols(symbols, formatting)) << endl << endl;

    RuleSet rules;
    shared_ptr<Rule> startRule = make_shared<Rule>(startSymbol, SymbolList{listSymbol}, L"{cout << \"1\\n\";}");
    rules.insert(startRule);
    rules.insert(make_shared<Rule>(listSymbol, SymbolList{listSymbol, pairSymbol}, L"{cout << \"2\\n\";}"));
    rules.insert(make_shared<Rule>(listSymbol, SymbolList{pairSymbol}, L"{cout << \"3\\n\";}"));
    rules.insert(make_shared<Rule>(pairSymbol, SymbolList{lparenSymbol, pairSymbol, rparenSymbol}, L"{cout << \"4\\n\";}"));
    rules.insert(make_shared<Rule>(pairSymbol, SymbolList{lparenSymbol, rparenSymbol}, L"{cout << \"5\\n\";}"));

    calculateFirstSets(symbols, rules);

    for(shared_ptr<Symbol> symbol : symbols)
    {
        cout << string_cast<string>(dumpSymbol(symbol, formatting) + L" : " + dumpSymbols(first(symbol), formatting)) << endl;
    }
    cout << endl;

    ItemSet startSet;
    startSet.insert(Item(startRule, 0, TerminalSymbol::make(L"EOF")));

    startSet = closure(startSet, rules);

    unordered_map<ItemSet, ItemSetProperties, ItemSetHasher, ItemSetCompare> canonicalCollection;
    vector<pair<ItemSet, ItemSetProperties>> canonicalSets;
    size_t nextSet = 0;
    canonicalSets.push_back(make_pair(startSet, ItemSetProperties(nextSet++)));
    canonicalCollection[startSet] = get<1>(canonicalSets.back());

    cout << "Set " << nextSet << " : " << string_cast<string>(dumpItemSet(get<0>(canonicalSets.back()), formatting)) << endl << endl;

    for(size_t i = 0; i < canonicalSets.size(); i++)
    {
        for(shared_ptr<Symbol> symbol : symbols)
        {
            ItemSet newSet = calculateGoto(get<0>(canonicalSets[i]), symbol, rules);
            if(newSet.empty())
                continue;
            ItemSetProperties &properties = canonicalCollection[newSet];
            if(properties.index == ItemSetProperties::NoIndex)
            {
                properties.index = nextSet++;
                canonicalSets.push_back(make_pair(newSet, properties));
                cout << "Set " << nextSet << " : " << string_cast<string>(dumpItemSet(get<0>(canonicalSets.back()), formatting)) << endl << endl;
            }
            get<1>(canonicalSets[i]).gotoTable[symbol] = properties.index;
            cout << "goto(" << (i + 1) << ", " << string_cast<string>(dumpSymbol(symbol, formatting)) << ") = " << (properties.index + 1) << endl << endl;
        }
    }

    vector<shared_ptr<Symbol>> terminalSymbols;
    unordered_map<shared_ptr<Symbol>, size_t> terminalSymbolMap;

    for(shared_ptr<Symbol> symbol : symbols)
    {
        if(symbol->isTerminal())
        {
            terminalSymbolMap[symbol] = terminalSymbols.size();
            terminalSymbols.push_back(symbol);
        }
    }

#if 0
    vector<vector<vector<wstring>>> actionsTable;
    actionsTable.resize(canonicalSets.size());
    for(size_t state = 0; state < actionsTable.size(); state++)
    {
        vector<vector<wstring>> &actionsRow = actionsTable[state];
        actionsRow.resize(terminalSymbols.size());
        for(size_t symbolIndex = 0; symbolIndex < terminalSymbols.size(); symbolIndex++)
        {
            actionsRow[symbolIndex] = errorActionString();
            unordered_map<shared_ptr<Symbol>, size_t> &gotoTable = get<1>(canonicalSets[i]).gotoTable;
        }
    }
#endif
    return 0;
}