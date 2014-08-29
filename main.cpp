#include <cwchar>
#include <iostream>
#include <string>
#include <unordered_set>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "symbol.h"
#include "rule.h"
#include "item.h"
#include "generate.h"
#include "string_cast.h"
#include "dump.h"
#include "file_writer.h"

using namespace std;

static constexpr size_t NoIndex = ~(size_t)0;

struct ActionType
{
    enum Type
    {
        Error,
        Shift,
        Reduce,
        Accept,
    };
    Type type;
    shared_ptr<Rule> rule;
    size_t index = NoIndex;
    ActionType()
        : type(Error), rule(nullptr)
    {
    }
    ActionType(shared_ptr<Rule> rule, size_t index, bool isAccept)
        : type(isAccept ? Accept : Reduce), rule(rule), index(index)
    {
    }
    ActionType(size_t index)
        : type(Shift), rule(nullptr), index(index)
    {
    }
    bool operator ==(const ActionType &rt) const
    {
        return type == rt.type && rule == rt.rule && index == rt.index;
    }
    bool operator !=(const ActionType &rt) const
    {
        return type != rt.type || rule != rt.rule || index != rt.index;
    }
    size_t hashCode() const
    {
        return (size_t)type * 5 + hash<shared_ptr<Rule>>()(rule) + index * 17;
    }
    void write(FileWriter *writer, size_t lookahead) const
    {
        switch(type)
        {
        case Shift:
            writer->writeShiftAction(index, lookahead);
            return;
        case Reduce:
            writer->writeReduceAction(rule, index, lookahead);
            return;
        case Accept:
            writer->writeAcceptAction(rule, index, lookahead);
            return;
        default:
            writer->writeErrorAction(lookahead);
            return;
        }
    }
    operator wstring() const
    {
        switch(type)
        {
        case Shift:
            return L"shift";
        case Reduce:
            return L"reduce : '" + dumpRule(rule, FormattingOptions()) + L"'";
        case Accept:
            return L"accept : '" + dumpRule(rule, FormattingOptions()) + L"'";
        default:
            return L"error";
        }
    }

};

namespace std
{
template <>
struct hash<ActionType>
{
    size_t operator ()(const ActionType &v) const
    {
        return v.hashCode();
    }
};
}

struct ItemSetProperties
{
    size_t index;
    unordered_map<shared_ptr<Symbol>, size_t> gotoTable;
    ItemSetProperties(size_t index = NoIndex)
        : index(index)
    {
    }
};

