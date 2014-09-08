#include "file_writer.h"
#include <unordered_map>
#include <sstream>
#include <tuple>
#include <cwctype>
#include <fstream>
#include <stdexcept>
#include <cwctype>
#include "string_cast.h"

using namespace std;

namespace
{
wstring getOption(wstring optionName, wstring optionDefault, const unordered_map<wstring, wstring> &options)
{
    auto iter = options.find(optionName);
    if(iter == options.end())
        return optionDefault;
    return get<1>(*iter);
}

wstring getOptionCppIdentifier(wstring optionName, wstring optionDefault, const unordered_map<wstring, wstring> &options)
{
    wstring retval = getOption(optionName, optionDefault, options);
    if(retval == L"")
        throw runtime_error("missing value for %option " + string_cast<string>(optionName) + " : must be valid C++ identifier");
    if(!iswalpha(retval[0]) && retval[0] != '_')
        throw runtime_error("invalid value for %option " + string_cast<string>(optionName) + " : must be valid C++ identifier");
    for(wchar_t ch : retval)
    {
        if(!iswalnum(ch) && ch != '_')
            throw runtime_error("invalid value for %option " + string_cast<string>(optionName) + " : must be valid C++ identifier");
    }
    return retval;
}

wstring getOptionCppIdentifierPrefix(wstring optionName, wstring optionDefault, const unordered_map<wstring, wstring> &options)
{
    wstring retval = getOption(optionName, optionDefault, options);
    if(retval == L"")
        return retval;
    if(!iswalpha(retval[0]) && retval[0] != '_' && retval[0] != ':')
        throw runtime_error("invalid value for %option " + string_cast<string>(optionName) + " : must be valid scoped C++ identifier");
    int colonCount = 0;
    for(wchar_t ch : retval)
    {
        if(ch == ':')
        {
            colonCount++;
            continue;
        }
        if((colonCount != 0 && colonCount != 2) || (!iswalnum(ch) && ch != '_'))
            throw runtime_error("invalid value for %option " + string_cast<string>(optionName) + " : must be valid scoped C++ identifier");
        colonCount = 0;
    }
    if(colonCount != 0 && colonCount != 2)
        throw runtime_error("invalid value for %option " + string_cast<string>(optionName) + " : must be valid scoped C++ identifier");
    return retval;
}

bool getOptionBoolean(wstring optionName, bool optionDefault, const unordered_map<wstring, wstring> &options)
{
    wstring v = getOption(optionName, (optionDefault ? L"true" : L"false"), options);
    if(v == L"true" || v == L"yes" || v == L"on" || v == L"")
        return true;
    if(v == L"false" || v == L"no" || v == L"off")
        return false;
    throw runtime_error("invalid value for %option " + string_cast<string>(optionName) + " : use true, false, yes, no, on, or off");
}

class ofilter_streambuf : public streambuf
{
    unique_ptr<ostream> output;
public:
    explicit ofilter_streambuf(unique_ptr<ostream> output)
        : output(std::move(output))
    {
    }
protected:
    virtual int filter(int ch) = 0;
    virtual int overflow(int ch = EOF) override
    {
        if(ch == EOF)
        {
            return ch;
        }
        int v = filter(ch);
        while(v != EOF)
        {
            output->put(v);
            v = filter(EOF);
        }
        if(*output)
            return ch;
        return EOF;
    }
    virtual int sync() override
    {
        output->flush();
        if(*output)
            return 0;
        return -1;
    }
};

class oline_counting_streambuf : public ofilter_streambuf
{
    size_t currentLine = 1;
public:
    oline_counting_streambuf(unique_ptr<ostream> output)
        : ofilter_streambuf(std::move(output))
    {
    }
    size_t getLineNumber() const
    {
        return currentLine;
    }
protected:
    virtual int filter(int ch) override
    {
        if(ch == '\n')
            currentLine++;
        return ch;
    }
};

class oline_counting_stream : public ostream
{
    unique_ptr<oline_counting_streambuf> sb;
    explicit oline_counting_stream(unique_ptr<oline_counting_streambuf> sb)
        : ostream(sb.get())
    {
        this->sb = std::move(sb);
    }
public:
    explicit oline_counting_stream(unique_ptr<ostream> output)
        : oline_counting_stream(unique_ptr<oline_counting_streambuf>(new oline_counting_streambuf(std::move(output))))
    {
    }
    size_t getLineNumber() const
    {
        return sb->getLineNumber();
    }
};

class CPlusPlusFileWriter : public FileWriter
{
    oline_counting_stream os, os2;
    string valueTypeName, parseClassName, nullString, sourceFileName, headerFileName, inputFileName, terminalSymbolPrefix;
    size_t indentAmount = 4;
    string indent(size_t amount)
    {
        amount *= indentAmount;
        return string(amount, ' ');
    }
    bool gotTerminalList = false, gotNonterminalList = false;
    vector<gc_pointer<Symbol>> terminals;
    vector<gc_pointer<Symbol>> nonterminals;
    unordered_map<gc_pointer<Rule>, size_t> ruleNumbers;
    vector<gc_pointer<Rule>> rules;
    string prologue;
    size_t stateCount;
    bool useCpp11 = false;
    static wstring getCharacterLiteral(unsigned value)
    {
        wostringstream ss;
        if(value >= 0x10000)
        {
            ss << L"\\U";
            ss.fill(L'0');
            ss.width(8);
            ss << hex << value;
        }
        else if(value >= 0x80)
        {
            ss << L"\\u";
            ss.fill(L'0');
            ss.width(4);
            ss << hex << value;
        }
        else if(value == 0x7F)
        {
            ss << L"\\x7F";
        }
        else if(value < 0x20)
        {
            switch(value)
            {
            case '\a':
                ss << L"\\a";
                break;
            case '\b':
                ss << L"\\b";
                break;
            case '\f':
                ss << L"\\f";
                break;
            case '\n':
                ss << L"\\n";
                break;
            case '\r':
                ss << L"\\r";
                break;
            case '\t':
                ss << L"\\t";
                break;
            case '\v':
                ss << L"\\v";
                break;
            default:
                ss << L"\\x";
                ss.fill(L'0');
                ss.width(2);
                ss << hex << value;
                break;
            }
        }
        else
        {
            switch(value)
            {
            case '\"':
            case '\'':
            case '\\':
                ss << L"\\" << (wchar_t)value;
                break;
            default:
                ss << (wchar_t)value;
            }
        }
        return ss.str();
    }
    static wstring escapeString(wstring str)
    {
        wstring retval = L"";
        for(size_t i = 0; i < str.size(); i++)
        {
            unsigned value = str[i];
            if(value >= 0xD800U && value <= 0xDBFFU && i + 1 < str.size())
            {
                unsigned nextValue = str[i + 1];
                if(nextValue >= 0xDC00U && nextValue <= 0xDFFFU)
                {
                    i++;
                    value -= 0xD800U;
                    nextValue -= 0xDC00U;
                    value <<= 10;
                    value += nextValue;
                }
            }
            retval += getCharacterLiteral(value);
        }
        return retval;
    }
    static string escapeString(string str)
    {
        return string_cast<string>(escapeString(string_cast<wstring>(str)));
    }
    wstring getRuleName(gc_pointer<Rule> rule)
    {
        wostringstream ss;
        ss << L"reduce_to_";
        for(wchar_t ch : rule->lhs->name)
        {
            if(iswalnum(ch) || ch == '_')
                ss << ch;
            else
                ss << L"_";
        }
        ss << L"_" << ruleNumbers[rule];
        return ss.str();
    }
    string getHeaderGuardName()
    {
        ostringstream ss;
        ss << "PARSER_";
        for(char ch : headerFileName)
        {
            if(isalnum(ch))
                ss << (char)toupper(ch);
            else
                ss << '_';
        }
        return ss.str();
    }
    static void writeLineDirective(string fileName, oline_counting_stream &os)
    {
        size_t line = os.getLineNumber() + 1;
        os << "#line " << line << " \"" << escapeString(fileName) << "\"\n";
    }
    void writeParseFunctions()
    {
        string enumPrefix = "";
        if(useCpp11)
            enumPrefix = "ActionType::";
        os << "size_t " << parseClassName << "::translateToken(const " << valueTypeName << " &tok)\n";
        os << "{\n";
        os << indent(1) << "for(size_t i = 0; i < sizeof(terminalsTable) / sizeof(terminalsTable[0]); i++)\n";
        os << indent(1) << "{\n";
        os << indent(2) << "if(terminalsTable[i] == tok)\n";
        os << indent(3) << "return i;\n";
        os << indent(1) << "}\n";
        os << indent(1) << "handleError(\"unknown token\");\n";
        os << indent(1) << "return 0;\n";
        os << "}\n";
        os << valueTypeName << " " << parseClassName << "::parse()\n";
        os << "{\n";
        os << indent(1) << valueTypeName << " token = getToken();\n";
        os << indent(1) << "size_t ttok = translateToken(token);\n";
        os << indent(1) << "theStack.assign(1, ElementType(0, terminalsTable[0]));\n";
        os << "\n";
        os << indent(1) << "for(;;)\n";
        os << indent(1) << "{\n";
        os << indent(2) << "size_t state = theStack.back().state;\n";
        os << indent(2) << "switch(actionTable[state][ttok].type)\n";
        os << indent(2) << "{\n";
        os << indent(2) << "case " << enumPrefix << "Shift:\n";
        os << indent(3) << "theStack.push_back(ElementType(actionTable[state][ttok].nextState, token));\n";
        os << indent(3) << "token = getToken();\n";
        os << indent(3) << "ttok = translateToken(token);\n";
        os << indent(3) << "break;\n";
        os << indent(2) << "case " << enumPrefix << "Accept:\n";
        os << indent(3) << "return (this->*actionTable[state][ttok].reduceFn)(token);\n";
        os << indent(2) << "case " << enumPrefix << "Reduce:\n";
        os << indent(2) << "{\n";
        os << indent(3) << valueTypeName << " value = (this->*actionTable[state][ttok].reduceFn)(token);\n";
        os << indent(3) << "ttok = translateToken(token);\n";
        os << indent(3) << "theStack.erase(theStack.begin() + (theStack.size() - actionTable[state][ttok].popCount), theStack.end());\n";
        os << indent(3) << "size_t symbol = actionTable[state][ttok].nextState;\n";
        os << indent(3) << "state = theStack.back().state;\n";
        os << indent(3) << "theStack.push_back(ElementType(gotoTable[state][symbol], value));\n";
        os << indent(3) << "break;\n";
        os << indent(2) << "}\n";
        os << indent(2) << "default:\n";
        os << indent(3) << "handleError(\"unexpected token\");\n";
        os << indent(3) << "return terminalsTable[0];\n";
        os << indent(2) << "}\n";
        os << indent(1) << "}\n";
        os << "}\n";
    }
    void onGotSymbols()
    {
        os << "// This is a automatically generated file : DO NOT MODIFY\n// This file is generated from '" << inputFileName << "'\n";
        os << "#include \"" << escapeString(headerFileName) << "\"\n";
        os2 << "// This is a automatically generated file : DO NOT MODIFY\n// This file is generated from '" << inputFileName << "'\n";
        os2 << "#ifndef " << getHeaderGuardName() << "\n";
        os2 << "#define " << getHeaderGuardName() << "\n";
        os2 << prologue << "\n";
        writeLineDirective(headerFileName, os2);
        os2 << "#include <vector>\n";
        os2 << "#include <string>\n";
        os2 << "#include <stdexcept>\n";
        os2 << "#include <cstdio> // for EOF\n";
        os2 << "\n";
        os2 << "class " << parseClassName << "\n";
        os2 << "{\n";
        os2 << "public:\n";
        os2 << indent(1) << "struct ParseError : public std::runtime_error\n";
        os2 << indent(1) << "{\n";
        os2 << indent(2) << "explicit ParseError(const std::string &msg)" << (useCpp11 ? " noexcept" : "") << "\n";
        os2 << indent(3) << ": runtime_error(msg)\n";
        os2 << indent(2) << "{\n";
        os2 << indent(2) << "}\n";
        os2 << indent(1) << "};\n";
        os2 << "private:\n";
        os2 << indent(1) << "struct ElementType\n";
        os2 << indent(1) << "{\n";
        os2 << indent(2) << "size_t state;\n";
        os2 << indent(2) << valueTypeName << " value;\n";
        os2 << indent(2) << "ElementType(size_t state, " << valueTypeName << " value)\n";
        os2 << indent(3) << ": state(state), value(value)\n";
        os2 << indent(2) << "{\n";
        os2 << indent(2) << "}\n";
        os2 << indent(1) << "};\n";
        os2 << indent(1) << "std::vector<ElementType> theStack;\n";
        os2 << indent(1) << "static " << (useCpp11 ? "constexpr" : "const") << " size_t ErrorState = ~(size_t)0;\n";
        os2 << indent(1) << (useCpp11 ? "enum class" : "enum") << " ActionType\n";
        os2 << indent(1) << "{\n";
        os2 << indent(2) << "Shift,\n";
        os2 << indent(2) << "Reduce,\n";
        os2 << indent(2) << "Accept,\n";
        os2 << indent(2) << "Error\n";
        os2 << indent(1) << "};\n";
        os2 << indent(1) << "struct ActionEntry\n";
        os2 << indent(1) << "{\n";
        os2 << indent(2) << "ActionType type;\n";
        os2 << indent(2) << "size_t nextState;\n";
        os2 << indent(2) << valueTypeName << " (" << parseClassName << "::*reduceFn)(" << valueTypeName << " &peekToken);\n";
        os2 << indent(2) << "size_t popCount;\n";
        os2 << indent(1) << "};\n";
    }
public:
    CPlusPlusFileWriter(unique_ptr<ostream> stream, unique_ptr<ostream> stream2, string sourceFileName, string headerFileName, const unordered_map<wstring, wstring> &options, string inputFileName)
        : os(std::move(stream)), os2(std::move(stream2)), valueTypeName(string_cast<string>(getOptionCppIdentifier(L"ValueType", L"ValueType", options))), parseClassName(string_cast<string>(getOptionCppIdentifier(L"ClassName", L"MyParser", options))), nullString("NULL"), sourceFileName(sourceFileName), headerFileName(headerFileName)
    {
        this->inputFileName = inputFileName;
        if(getOptionBoolean(L"UseC++11", false, options))
        {
            nullString = "nullptr";
            useCpp11 = true;
        }
        terminalSymbolPrefix = string_cast<string>(getOptionCppIdentifierPrefix(L"SymbolPrefix", L"", options));
    }
    virtual ~CPlusPlusFileWriter()
    {
    }
    static constexpr const wchar_t *const language = L"C++";
    virtual wstring getLanguage() const override
    {
        return language;
    }
    virtual void writePrologue(unordered_multimap<wstring, CodeSection> code) override
    {
        prologue = "";
        for(auto v : code)
        {
            const CodeSection &codeSection = std::get<1>(v);
            if(std::get<0>(v) == L"")
            {
                if(codeSection.empty())
                    continue;
                prologue += "\n" + string_cast<string>(codeSection.location.getCLineDirective() + codeSection.code) + "\n";
            }
            else
                throw runtime_error("invalid code section name : " + string_cast<string>(std::get<0>(v)));
        }
    }
    virtual void writeEpilogue(unordered_multimap<wstring, CodeSection> code) override
    {
        for(auto v : code)
        {
            const CodeSection &codeSection = std::get<1>(v);
            if(std::get<0>(v) == L"")
            {
                if(codeSection.empty())
                    continue;
                os << endl << string_cast<string>(codeSection.location.getCLineDirective() + codeSection.code) << endl;
            }
            else
                throw runtime_error("invalid code section name : " + string_cast<string>(std::get<0>(v)));
        }
    }
    virtual void setTerminalList(vector<gc_pointer<Symbol>> terminals) override
    {
        this->terminals = terminals;
        gotTerminalList = true;
        if(gotNonterminalList)
            onGotSymbols();
    }
    virtual void setNonterminalList(vector<gc_pointer<Symbol>> nonterminals) override
    {
        this->nonterminals = nonterminals;
        gotNonterminalList = true;
        if(gotTerminalList)
            onGotSymbols();
    }
    virtual void setRules(const RuleSet &rules) override
    {
        this->rules.reserve(rules.size());
        for(gc_pointer<Rule> rule : rules)
        {
            ruleNumbers[rule] = this->rules.size();
            this->rules.push_back(rule);
        }
    }
    virtual void startActionTable(size_t stateCount) override
    {
        this->stateCount = stateCount;
        os2 << indent(1) << "static const ActionEntry actionTable[" << stateCount << "][" << terminals.size() << "];\n";
        os2 << indent(1) << "static const size_t gotoTable[" << stateCount << "][" << nonterminals.size() << "];\n";
        os2 << indent(1) << "static const " << valueTypeName << " terminalsTable[" << terminals.size() << "];\n";
        for(gc_pointer<Rule> rule : rules)
        {
            os2 << indent(1) << valueTypeName << " " << string_cast<string>(getRuleName(rule)) << "(" << valueTypeName << " &peekToken);\n";
        }
        os2 << indent(1) << "size_t translateToken(const " << valueTypeName << " &tok);\n";
        os2 << "public:\n";
        os2 << indent(1) << "virtual ~" << parseClassName << "()\n";
        os2 << indent(1) << "{\n";
        os2 << indent(1) << "}\n";
        os2 << indent(1) << valueTypeName << " parse();\n";
        os2 << "protected:\n";
        os2 << indent(1) << "virtual " << valueTypeName << " getToken() = 0;\n";
        os2 << indent(1) << "virtual void handleError(const std::string &msg)\n";
        os2 << indent(1) << "{\n";
        os2 << indent(2) << "throw ParseError(msg);\n";
        os2 << indent(1) << "}\n";
        os2 << "};\n";
        os2 << "#endif\n";
        for(gc_pointer<Rule> rule : rules)
        {
            os << valueTypeName << " " << parseClassName << "::" << string_cast<string>(getRuleName(rule)) << "(" << valueTypeName << " &peekToken)\n";
            os << "{\n";
            os << indent(1) << valueTypeName << " dollar_dollar;\n";
            os << indent(1) << string_cast<string>(rule->substituteCPlusPlusCode([&](int index)
            {
                wostringstream ss;
                ss << L"(this->theStack[this->theStack.size() - " << (rule->rhs.size() - index + 1) << "].value)";
                return ss.str();
            }, L"dollar_dollar")) << "\n";
            writeLineDirective(sourceFileName, os);
            os << indent(1) << "return dollar_dollar;\n";
            os << "}\n";
        }
        os << "const " << valueTypeName << " " << parseClassName << "::terminalsTable[" << terminals.size() << "] =\n";
        os << "{\n";
        for(size_t i = 0; i < terminals.size(); i++)
        {
            os << indent(1) << valueTypeName << "(" << (terminals[i]->name.substr(0, 1) == L"\'" ? "" : terminalSymbolPrefix) << string_cast<string>(terminals[i]->name) << "),\n";
        }
        os << "};\n";
        os << "const " << parseClassName << "::ActionEntry " << parseClassName << "::actionTable[" << stateCount << "][" << terminals.size() << "] =\n";
        os << "{\n";
    }
    virtual void endActionTableAndStartGotoTable() override
    {
        os << "};\n";
        os << "const size_t " << parseClassName << "::gotoTable[" << stateCount << "][" << nonterminals.size() << "] =\n";
        os << "{\n";
    }
    virtual void endGotoTable() override
    {
        os << "};\n";
        writeParseFunctions();
    }
    virtual void startActionState(size_t state) override
    {
        os << indent(1) << "{ // state " << state << "\n";
    }
    virtual void endActionState() override
    {
        os << indent(1) << "},\n";
    }
    virtual void startGotoState(size_t state) override
    {
        os << indent(1) << "{ // state " << state << "\n";
    }
    virtual void endGotoState() override
    {
        os << indent(1) << "},\n";
    }
    virtual void writeGoto(size_t nonterminalIndex, size_t newState) override
    {
        if(newState == ~(size_t)0)
            os << indent(2) << parseClassName << "::ErrorState,\n";
        else
            os << indent(2) << newState << ",\n";
    }
    virtual void writeErrorAction(size_t lookahead) override
    {
        string enumPrefix = parseClassName + "::";
        if(useCpp11)
            enumPrefix += "ActionType::";
        os << indent(2) << "{" << enumPrefix << "Error, 0, " << nullString << ", 0},\n";
    }
    virtual void writeReduceAction(gc_pointer<Rule> rule, size_t nonterminalIndex, size_t lookahead) override
    {
        string enumPrefix = parseClassName + "::";
        if(useCpp11)
            enumPrefix += "ActionType::";
        os << indent(2) << "{" << enumPrefix << "Reduce, " << nonterminalIndex << ", &" << parseClassName << "::" << string_cast<string>(getRuleName(rule)) << ", " << rule->rhs.size() << "},\n";
    }
    virtual void writeAcceptAction(gc_pointer<Rule> rule, size_t nonterminalIndex, size_t lookahead) override
    {
        string enumPrefix = parseClassName + "::";
        if(useCpp11)
            enumPrefix += "ActionType::";
        os << indent(2) << "{" << enumPrefix << "Accept, " << nonterminalIndex << ", &" << parseClassName << "::" << string_cast<string>(getRuleName(rule)) << ", " << rule->rhs.size() << "},\n";
    }
    virtual void writeShiftAction(size_t newState, size_t lookahead) override
    {
        string enumPrefix = parseClassName + "::";
        if(useCpp11)
            enumPrefix += "ActionType::";
        os << indent(2) << "{" << enumPrefix << "Shift, " << newState << ", " << nullString << ", 0},\n";
    }
};

vector<string> decomposePath(string path)
{
    vector<string> retval;
    bool haveAnything = true;
    retval.push_back("");
    for(char ch : path)
    {
        if(ch == '/' || ch == '\\')
        {
            haveAnything = false;
        }
        else
        {
            if(!haveAnything)
            {
                retval.push_back("");
            }
            retval.back() += ch;
            haveAnything = true;
        }
    }
    return retval;
}

string getRelativeName(string startFile, string destFile)
{
    vector<string> startPath = decomposePath(startFile);
    vector<string> destPath = decomposePath(destFile);
    if(startPath.front() == ".")
        startPath.erase(startPath.begin(), startPath.begin() + 1);
    if(destPath.front() == ".")
        destPath.erase(destPath.begin(), destPath.begin() + 1);
    for(size_t i = 1; i < startPath.size(); i++)
    {
        while(i < startPath.size() && i >= 1 && startPath[i] == ".." && startPath[i - 1] != "." && startPath[i - 1] != "..")
        {
            startPath.erase(startPath.begin() + i - 1, startPath.begin() + i + 1);
            i--;
        }
    }
    for(size_t i = 1; i < destPath.size(); i++)
    {
        while(i < destPath.size() && i >= 1 && destPath[i] == ".." && destPath[i - 1] != "." && destPath[i - 1] != "..")
        {
            destPath.erase(destPath.begin() + i - 1, destPath.begin() + i + 1);
            i--;
        }
    }
    while(startPath.size() > 1 && destPath.size() > 1 && startPath.front() == destPath.front())
    {
        startPath.erase(startPath.begin(), startPath.begin() + 1);
        destPath.erase(destPath.begin(), destPath.begin() + 1);
    }
    string retval = "", seperator = "";
    for(string s : destPath)
    {
        retval += seperator;
        retval += s;
        seperator = "/";
    }
    for(size_t i = 1; i < startPath.size(); i++)
    {
        retval = "../" + retval;
    }
    return retval;
}
}

