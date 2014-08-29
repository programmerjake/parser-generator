#ifndef RULE_H
#define RULE_H

#include "symbol.h"
#include <cwchar>
#include <string>
#include <memory>
#include <unordered_map>
#include <iterator>
#include <tuple>
#include <cassert>

using namespace std;

struct Rule final
{
    shared_ptr<NonterminalSymbol> lhs;
    SymbolList rhs;
    wstring code;
    Rule(shared_ptr<NonterminalSymbol> lhs, SymbolList rhs, wstring code = L"")
        : lhs(lhs), rhs(rhs), code(code)
    {
    }
};

class RuleSet final
{
    typedef unordered_multimap<shared_ptr<NonterminalSymbol>, shared_ptr<Rule>> RulesType;
    RulesType rules;
public:
    class iterator : public std::iterator<std::forward_iterator_tag, const shared_ptr<Rule>>
    {
        friend class RuleSet;
        RulesType::const_iterator internalIterator;
        explicit iterator(RulesType::const_iterator internalIterator)
            : internalIterator(internalIterator)
        {
        }
    public:
        iterator()
        {
        }
        const shared_ptr<Rule> &operator *() const
        {
            return get<1>(*internalIterator);
        }
        const shared_ptr<Rule> *operator ->() const
        {
            return &get<1>(*internalIterator);
        }
        const iterator &operator ++()
        {
            ++internalIterator;
            return *this;
        }
        const iterator operator ++(int)
        {
            return iterator(internalIterator++);
        }
        bool operator ==(const iterator &r) const
        {
            return internalIterator == r.internalIterator;
        }
        bool operator !=(const iterator &r) const
        {
            return internalIterator != r.internalIterator;
        }
    };
    iterator begin() const
    {
        return iterator(rules.begin());
    }
    iterator end() const
    {
        return iterator(rules.end());
    }
    iterator cbegin() const
    {
        return iterator(rules.cbegin());
    }
    iterator cend() const
    {
        return iterator(rules.cend());
    }
    class MatchRetval final
    {
        friend class RuleSet;
        iterator beginValue;
        iterator endValue;
        size_t sizeValue;
        MatchRetval(iterator beginValue, iterator endValue, size_t sizeValue)
            : beginValue(beginValue), endValue(endValue), sizeValue(sizeValue)
        {
        }
    public:
        iterator begin() const
        {
            return beginValue;
        }
        iterator end() const
        {
            return endValue;
        }
        size_t size() const
        {
            return sizeValue;
        }
    };
    MatchRetval match(shared_ptr<NonterminalSymbol> key) const
    {
        auto v = rules.equal_range(key);
        return MatchRetval(iterator(get<0>(v)), iterator(get<1>(v)), rules.count(key));
    }
    iterator find(shared_ptr<Rule> lookFor) const
    {
        auto matches = match(lookFor->lhs);
        for(auto i = matches.begin(); i != matches.end(); ++i)
        {
            if(lookFor == *i)
                return i;
        }
        return end();
    }
    iterator insert(const shared_ptr<Rule> &rule)
    {
        assert(rule != nullptr);
        return iterator(rules.insert(make_pair(rule->lhs, rule)));
    }
    size_t count(shared_ptr<NonterminalSymbol> key) const
    {
        return rules.count(key);
    }
    size_t size() const
    {
        return rules.size();
    }
    bool operator ==(const RuleSet &rt) const
    {
        for(auto v : *this)
        {
            if(rt.find(v) == rt.end())
                return false;
        }
        for(auto v : rt)
        {
            if(find(v) == end())
                return false;
        }
        return true;
    }
    bool operator !=(const RuleSet &rt) const
    {
        for(auto v : *this)
        {
            if(rt.find(v) == rt.end())
                return true;
        }
        for(auto v : rt)
        {
            if(find(v) == end())
                return true;
        }
        return false;
    }
};

namespace std
{
template <>
struct hash<RuleSet>
{
    size_t operator ()(const RuleSet & rs) const
    {
        size_t retval = rs.size() * 8191;
        hash<shared_ptr<Rule>> pointerHasher;
        for(shared_ptr<Rule> rule : rs) // must be order independent
        {
            retval += pointerHasher(rule);
        }
        return retval;
    }
};
}

#endif // RULE_H