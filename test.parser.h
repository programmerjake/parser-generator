// This is a automatically generated file : DO NOT MODIFY
// This file is generated from 'test.parser'
#ifndef PARSER_TEST_PARSER_H
#define PARSER_TEST_PARSER_H

#line 1 "test.parser"

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <cassert>
#include <map>
#include <stdexcept>

using namespace std;

enum TokenType
{
    TTEof,
    TTId,
    TTNumber,
    TTString,
    TTCharacter,
    TTPlus,
    TTMinus,
    TTStar,
    TTFSlash,
    TTLParen,
    TTRParen,
    TTSemicolon,
    TTAssign,
    TTLEq,
    TTLNE,
    TTLLT,
    TTLLE,
    TTLGT,
    TTLGE,
    TTPeriod,
    TTEMark,
};

struct ValueType
{
    TokenType type;
    string svalue;
    double nvalue;
    ValueType()
    {
        type = TTEof;
        svalue = "";
        nvalue = 0;
    }
    explicit ValueType(int) // for EOF
    {
        type = TTEof;
        svalue = "";
        nvalue = 0;
    }
    explicit ValueType(TokenType type, string svalue = "", double nvalue = 0)
        : type(type), svalue(svalue), nvalue(nvalue)
    {
    }
    bool operator ==(const ValueType &rt) const
    {
        return type == rt.type;
    }
    bool operator !=(const ValueType &rt) const
    {
        return type != rt.type;
    }
    friend ostream &operator <<(ostream &os, const ValueType &v)
    {
        if(v.type == TTNumber)
            os << v.nvalue;
        else
            os << v.svalue;
        return os;
    }
    double getNumber() const
    {
        if(type == TTCharacter)
            return (int)svalue[0];
        if(type == TTNumber)
            return nvalue;
        throw runtime_error("can't use string as number");
    }
    string getString() const
    {
        if(type == TTString)
            return svalue;
        if(type == TTCharacter)
            return svalue;
        throw runtime_error("can't use number as string");
    }
    static map<string, ValueType> &getSymbolTable();
};



#line 102 "test.parser.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdio> // for EOF

class MyParser
{
public:
    struct ParseError : public std::runtime_error
    {
        explicit ParseError(const std::string &msg) noexcept
            : runtime_error(msg)
        {
        }
    };
private:
    struct ElementType
    {
        size_t state;
        ValueType value;
        ElementType(size_t state, ValueType value)
            : state(state), value(value)
        {
        }
    };
    std::vector<ElementType> theStack;
    static constexpr size_t ErrorState = ~(size_t)0;
    enum class ActionType
    {
        Shift,
        Reduce,
        Accept,
        Error
    };
    struct ActionEntry
    {
        ActionType type;
        size_t nextState;
        ValueType (MyParser::*reduceFn)(ValueType &peekToken);
        size_t popCount;
    };
    static const ActionEntry actionTable[48][21];
    static const size_t gotoTable[48][5];
    static const ValueType terminalsTable[21];
    ValueType reduce_to_factor_0(ValueType &peekToken);
    ValueType reduce_to_factor_1(ValueType &peekToken);
    ValueType reduce_to_factor_2(ValueType &peekToken);
    ValueType reduce_to_factor_3(ValueType &peekToken);
    ValueType reduce_to_factor_4(ValueType &peekToken);
    ValueType reduce_to_start_5(ValueType &peekToken);
    ValueType reduce_to_start_6(ValueType &peekToken);
    ValueType reduce_to_add_sub_expression_7(ValueType &peekToken);
    ValueType reduce_to_add_sub_expression_8(ValueType &peekToken);
    ValueType reduce_to_add_sub_expression_9(ValueType &peekToken);
    ValueType reduce_to_expression_10(ValueType &peekToken);
    ValueType reduce_to_expression_11(ValueType &peekToken);
    ValueType reduce_to_mul_div_expression_12(ValueType &peekToken);
    ValueType reduce_to_mul_div_expression_13(ValueType &peekToken);
    ValueType reduce_to_mul_div_expression_14(ValueType &peekToken);
    size_t translateToken(const ValueType &tok);
public:
    virtual ~MyParser()
    {
    }
    ValueType parse();
protected:
    virtual ValueType getToken() = 0;
    virtual void handleError(const std::string &msg)
    {
        throw ParseError(msg);
    }
};
#endif