FileWriter *makeFileWriter(wstring language, string inputFileName, unordered_map<wstring, wstring> options)
{
    string fileName, headerName;
    if(language == CPlusPlusFileWriter::language)
    {
        fileName = inputFileName + ".cpp";
        fileName = string_cast<string>(getOption(L"OutputFile", string_cast<wstring>(fileName), options));
        string baseFileName = fileName;
        size_t lastPeriodPosition = baseFileName.find_last_of("./\\");
        if(lastPeriodPosition != string::npos && baseFileName[lastPeriodPosition] == '.')
            baseFileName.erase(lastPeriodPosition);
        headerName = baseFileName + ".h";
        headerName = string_cast<string>(getOption(L"HeaderFile", string_cast<wstring>(headerName), options));
        unique_ptr<ofstream> outputFile = unique_ptr<ofstream>(new ofstream(fileName));
        if(!*outputFile)
            throw runtime_error("can't open output source file '" + fileName + "'");
        unique_ptr<ofstream> headerFile = unique_ptr<ofstream>(new ofstream(headerName));
        if(!*headerFile)
            throw runtime_error("can't open output header file '" + headerName + "'");
        return new CPlusPlusFileWriter(std::move(outputFile), std::move(headerFile), getRelativeName(fileName, fileName), getRelativeName(fileName, headerName), options, inputFileName);
    }
    throw runtime_error("unknown output language");
}