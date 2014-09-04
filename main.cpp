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
#include <cwctype>
#include <stdexcept>
#include "symbol.h"
#include "rule.h"
#include "item.h"
#include "generate.h"
#include "string_cast.h"
#include "dump.h"
#include "file_writer.h"
#include "location.h"

using namespace std;

enum class TokenType
{
    EndOfFile,
    EndOfLine,
    CodeSection,
    Colon,
    Pipe,
    Semicolon,
    Identifier,
    DoublePercent,
    PercentIdentifier,
    Character,
    String,
};

struct Token
{
    Location location;
    TokenType type;
    wstring value;
    Token(Location location = Location(L""), TokenType type = TokenType::EndOfFile, wstring value = L"")
        : location(location), type(type), value(value)
    {
    }
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
    wstring makeCharacterLiteral() const
    {
        wstring retval = L"\'";
        for(size_t i = 0; i < value.size(); i++)
        {
            unsigned value = this->value[i];
            if(value >= 0xD800U && value <= 0xDBFFU && i + 1 < this->value.size())
            {
                unsigned nextValue = this->value[i + 1];
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
        retval += L"\'";
        return retval;
    }
    wstring makeStringLiteral() const
    {
        wstring retval = L"\"";
        for(size_t i = 0; i < value.size(); i++)
        {
            unsigned value = this->value[i];
            if(value >= 0xD800U && value <= 0xDBFFU && i + 1 < this->value.size())
            {
                unsigned nextValue = this->value[i + 1];
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
        retval += L"\"";
        return retval;
    }
    vector<wstring> makeCharacterLiterals() const
    {
        vector<wstring> retval;
        for(size_t i = 0; i < value.size(); i++)
        {
            unsigned value = this->value[i];
            if(value >= 0xD800U && value <= 0xDBFFU && i + 1 < this->value.size())
            {
                unsigned nextValue = this->value[i + 1];
                if(nextValue >= 0xDC00U && nextValue <= 0xDFFFU)
                {
                    i++;
                    value -= 0xD800U;
                    nextValue -= 0xDC00U;
                    value <<= 10;
                    value += nextValue;
                }
            }
            retval.push_back(L"\'" + getCharacterLiteral(value) + L"\'");
        }
        return std::move(retval);
    }
};

string loadAll(istream &is)
{
    string retval;
    constexpr size_t readChunkSize = 4096;
    char buffer[readChunkSize];
    while(is.read(buffer, readChunkSize))
    {
        retval.append(buffer, readChunkSize);
    }
    retval.append(buffer, is.gcount());
    return std::move(retval);
}

struct ParseError : public runtime_error
{
    Location location;
    wstring msg;
    explicit ParseError(wstring msg)
        : runtime_error(string_cast<string>(msg)), location(L""), msg(msg)
    {
    }
    ParseError(Location location, wstring msg)
        : ParseError(static_cast<wstring>(location) + L" : " + msg)
    {
        this->location = location;
    }
};

class Tokenizer
{
    const wstring input;
    size_t inputPosition = 0;
    Location location;
    wint_t peek() const
    {
        if(inputPosition >= input.size())
            return WEOF;
        wchar_t ch = input[inputPosition];
        if(ch == '\r')
            ch = '\n';
        return ch;
    }
    void next()
    {
        if(inputPosition < input.size())
        {
            wchar_t ch = input[inputPosition++];
            if(ch == '\r')
            {
                location.line++;
                location.column = 1;
                if(inputPosition < input.size() && input[inputPosition] == '\n')
                    inputPosition++;
            }
            else if(ch == '\n')
            {
                location.line++;
                location.column = 1;
            }
            else if(ch == '\t')
            {
                constexpr size_t tabWidth = 4;
                size_t x = location.column;
                x--;
                x -= x % tabWidth;
                x += tabWidth;
                x++;
                location.column = x;
            }
            else
                location.column++;
        }
    }
    void skipWhiteSpace()
    {
        while(iswblank(peek()))
        {
            next();
        }
    }
    void readStringEscape()
    {
        assert(peek() == '\\');
        next();
        switch(peek())
        {
        case WEOF:
        case '\n':
            throw ParseError(location, L"missing rest of escape sequence");
        case '\'':
        case '\\':
        case '\"':
            token.value += peek();
            next();
            break;
        case 'a':
            token.value += L'\a';
            next();
            break;
        case 'b':
            token.value += L'\b';
            next();
            break;
        case 'f':
            token.value += L'\f';
            next();
            break;
        case 'n':
            token.value += L'\n';
            next();
            break;
        case 'r':
            token.value += L'\r';
            next();
            break;
        case 't':
            token.value += L'\t';
            next();
            break;
        case 'v':
            token.value += L'\v';
            next();
            break;
        case '0':
            token.value += L'\0';
            next();
            break;
        case 'x':
        case 'u':
        case 'U':
        {
            unsigned value = 0;
            size_t digitCount = 2;
            if(peek() == 'u')
                digitCount = 4;
            else if(peek() == 'U')
                digitCount = 8;
            next();
            for(size_t i = 0; i < digitCount; i++)
            {
                if(!iswxdigit(peek()))
                    throw ParseError(location, L"missing hexadecimal digit in escape sequence");
                value *= 0x10;
                if(iswdigit(peek()))
                    value += peek() - '0';
                else if(iswlower(peek()))
                    value += peek() - 'a' + 0xA;
                else
                    value += peek() - 'A' + 0xA;
                if(value > 0x10FFFF)
                    throw ParseError(location, L"unicode literal out of range");
                next();
            }
            wchar_t ch = value;
            if((unsigned)ch != value)
            {
                value -= 0x10000;
                token.value += (wchar_t)((value >> 10) + 0xD800);
                token.value += (wchar_t)((value & 0x3FF) + 0xDC00);
            }
            else
                token.value += ch;
            if(token.value.size() >= 2)
            {
                unsigned ch1, ch2;
                ch1 = token.value[token.value.size() - 2];
                ch2 = token.value[token.value.size() - 1];
                if(ch1 >= 0xD800U && ch1 < 0xDC00U && ch2 >= 0xDC00U && ch2 < 0xE000U)
                {
                    ch1 &= 0x3FFU;
                    ch2 &= 0x3FFU;
                    ch = (ch1 << 10) + ch2;
                    if((unsigned)ch == (ch1 << 10) + ch2)
                    {
                        token.value.erase(token.value.size() - 2);
                        token.value += ch;
                    }
                }
            }
            break;
        }
        default:
            throw ParseError(location, L"invalid escape sequence");
        }
    }
public:
    Tokenizer(wstring fileName, wstring input)
        : input(std::move(input)), location(fileName, 1, 1)
    {
        nextToken();
    }
    Tokenizer(wstring fileName, istream &is)
        : input(string_cast<wstring>(loadAll(is))), location(fileName, 1, 1)
    {
        nextToken();
    }
    Token token;
    void nextToken()
    {
        for(;;)
        {
            skipWhiteSpace();
            token = Token(location);
            if(peek() == WEOF)
            {
                token.type = TokenType::EndOfFile;
                return;
            }
            if(peek() == '\n')
            {
                token.type = TokenType::EndOfLine;
                next();
                return;
            }
            if(iswalpha(peek()) || peek() == '_')
            {
                token.type = TokenType::Identifier;
                while(iswalnum(peek()) || peek() == '_')
                {
                    token.value += peek();
                    next();
                }
                return;
            }
            if(peek() == '\'')
            {
                token.type = TokenType::Character;
                next();
                if(peek() == '\\')
                    readStringEscape();
                else if(peek() == '\'')
                    throw ParseError(location, L"empty character literal not allowed");
                else if(peek() == WEOF || peek() == '\n')
                    throw ParseError(location, L"missing closing single quote");
                else
                {
                    token.value += peek();
                    next();
                }
                if(peek() != '\'')
                    throw ParseError(location, L"expected closing single quote");
                next();
                return;
            }
            if(peek() == '\"')
            {
                token.type = TokenType::String;
                next();
                while(peek() != '\"' && peek() != WEOF && peek() != '\n')
                {
                    if(peek() == '\\')
                        readStringEscape();
                    else
                    {
                        token.value += peek();
                        next();
                    }
                }
                if(peek() != '\"')
                    throw ParseError(location, L"expected closing double quote");
                next();
                return;
            }
            if(peek() == '%')
            {
                token.value += peek();
                next();
                if(iswalpha(peek()) || peek() == '_')
                {
                    token.type = TokenType::PercentIdentifier;
                    while(iswalnum(peek()) || peek() == '_')
                    {
                        token.value += peek();
                        next();
                    }
                    return;
                }
                else if(peek() == '%')
                {
                    token.type = TokenType::DoublePercent;
                    token.value += peek();
                    next();
                    return;
                }
                else if(peek() == '{')
                {
                    token.type = TokenType::CodeSection;
                    token.value = L"";
                    next();
                    while(peek() != WEOF)
                    {
                        if(peek() == '%')
                        {
                            next();
                            while(peek() == '%')
                            {
                                token.value += L'%';
                                next();
                            }
                            if(peek() == '}')
                            {
                                next();
                                return;
                            }
                            else
                            {
                                token.value += L'%';
                            }
                        }
                        else
                        {
                            token.value += peek();
                            next();
                        }
                    }
                    throw ParseError(location, L"expected closing %}");
                }
                else
                    throw ParseError(location, L"unexpected %");
            }
            if(peek() == '{')
            {
                size_t braceNestLevel = 1;
                wint_t quoteCharacter = WEOF;
                token.value += peek();
                token.type = TokenType::CodeSection;
                next();
                while(braceNestLevel > 0)
                {
                    if(peek() == WEOF)
                    {
                        if(quoteCharacter == '\'')
                            throw ParseError(location, L"expected closing single quote");
                        if(quoteCharacter == '\"')
                            throw ParseError(location, L"expected closing double quote");
                        throw ParseError(location, L"expected closing brace");
                    }
                    if(quoteCharacter != WEOF)
                    {
                        if(peek() == '\\')
                        {
                            token.value += peek();
                            next();
                            if(peek() == WEOF)
                                throw ParseError(location, L"missing rest of escape sequence");
                            token.value += peek();
                            next();
                        }
                        else if(peek() == quoteCharacter)
                        {
                            token.value += peek();
                            next();
                            quoteCharacter = WEOF;
                        }
                        else
                        {
                            token.value += peek();
                            next();
                        }
                    }
                    else if(peek() == '\'' || peek() == '\"')
                    {
                        token.value += peek();
                        quoteCharacter = peek();
                        next();
                    }
                    else if(peek() == '{')
                    {
                        braceNestLevel++;
                        token.value += peek();
                        next();
                    }
                    else if(peek() == '}')
                    {
                        braceNestLevel--;
                        token.value += peek();
                        next();
                    }
                    else
                    {
                        token.value += peek();
                        next();
                    }
                }
                return;
            }
            if(peek() == ';')
            {
                token.value += peek();
                token.type = TokenType::Semicolon;
                next();
                return;
            }
            if(peek() == ':')
            {
                token.value += peek();
                token.type = TokenType::Colon;
                next();
                return;
            }
            if(peek() == '|')
            {
                token.value += peek();
                token.type = TokenType::Pipe;
                next();
                return;
            }
            if(peek() == '/')
            {
                next();
                if(peek() == '/')
                {
                    while(peek() != WEOF && peek() != '\n')
                        next();
                    continue;
                }
                else if(peek() == '*')
                {
                    next();
                    while(peek() != WEOF)
                    {
                        if(peek() == '*')
                        {
                            while(peek() == '*')
                                next();
                            if(peek() == '/')
                                break;
                        }
                        else
                            next();
                    }
                    if(peek() != '/')
                        throw ParseError(location, L"expected */");
                    next();
                    continue;
                }
                else
                    throw ParseError(location, L"invalid character");
            }
            throw ParseError(location, L"invalid character");
            break;
        }
    }
};

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

void parsePrologueSection(Tokenizer &tokenizer, unordered_multimap<wstring, CodeSection> &prologueCode, SymbolSet &symbols, unordered_map<wstring, shared_ptr<Symbol>> &symbolsMap, unordered_map<wstring, wstring> &outputOptions)
{
    bool nextAtBeginningOfLine = true;
    for(;;)
    {
        Token &token = tokenizer.token;
        bool atBeginningOfLine = nextAtBeginningOfLine;
        nextAtBeginningOfLine = false;
        switch(token.type)
        {
        case TokenType::EndOfFile:
            throw ParseError(token.location, L"expected %%");
        case TokenType::DoublePercent:
            tokenizer.nextToken();
            return;
        case TokenType::CodeSection:
            prologueCode.insert(make_pair(L"", CodeSection(token.location, token.value)));
            tokenizer.nextToken();
            break;
        case TokenType::EndOfLine:
            nextAtBeginningOfLine = true;
            tokenizer.nextToken();
            break;
        case TokenType::PercentIdentifier:
            if(!atBeginningOfLine)
                throw ParseError(token.location, L"unexpected token");
            if(token.value == L"%token")
            {
                tokenizer.nextToken();
                while(token.type == TokenType::Identifier)
                {
                    if(symbolsMap.count(token.value) > 0)
                        throw ParseError(token.location, L"already declared as token");
                    shared_ptr<Symbol> symbol = TerminalSymbol::make(token.value);
                    symbolsMap[token.value] = symbol;
                    symbols.insert(symbol);
                    tokenizer.nextToken();
                }
                if(token.type != TokenType::EndOfLine && token.type != TokenType::EndOfFile)
                    throw ParseError(token.location, L"unexpected token");
            }
            else if(token.value == L"%option")
            {
                tokenizer.nextToken();
                if(token.type != TokenType::String && token.type != TokenType::Identifier)
                    throw ParseError(token.location, L"expected option name");
                wstring name = token.value, value = L"";
                tokenizer.nextToken();
                if(token.type == TokenType::String)
                {
                    value = token.value;
                    tokenizer.nextToken();
                }
                if(token.type != TokenType::EndOfLine && token.type != TokenType::EndOfFile)
                    throw ParseError(token.location, L"unexpected token");
                outputOptions[name] = value;
            }
            else
                throw ParseError(token.location, L"unknown directive");
            break;
        default:
            throw ParseError(token.location, L"unexpected token");
        }
    }
}

shared_ptr<Symbol> findOrMakeSymbol(wstring name, SymbolSet &symbols, unordered_map<wstring, shared_ptr<Symbol>> &symbolsMap)
{
    shared_ptr<Symbol> &retval = symbolsMap[name];
    if(retval == nullptr)
    {
        retval = make_shared<NonterminalSymbol>(name);
        symbols.insert(retval);
    }
    return retval;
}

void getNewLines(Tokenizer &tokenizer)
{
    while(tokenizer.token.type == TokenType::EndOfLine)
        tokenizer.nextToken();
}

void parseRule(Tokenizer &tokenizer, RuleSet &rules, SymbolSet &symbols, unordered_map<wstring, shared_ptr<Symbol>> &symbolsMap, shared_ptr<NonterminalSymbol> &startSymbol)
{
    Token &token = tokenizer.token;
    if(token.type != TokenType::Identifier)
        throw ParseError(token.location, L"expected an identifier");
    shared_ptr<Symbol> symbol = findOrMakeSymbol(token.value, symbols, symbolsMap);
    if(symbol->isTerminal())
        throw ParseError(token.location, L"can't use terminal symbol in left-hand side of rule");
    shared_ptr<NonterminalSymbol> lhs = dynamic_pointer_cast<NonterminalSymbol>(symbol);
    assert(lhs != nullptr);
    if(startSymbol == nullptr)
        startSymbol = lhs;
    tokenizer.nextToken();
    getNewLines(tokenizer);
    if(token.type != TokenType::Colon)
        throw ParseError(token.location, L"expected :");

    tokenizer.nextToken();
    getNewLines(tokenizer);
    SymbolList rhs;
    CodeSection code = CodeSection();
    bool hasCode = false;

    while(token.type != TokenType::Semicolon && token.type != TokenType::EndOfFile)
    {
        switch(token.type)
        {
        case TokenType::Character:
            if(hasCode)
                throw ParseError(token.location, L"expected | or ;");
            symbol = TerminalSymbol::make(token.makeCharacterLiteral());
            symbols.insert(symbol);
            rhs.push_back(symbol);
            tokenizer.nextToken();
            break;
        case TokenType::CodeSection:
            if(hasCode)
                throw ParseError(token.location, L"expected | or ;");
            code = CodeSection(token.location, token.value);
            hasCode = true;
            tokenizer.nextToken();
            break;
        case TokenType::Identifier:
            if(hasCode)
                throw ParseError(token.location, L"expected | or ;");
            symbol = findOrMakeSymbol(token.value, symbols, symbolsMap);
            symbols.insert(symbol);
            rhs.push_back(symbol);
            tokenizer.nextToken();
            break;
        case TokenType::Pipe:
            rules.insert(make_shared<Rule>(lhs, rhs, code));
            rhs.clear();
            code = CodeSection();
            hasCode = false;
            tokenizer.nextToken();
            break;
        case TokenType::String:
            if(hasCode)
                throw ParseError(token.location, L"expected | or ;");
            for(wstring literal : token.makeCharacterLiterals())
            {
                symbol = TerminalSymbol::make(literal);
                symbols.insert(symbol);
                rhs.push_back(symbol);
            }
            tokenizer.nextToken();
            break;
        default:
            throw ParseError(token.location, L"unexpected token");
        }
        getNewLines(tokenizer);
    }
    rules.insert(make_shared<Rule>(lhs, rhs, code));
    if(token.type != TokenType::Semicolon)
        throw ParseError(token.location, L"expected ;");
    tokenizer.nextToken();
}

void parseRulesSection(Tokenizer &tokenizer, RuleSet &rules, SymbolSet &symbols, unordered_map<wstring, shared_ptr<Symbol>> &symbolsMap, shared_ptr<NonterminalSymbol> &startSymbol)
{
    Token &token = tokenizer.token;
    getNewLines(tokenizer);
    if(token.type != TokenType::Identifier)
        throw ParseError(token.location, L"expected rule");
    while(token.type == TokenType::Identifier)
    {
        parseRule(tokenizer, rules, symbols, symbolsMap, startSymbol);
        getNewLines(tokenizer);
    }
    if(token.type != TokenType::DoublePercent)
    {
        throw ParseError(token.location, L"expected %% or a rule");
    }
    tokenizer.nextToken();
}

void parseEpilogueSection(Tokenizer &tokenizer, unordered_multimap<wstring, CodeSection> &epilogueCode)
{
    bool nextAtBeginningOfLine = false;
    for(;;)
    {
        Token &token = tokenizer.token;
        bool atBeginningOfLine = nextAtBeginningOfLine;
        nextAtBeginningOfLine = false;
        switch(token.type)
        {
        case TokenType::EndOfFile:
            return;
        case TokenType::CodeSection:
            epilogueCode.insert(make_pair(L"", CodeSection(token.location, token.value)));
            tokenizer.nextToken();
            break;
        case TokenType::EndOfLine:
            nextAtBeginningOfLine = true;
            tokenizer.nextToken();
            break;
        case TokenType::PercentIdentifier:
            if(!atBeginningOfLine)
                throw ParseError(token.location, L"unexpected token");
            if(token.value == L"%token")
                throw ParseError(token.location, L"can't use %token here");
            else
                throw ParseError(token.location, L"unknown directive");
            break;
        default:
            throw ParseError(token.location, L"unexpected token");
        }
    }
}

void version()
{
    cout << "Parser Generator v1.0.1 by Jacob R. Lifshay (c) 2014\n";
#define STRINGIFY(v) #v
#if defined(__clang__)
	/* Clang/LLVM. ---------------------------------------------- */
    string compilerVersionString = "Clang/LLVM " __clang_version__;
#elif defined(__ICC) || defined(__INTEL_COMPILER)
	/* Intel ICC/ICPC. ------------------------------------------ */
    string compilerVersionString = __VERSION__;
#elif defined(__GNUC__) || defined(__GNUG__)
	/* GNU GCC/G++. --------------------------------------------- */
    string compilerVersionString = "G++ " __VERSION__;
#elif defined(__HP_cc) || defined(__HP_aCC)
	/* Hewlett-Packard C/aC++. ---------------------------------- */
    string compilerVersionString = "HP aC++ " STRINGIFY(__HP_aCC);
#elif defined(__IBMC__) || defined(__IBMCPP__)
	/* IBM XL C/C++. -------------------------------------------- */
    string compilerVersionString = "IBM XL C++ " __xlc__;
#elif defined(_MSC_VER)
	/* Microsoft Visual Studio. --------------------------------- */
    string compilerVersionString = "Microsoft Visual Studio " _MSC_VER;
#elif defined(__PGI)
	/* Portland Group PGCC/PGCPP. ------------------------------- */
    string compilerVersionString = "Portland Group PGCPP " __PGIC__ "." __PGIC_MINOR "." __PGIC_PATCHLEVEL__;
#else
#warning unknown compiler
    string compilerVersionString = "Unknown : '" __VERSION__ "'";
#endif
    cout << "Built with " << compilerVersionString << endl;
}

void help(string programName)
{
    version();
    cout << "\nUsage : " << programName << " [options] [--] <input file>\n\nOptions:\n\n-h\t\tShow this help.\n-?\n--help\n\n--verbose\tShow Version.\n-v\t\tVerbose output.\n\n--\t\tStop parsing options.";
    cout << endl;
}

int main(int argc, char **argv)
{
    string inputFile;
    bool parseOptions = true, gotInputFile = false, verbose = false;
    for(int i = 1; i < argc; i++)
    {
        string arg = argv[i];
        if(parseOptions)
        {
            if(arg == "-h" || arg == "-?" || arg == "--help")
            {
                help(argv[0]);
                exit(0);
            }
            if(arg == "--version")
            {
                version();
                exit(0);
            }
            if(arg == "-v")
            {
                verbose = true;
                continue;
            }
            if(arg == "--")
            {
                parseOptions = false;
                continue;
            }
            if(arg.substr(0, 1) == "-")
            {
                cerr << "invalid option : " << arg << endl;
                exit(1);
            }
        }
        if(gotInputFile)
        {
            cerr << "can't specify multiple input files in one command\n";
            exit(1);
        }
        gotInputFile = true;
        inputFile = arg;
    }

    if(!gotInputFile)
    {
        cerr << "No file to process.\nfor help do '" << argv[0] << " -h'\n";
        exit(1);
    }

    SymbolSet symbols;
    unordered_map<wstring, shared_ptr<Symbol>> symbolsMap;
    RuleSet rules;
    shared_ptr<TerminalSymbol> eofSymbol = TerminalSymbol::make(L"EOF");
    symbols.insert(eofSymbol);
    shared_ptr<NonterminalSymbol> startSymbol;
    unordered_multimap<wstring, CodeSection> prologueCode, epilogueCode;
    unordered_map<wstring, wstring> outputOptions;
    try
    {
        ifstream is(inputFile);
        Tokenizer tokenizer(string_cast<wstring>(inputFile), is);
        parsePrologueSection(tokenizer, prologueCode, symbols, symbolsMap, outputOptions);
        parseRulesSection(tokenizer, rules, symbols, symbolsMap, startSymbol);
        parseEpilogueSection(tokenizer, epilogueCode);
    }
    catch(exception &e)
    {
        cerr << "Error : " << e.what() << endl;
        return 1;
    }

    if(verbose)
    {
        cout << "parsed input file." << endl;
    }

    calculateFirstSets(symbols, rules);

    if(verbose)
    {
        cout << "calculated First sets." << endl;
    }

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
        if(verbose)
        {
            cout << "processing canonical set " << (i + 1) << " out of " << canonicalSets.size() << "\x1b[K\r" << flush;
        }

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

    if(verbose)
    {
        cout << "processed " << canonicalSets.size() << " canonical sets.\x1b[K" << endl;
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
                cerr << inputFile << ": error: conflict on lookahead of " << string_cast<string>(dumpSymbol(terminalSymbols[symbolIndex], FormattingOptions())) << " : \n";
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

    if(verbose)
    {
        cout << "filled tables." << endl;
    }

    try
    {
        FileWriter *writer = makeFileWriter(L"C++", inputFile, outputOptions);
        writer->writePrologue(prologueCode);
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
        writer->writeEpilogue(epilogueCode);
        delete writer;
    }
    catch(exception &e)
    {
        cerr << inputFile << ": error : " << e.what() << endl;
        return 1;
    }

    if(verbose)
    {
        cout << "wrote output files." << endl;
    }
    return 0;
}