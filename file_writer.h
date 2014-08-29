#ifndef FILE_WRITER_H_INCLUDED
#define FILE_WRITER_H_INCLUDED

#include <ostream>
#include <vector>
#include <memory>
#include <cwchar>
#include <string>
#include "rule.h"
#include "symbol.h"

using namespace std;

class FileWriter
{
    FileWriter(const FileWriter &) = delete;
    void operator =(const FileWriter &) = delete;
protected:
    shared_ptr<ostream> stream;
    ostream &os;
public:
    FileWriter(shared_ptr<ostream> stream)
        : stream(stream), os(*stream)
    {
    }
    virtual ~FileWriter()
    {
    }
    virtual wstring getLanguage() const = 0;
    virtual void writePrologue(wstring code) = 0;
    virtual void writeEpilogue(wstring code) = 0;
    virtual void setTerminalList(vector<shared_ptr<Symbol>> terminals) = 0;
    virtual void setNonterminalList(vector<shared_ptr<Symbol>> nonterminals) = 0;
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
    virtual void writeReduceAction(shared_ptr<Rule> rule, size_t nonterminalIndex, size_t lookahead) = 0;
    virtual void writeAcceptAction(shared_ptr<Rule> rule, size_t nonterminalIndex, size_t lookahead) = 0;
    virtual void writeShiftAction(size_t newState, size_t lookahead) = 0;
};

FileWriter *makeFileWriter(wstring language, shared_ptr<ostream> os);

#endif // FILE_WRITER_H_INCLUDED
