#ifndef GENERATE_H_INCLUDED
#define GENERATE_H_INCLUDED

#include "symbol.h"
#include "rule.h"
#include "item.h"

void calculateFirstSets(const SymbolSet &symbols, const RuleSet &rules);
TerminalSet first(gc_pointer<Symbol> symbol);
TerminalSet first(SymbolList symbols);
ItemSet closure(ItemSet items, const RuleSet &rules);
ItemSet calculateGoto(ItemSet items, gc_pointer<Symbol> acceptedSymbol, const RuleSet &rules);

#endif // GENERATE_H_INCLUDED
