#ifndef ITEM_H
#define ITEM_H

#include "symbol.h"
#include "rule.h"
#include <cwchar>
#include <string>
#include <vector>
#include <memory>
#include "gc.h"
#include <unordered_set>

struct Item final
{
    gc_pointer<Rule> rule;
    size_t currentLocation;
    gc_pointer<TerminalSymbol> lookahead;
    Item(gc_pointer<Rule> rule, size_t currentLocation, gc_pointer<TerminalSymbol> lookahead)
        : rule(rule), currentLocation(currentLocation), lookahead(lookahead)
    {
    }
    bool operator ==(const Item &r) const
    {
        return rule == r.rule && currentLocation == r.currentLocation && lookahead == r.lookahead;
    }
    bool operator !=(const Item &r) const
    {
        return rule != r.rule || currentLocation != r.currentLocation || lookahead != r.lookahead;
    }
};

namespace std
{
template <>
struct hash<Item>
{
    size_t operator ()(const Item &item) const
    {
        return hash<gc_pointer<Rule>>()(item.rule) * 17 + item.currentLocation * 5 + hash<gc_pointer<TerminalSymbol>>()(item.lookahead);
    }
};
}

typedef unordered_set<Item> ItemSet;

struct ItemSetCompare
{
    bool operator()(const ItemSet &a, const ItemSet &b) const
    {
        for(const Item &v : a)
        {
            if(b.count(v) == 0)
                return false;
        }
        for(const Item &v : b)
        {
            if(a.count(v) == 0)
                return false;
        }
        return true;
    }
};

struct ItemSetHasher
{
    size_t operator ()(const ItemSet &s) const
    {
        size_t retval = s.size() * 8191;
        hash<Item> itemHasher;
        for(const Item &item : s) // must be order independent
        {
            retval += itemHasher(item);
        }
        return retval;
    }
};

#endif // ITEM_H