int main()
{
    SymbolSet symbols;
    RuleSet rules;
    shared_ptr<NonterminalSymbol> startSymbol = make_shared<NonterminalSymbol>(L"Start");
    symbols.insert(startSymbol);
    shared_ptr<TerminalSymbol> eofSymbol = TerminalSymbol::make(L"EOF");
    symbols.insert(eofSymbol);
#define DECLARE_SYMBOL(s) \
    shared_ptr<NonterminalSymbol> symbol ## s = make_shared<NonterminalSymbol>(L ## #s); \
    symbols.insert(symbol ## s)
#define DECLARE_TSYMBOL(s, v) \
    shared_ptr<TerminalSymbol> symbol ## s = TerminalSymbol::make(L ## #v); \
    symbols.insert(symbol ## s)
#define DECLARE_RULE(t, code, ...) \
    rules.insert(make_shared<Rule>(t, SymbolList{__VA_ARGS__}, code))
    DECLARE_SYMBOL(Statement);
    DECLARE_SYMBOL(Expression);
    DECLARE_SYMBOL(Term);
    DECLARE_SYMBOL(Factor);
    DECLARE_SYMBOL(Number);
    DECLARE_SYMBOL(Digit);
    DECLARE_SYMBOL(WS);
    DECLARE_TSYMBOL(Plus, '+');
    DECLARE_TSYMBOL(Minus, '-');
    DECLARE_TSYMBOL(Times, '*');
    DECLARE_TSYMBOL(Divide, '/');
    DECLARE_TSYMBOL(Semicolon, ';');
    DECLARE_TSYMBOL(LParen, '(');
    DECLARE_TSYMBOL(RParen, ')');
    DECLARE_TSYMBOL(Space, ' ');
    DECLARE_TSYMBOL(Tab, '\t');
    DECLARE_TSYMBOL(Newline, '\n');
    DECLARE_TSYMBOL(D0, '0');
    DECLARE_TSYMBOL(D1, '1');
    DECLARE_TSYMBOL(D2, '2');
    DECLARE_TSYMBOL(D3, '3');
    DECLARE_TSYMBOL(D4, '4');
    DECLARE_TSYMBOL(D5, '5');
    DECLARE_TSYMBOL(D6, '6');
    DECLARE_TSYMBOL(D7, '7');
    DECLARE_TSYMBOL(D8, '8');
    DECLARE_TSYMBOL(D9, '9');

    DECLARE_RULE(symbolDigit, L"{$$ = $1 - '0';}", symbolD0);
    DECLARE_RULE(symbolDigit, L"{$$ = $1 - '0';}", symbolD1);
    DECLARE_RULE(symbolDigit, L"{$$ = $1 - '0';}", symbolD2);
    DECLARE_RULE(symbolDigit, L"{$$ = $1 - '0';}", symbolD3);
    DECLARE_RULE(symbolDigit, L"{$$ = $1 - '0';}", symbolD4);
    DECLARE_RULE(symbolDigit, L"{$$ = $1 - '0';}", symbolD5);
    DECLARE_RULE(symbolDigit, L"{$$ = $1 - '0';}", symbolD6);
    DECLARE_RULE(symbolDigit, L"{$$ = $1 - '0';}", symbolD7);
    DECLARE_RULE(symbolDigit, L"{$$ = $1 - '0';}", symbolD8);
    DECLARE_RULE(symbolDigit, L"{$$ = $1 - '0';}", symbolD9);

    //DECLARE_RULE(symbolWS, L"", symbolSpace);
    //DECLARE_RULE(symbolWS, L"", symbolTab);
    //DECLARE_RULE(symbolWS, L"", symbolNewline);
    rules.insert(make_shared<Rule>(symbolWS, SymbolList{}, L""));

    DECLARE_RULE(symbolStatement, L"{cout << \"output : \" << $1 << \"\\n\";}", symbolExpression, symbolWS, symbolSemicolon);

    DECLARE_RULE(startSymbol, L"", symbolStatement);
    DECLARE_RULE(startSymbol, L"", symbolStatement, symbolNewline);
    DECLARE_RULE(startSymbol, L"", startSymbol, symbolStatement);
    DECLARE_RULE(startSymbol, L"", startSymbol, symbolStatement, symbolNewline);

    DECLARE_RULE(symbolNumber, L"{$$ = $2;}", symbolWS, symbolDigit);
    DECLARE_RULE(symbolNumber, L"{$$ = 10 * $1 + $2;}", symbolNumber, symbolDigit);

    DECLARE_RULE(symbolFactor, L"{$$ = $1;}", symbolNumber);
    DECLARE_RULE(symbolFactor, L"{$$ = -$3;}", symbolWS, symbolMinus, symbolFactor);
    DECLARE_RULE(symbolFactor, L"{$$ = $3;}", symbolWS, symbolLParen, symbolExpression, symbolWS, symbolRParen);

    DECLARE_RULE(symbolTerm, L"{$$ = $1;}", symbolFactor);
    DECLARE_RULE(symbolTerm, L"{if($4 == 0) {cout << \"divide by zero\\n\"; $$ = 0;} else $$ = $1 / $4;}", symbolTerm, symbolWS, symbolDivide, symbolFactor);
    DECLARE_RULE(symbolTerm, L"{$$ = $1 * $4;}", symbolTerm, symbolWS, symbolTimes, symbolFactor);

    DECLARE_RULE(symbolExpression, L"{$$ = $1;}", symbolTerm);
    DECLARE_RULE(symbolExpression, L"{$$ = $1 + $4;}", symbolExpression, symbolWS, symbolPlus, symbolTerm);
    DECLARE_RULE(symbolExpression, L"{$$ = $1 - $4;}", symbolExpression, symbolWS, symbolMinus, symbolTerm);

    calculateFirstSets(symbols, rules);

    ItemSet startSet;
    for(shared_ptr<Rule> rule : rules.match(startSymbol))
    {
        startSet.insert(Item(rule, 0, eofSymbol));
    }

    startSet = closure(startSet, rules);

    unordered_map<ItemSet, ItemSetProperties, ItemSetHasher, ItemSetCompare> canonicalCollection;
    vector<pair<ItemSet, ItemSetProperties>> canonicalSets;
    size_t nextSet = 0;
    canonicalSets.push_back(make_pair(startSet, ItemSetProperties(nextSet++)));
    canonicalCollection[startSet] = get<1>(canonicalSets.back());

    //cout << "Set " << nextSet << " : " << string_cast<string>(dumpItemSet(get<0>(canonicalSets.back()), formatting)) << endl << endl;

    for(size_t i = 0; i < canonicalSets.size(); i++)
    {
        for(shared_ptr<Symbol> symbol : symbols)
        {
            ItemSet newSet = calculateGoto(get<0>(canonicalSets[i]), symbol, rules);
            if(newSet.empty())
                continue;
            ItemSetProperties &properties = canonicalCollection[newSet];
            if(properties.index == NoIndex)
            {
                properties.index = nextSet++;
                canonicalSets.push_back(make_pair(newSet, properties));
                //cout << "Set " << nextSet << " : " << string_cast<string>(dumpItemSet(get<0>(canonicalSets.back()), formatting)) << endl << endl;
            }
            get<1>(canonicalSets[i]).gotoTable[symbol] = properties.index;
            //cout << "goto(" << (i + 1) << ", " << string_cast<string>(dumpSymbol(symbol, formatting)) << ") = " << (properties.index + 1) << endl << endl;
        }
    }

    vector<shared_ptr<Symbol>> terminalSymbols;
    unordered_map<shared_ptr<Symbol>, size_t> terminalSymbolMap;
    vector<shared_ptr<Symbol>> nonterminalSymbols;
    unordered_map<shared_ptr<Symbol>, size_t> nonterminalSymbolMap;

    terminalSymbolMap[eofSymbol] = terminalSymbols.size();
    terminalSymbols.push_back(eofSymbol); // eof must be first terminal
    nonterminalSymbolMap[startSymbol] = nonterminalSymbols.size();
    nonterminalSymbols.push_back(startSymbol); // start must be first nonterminal

    for(shared_ptr<Symbol> symbol : symbols)
    {
        if(symbol == eofSymbol || symbol == startSymbol)
            continue;
        if(symbol->isTerminal())
        {
            terminalSymbolMap[symbol] = terminalSymbols.size();
            terminalSymbols.push_back(symbol);
        }
        else
        {
            nonterminalSymbolMap[symbol] = nonterminalSymbols.size();
            nonterminalSymbols.push_back(symbol);
        }
    }

    vector<vector<unordered_set<ActionType>>> actionsTable;
    vector<vector<size_t>> gotoTable;
    actionsTable.resize(canonicalSets.size());
    gotoTable.resize(canonicalSets.size());
    bool anyConflicts = false;
    for(size_t state = 0; state < actionsTable.size(); state++)
    {
        vector<unordered_set<ActionType>> &actionsRow = actionsTable[state];
        vector<size_t> &gotoRow = gotoTable[state];
        actionsRow.resize(terminalSymbols.size());
        gotoRow.resize(nonterminalSymbols.size());
        for(const Item &item : get<0>(canonicalSets[state]))
        {
            if(item.currentLocation >= item.rule->rhs.size())
            {
                if(item.rule->lhs == startSymbol && item.lookahead == eofSymbol)
                {
                    actionsRow[terminalSymbolMap[item.lookahead]].insert(ActionType(item.rule, nonterminalSymbolMap[item.rule->lhs], true));
                }
                else
                {
                    actionsRow[terminalSymbolMap[item.lookahead]].insert(ActionType(item.rule, nonterminalSymbolMap[item.rule->lhs], false));
                }
            }
            else
            {
                shared_ptr<Symbol> nextSymbol = item.rule->rhs[item.currentLocation];
                if(nextSymbol->isTerminal())
                {
                    unordered_map<shared_ptr<Symbol>, size_t> &theGotoTable = get<1>(canonicalSets[state]).gotoTable;
                    actionsRow[terminalSymbolMap[nextSymbol]].insert(ActionType(theGotoTable[nextSymbol]));
                }
            }
        }
        for(size_t symbolIndex = 0; symbolIndex < terminalSymbols.size(); symbolIndex++)
        {
            if(actionsRow[symbolIndex].empty())
                actionsRow[symbolIndex].insert(ActionType());
            else if(actionsRow[symbolIndex].size() > 1)
            {
                cerr << "conflict on lookahead of " << string_cast<string>(dumpSymbol(terminalSymbols[symbolIndex], FormattingOptions())) << " : \n";
                for(ActionType action : actionsRow[symbolIndex])
                {
                    cerr << "    " << string_cast<string>(static_cast<wstring>(action)) << "\n";
                }
                anyConflicts = true;
            }
        }
        for(size_t symbolIndex = 0; symbolIndex < nonterminalSymbols.size(); symbolIndex++)
        {
            unordered_map<shared_ptr<Symbol>, size_t> &theGotoTable = get<1>(canonicalSets[state]).gotoTable;
            gotoRow[symbolIndex] = NoIndex;
            auto iter = theGotoTable.find(nonterminalSymbols[symbolIndex]);
            if(iter != theGotoTable.end())
                gotoRow[symbolIndex] = get<1>(*iter);
        }
    }
    if(anyConflicts)
        return 1;
    shared_ptr<ostream> pcout = shared_ptr<ostream>(&cout, [](ostream *){});
    FileWriter *writer = makeFileWriter(L"C++", "obj/out.cpp", "obj/out.h");
    writer->writePrologue(L"#include <iostream>\n\nusing std::cout;\ntypedef int ValueType;\n");
    writer->setTerminalList(terminalSymbols);
    writer->setNonterminalList(nonterminalSymbols);
    writer->setRules(rules);
    writer->startActionTable(canonicalSets.size());
    for(size_t state = 0; state < canonicalSets.size(); state++)
    {
        const vector<unordered_set<ActionType>> &actionsRow = actionsTable[state];
        writer->startActionState(state);
        for(size_t i = 0; i < terminalSymbols.size(); i++)
        {
            for(const ActionType &action : actionsRow[i])
            {
                action.write(writer, i);
            }
        }
        writer->endActionState();
    }
    writer->endActionTableAndStartGotoTable();
    for(size_t state = 0; state < canonicalSets.size(); state++)
    {
        const vector<size_t> &gotoRow = gotoTable[state];
        writer->startGotoState(state);
        for(size_t i = 0; i < nonterminalSymbols.size(); i++)
        {
            writer->writeGoto(i, gotoRow[i]);
        }
        writer->endGotoState();
    }
    writer->endGotoTable();
    writer->writeEpilogue(L"struct ParserImp : public MyParser\n{\n    virtual ValueType getToken()\n    {\n        return std::cin.get();\n    }\n};\nint main()\n{\n    ParserImp parser;\n    try\n    {\n        parser.parse();\n    }\n    catch(std::exception &e)\n    {\n        std::cerr << \"error : \" << e.what() << std::endl;\n    }\n}");
    delete writer;
    system("g++ -x c++ obj/out.cpp -o obj/out-test");
    return 0;
}