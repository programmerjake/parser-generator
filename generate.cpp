#include "generate.h"
#include "dump.h"
#include <cassert>
#include <iostream>
#include "string_cast.h"

using namespace std;

void calculateFirstSets(const SymbolSet &symbols, const RuleSet &rules)
{
    for(gc_pointer<Symbol> symbol : symbols)
    {
        if(!symbol->isTerminal())
        {
            gc_pointer<NonterminalSymbol> s = dynamic_pointer_cast<NonterminalSymbol>(symbol);
            assert(s != nullptr);
            s->firstSet.clear();
        }
    }
    bool didAnything = true;
    while(didAnything)
    {
        didAnything = false;
        for(gc_pointer<Symbol> symbol : symbols)
        {
            if(symbol->isTerminal())
                continue;
            gc_pointer<NonterminalSymbol> s = dynamic_pointer_cast<NonterminalSymbol>(symbol);
            assert(s != nullptr);
            TerminalSet &firstSet = s->firstSet;
            for(gc_pointer<Rule> rule : rules.match(s))
            {
                TerminalSet newFirstSet = first(rule->rhs);
                for(gc_pointer<TerminalSymbol> ts : newFirstSet)
                {
                    if(get<1>(firstSet.insert(ts)))
                        didAnything = true;
                }
            }
        }
    }
}

TerminalSet first(gc_pointer<Symbol> symbol)
{
    assert(symbol != nullptr);
    if(symbol->isTerminal())
    {
        TerminalSet retval;
        gc_pointer<TerminalSymbol> s = dynamic_pointer_cast<TerminalSymbol>(symbol);
        assert(s != nullptr);
        retval.insert(s);
        return move(retval);
    }
    gc_pointer<NonterminalSymbol> s = dynamic_pointer_cast<NonterminalSymbol>(symbol);
    return s->firstSet;
}

TerminalSet first(SymbolList symbols)
{
    TerminalSet retval;
    gc_pointer<TerminalSymbol> emptySymbol = TerminalSymbol::makeEmpty();
    for(gc_pointer<Symbol> symbol : symbols)
    {
        bool hasEmpty = false;
        for(gc_pointer<TerminalSymbol> ts : first(symbol))
        {
            if(ts == emptySymbol)
                hasEmpty = true;
            else
                retval.insert(ts);
        }
        if(!hasEmpty)
            return retval;
    }
    retval.insert(emptySymbol);
    return retval;
}

ItemSet closure(ItemSet items, const RuleSet &rules)
{
    bool didAnything = true;
    ItemSet worklist = items;
    while(didAnything)
    {
        didAnything = false;
        ItemSet nextWorklist;
        for(const Item &item : worklist)
        {
            assert(item.rule != nullptr);
            if(item.currentLocation >= item.rule->rhs.size())
                continue;
            gc_pointer<Symbol> peekSymbolGeneric = item.rule->rhs[item.currentLocation];
            assert(peekSymbolGeneric != nullptr);
            if(peekSymbolGeneric->isTerminal())
                continue;
            gc_pointer<NonterminalSymbol> peekSymbol = dynamic_pointer_cast<NonterminalSymbol>(peekSymbolGeneric);
            assert(peekSymbol != nullptr);
            //cout << "matching : " << string_cast<string>(dumpItem(item, FormattingOptions())) << endl;
            for(gc_pointer<Rule> rule : rules.match(peekSymbol))
            {
                SymbolList symbolList = item.rule->rhs;
                symbolList.erase(symbolList.begin(), symbolList.begin() + (item.currentLocation + 1));
                symbolList.push_back(item.lookahead);
                //cout << "lookahead : " << string_cast<string>(dumpSymbols(symbolList, FormattingOptions())) << endl;
                for(gc_pointer<TerminalSymbol> ts : first(symbolList))
                {
                    Item newItem(rule, 0, ts);
                    //cout << "testing : " << string_cast<string>(dumpItem(newItem, FormattingOptions())) << endl;
                    if(get<1>(items.insert(newItem)))
                    {
                        didAnything = true;
                        nextWorklist.insert(newItem);
                        //cout << "inserted\n";
                    }
                }
            }
        }
        worklist = move(nextWorklist);
    }
    return move(items);
}

ItemSet calculateGoto(ItemSet items, gc_pointer<Symbol> acceptedSymbol, const RuleSet &rules)
{
    ItemSet retval;
    for(const Item &item : items)
    {
        assert(item.rule != nullptr);
        if(item.currentLocation >= item.rule->rhs.size())
            continue;
        if(item.rule->rhs[item.currentLocation] != acceptedSymbol)
            continue;
        Item newItem = item;
        newItem.currentLocation++;
        retval.insert(newItem);
    }
    return closure(move(retval), rules);
}