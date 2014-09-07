#ifndef FILE_WRITER_H_INCLUDED
#define FILE_WRITER_H_INCLUDED

#include <ostream>
#include <vector>
#include <memory>
#include "gc.h"
#include <cwchar>
#include <string>
#include <unordered_map>
#include "rule.h"
#include "symbol.h"

using namespace std;

class FileWriter
{
    FileWriter(const FileWriter &) = delete;
    void operator =(const FileWriter &) = delete;
protected:
    gc_pointer<ostream> stream;
    ostream &os;
public:
    FileWriter(gc_pointer<ostream> stream)
        : stream(stream), os(*stream)
    {
    }
    virtual ~FileWriter()
    {
    }
    virtual wstring getLanguage() const = 0;
    virtual void writePrologue(unordered_multimap<wstring, CodeSection> code) = 0;
    virtual void writeEpilogue(unordered_multimap<wstring, CodeSection> code) = 0;
    virtual void setTerminalList(vector<gc_pointer<Symbol>> terminals) = 0;
    virtual void setNonterminalList(vector<gc_pointer<Symbol>> nonterminals) = 0;
    virtual void setRules(const RuleSet &rules) = 0;
    virtual void startActionTable(size_t stateCount) = 0;
    virtual void endActionTableAndStartGotoTable() = 0;
    virtual void endGotoTable() = 0;
    virtual void startActionState(size_t state) = 0;
    virtual void endActionState() = 0;
    virtual void startGotoState(size_t state) = 0;
    virtual void endGotoState() = 0;
    virtual void writeGoto(size_t nonterminalIndex, size_t newState) = 0;
    virtual void writeErrorAction(size_t lookahead) = 0;
    virtual void writeReduceAction(gc_pointer<Rule> rule, size_t nonterminalIndex, size_t lookahead) = 0;
    virtual void writeAcceptAction(gc_pointer<Rule> rule, size_t nonterminalIndex, size_t lookahead) = 0;
    virtual void writeShiftAction(size_t newState, size_t lookahead) = 0;
};

FileWriter *makeFileWriter(wstring language, string inputFileName, unordered_map<wstring, wstring> options = unordered_map<wstring, wstring>());

#endif // FILE_WRITER_H_INCLUDED
