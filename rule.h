#ifndef RULE_H
#define RULE_H

#include "symbol.h"
#include <cwchar>
#include <string>
#include <memory>
#include "gc.h"
#include <unordered_map>
#include <iterator>
#include <tuple>
#include <cassert>
#include <functional>
#include <cwctype>
#include "location.h"

using namespace std;

struct Rule final
{
    gc_pointer<NonterminalSymbol> lhs;
    SymbolList rhs;
    CodeSection code;
    Rule(gc_pointer<NonterminalSymbol> lhs, SymbolList rhs, CodeSection code = CodeSection())
        : lhs(lhs), rhs(rhs), code(code)
    {
        lhs->lhsUseCount++;
        for(gc_pointer<Symbol> symbol : rhs)
        {
            if(symbol->isTerminal())
                continue;
            gc_pointer<NonterminalSymbol> s = dynamic_pointer_cast<NonterminalSymbol>(symbol);
            assert(s != nullptr);
            s->rhsUseCount++;
        }
    }
    wstring substituteCPlusPlusCode(function<wstring(int)> getArgString, wstring destString) const
    {
        if(code.empty())
            return L"";
        wint_t stringLiteralDelimiter = WEOF;
        bool gotEscape = false;
        int index = 0;
        bool gotArgString = false, gettingArgString = false;
        wstring retval = code.location.getCLineDirective();
        for(wchar_t ch : code.code)
        {
            if(stringLiteralDelimiter != WEOF)
            {
                if(gotEscape)
                {
                    gotEscape = false;
                }
                else if(ch == '\\')
                {
                    gotEscape = true;
                }
                else if((wint_t)ch == stringLiteralDelimiter)
                {
                    stringLiteralDelimiter = WEOF;
                }
            }
            else if(ch == '$')
            {
                if(!gotArgString && gettingArgString)
                {
                    gettingArgString = false;
                    retval += destString;
                    continue;
                }
                else if(gotArgString && gettingArgString)
                {
                    retval += getArgString(index);
                    index = 0;
                    gotArgString = false;
                    continue;
                }
                else
                {
                    index = 0;
                    gotArgString = false;
                    gettingArgString = true;
                    continue;
                }
            }
            else if(iswdigit(ch) && gettingArgString)
            {
                gotArgString = true;
                index *= 10;
                index += ch - '0';
                continue;
            }
            else if(gotArgString)
            {
                retval += getArgString(index);
                index = 0;
                gotArgString = false;
                gettingArgString = false;
            }
            else if(gettingArgString)
            {
                retval += '$';
                gettingArgString = false;
            }
            retval += ch;
        }
        return retval;
    }
};

class RuleSet final
{
    typedef unordered_multimap<gc_pointer<NonterminalSymbol>, gc_pointer<Rule>> RulesType;
    RulesType rules;
public:
    class iterator : public std::iterator<std::forward_iterator_tag, const gc_pointer<Rule>>
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
        const gc_pointer<Rule> &operator *() const
        {
            return get<1>(*internalIterator);
        }
        const gc_pointer<Rule> *operator ->() const
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
    MatchRetval match(gc_pointer<NonterminalSymbol> key) const
    {
        auto v = rules.equal_range(key);
        return MatchRetval(iterator(get<0>(v)), iterator(get<1>(v)), rules.count(key));
    }
    iterator find(gc_pointer<Rule> lookFor) const
    {
        auto matches = match(lookFor->lhs);
        for(auto i = matches.begin(); i != matches.end(); ++i)
        {
            if(lookFor == *i)
                return i;
        }
        return end();
    }
    iterator insert(const gc_pointer<Rule> &rule)
    {
        assert(rule != nullptr);
        return iterator(rules.insert(make_pair(rule->lhs, rule)));
    }
    size_t count(gc_pointer<NonterminalSymbol> key) const
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
        hash<gc_pointer<Rule>> pointerHasher;
        for(gc_pointer<Rule> rule : rs) // must be order independent
        {
            retval += pointerHasher(rule);
        }
        return retval;
    }
};
}

#endif // RULE_H