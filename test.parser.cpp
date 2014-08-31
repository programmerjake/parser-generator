// This is a automatically generated file : DO NOT MODIFY
// This file is generated from 'test.parser'
#include "test.parser.h"
ValueType MyParser::reduce_to_factor_0()
{
    ValueType retval;
    {if(ValueType::getSymbolTable().count((this->theStack[this->theStack.size() - 1].value).svalue) == 0) handleError("empty variable"); retval = ValueType::getSymbolTable()[(this->theStack[this->theStack.size() - 1].value).svalue];}
    return retval;
}
ValueType MyParser::reduce_to_factor_1()
{
    ValueType retval;
    {retval = (this->theStack[this->theStack.size() - 2].value);}
    return retval;
}
ValueType MyParser::reduce_to_factor_2()
{
    ValueType retval;
    {retval = (this->theStack[this->theStack.size() - 1].value);}
    return retval;
}
ValueType MyParser::reduce_to_factor_3()
{
    ValueType retval;
    {retval = (this->theStack[this->theStack.size() - 1].value);}
    return retval;
}
ValueType MyParser::reduce_to_factor_4()
{
    ValueType retval;
    {retval = (this->theStack[this->theStack.size() - 1].value);}
    return retval;
}
ValueType MyParser::reduce_to_start_5()
{
    ValueType retval;
    {cout << "output: " << (this->theStack[this->theStack.size() - 2].value) << endl;}
    return retval;
}
ValueType MyParser::reduce_to_start_6()
{
    ValueType retval;
    {cout << "output: " << (this->theStack[this->theStack.size() - 2].value) << endl;}
    return retval;
}
ValueType MyParser::reduce_to_expression_7()
{
    ValueType retval;
    {ValueType::getSymbolTable()[(this->theStack[this->theStack.size() - 3].value).svalue] = (this->theStack[this->theStack.size() - 1].value); retval = (this->theStack[this->theStack.size() - 1].value);}
    return retval;
}
ValueType MyParser::reduce_to_expression_8()
{
    ValueType retval;
    {retval = (this->theStack[this->theStack.size() - 1].value);}
    return retval;
}
ValueType MyParser::reduce_to_add_sub_expression_9()
{
    ValueType retval;
    {retval = ValueType(TTNumber, "", (this->theStack[this->theStack.size() - 3].value).getNumber() + (this->theStack[this->theStack.size() - 1].value).getNumber());}
    return retval;
}
ValueType MyParser::reduce_to_add_sub_expression_10()
{
    ValueType retval;
    {if((this->theStack[this->theStack.size() - 3].value).type == TTString || (this->theStack[this->theStack.size() - 1].value).type == TTString) retval = ValueType(TTString, (this->theStack[this->theStack.size() - 3].value).getString() + (this->theStack[this->theStack.size() - 1].value).getString()); else retval = ValueType(TTNumber, "", (this->theStack[this->theStack.size() - 3].value).getNumber() + (this->theStack[this->theStack.size() - 1].value).getNumber());}
    return retval;
}
ValueType MyParser::reduce_to_add_sub_expression_11()
{
    ValueType retval;
    {retval = (this->theStack[this->theStack.size() - 1].value);}
    return retval;
}
ValueType MyParser::reduce_to_mul_div_expression_12()
{
    ValueType retval;
    {if((this->theStack[this->theStack.size() - 1].value).getNumber() == 0) handleError("division by zero"); retval = ValueType(TTNumber, "", (this->theStack[this->theStack.size() - 3].value).getNumber() / (this->theStack[this->theStack.size() - 1].value).getNumber());}
    return retval;
}
ValueType MyParser::reduce_to_mul_div_expression_13()
{
    ValueType retval;
    {retval = ValueType(TTNumber, "", (this->theStack[this->theStack.size() - 3].value).getNumber() * (this->theStack[this->theStack.size() - 1].value).getNumber());}
    return retval;
}
ValueType MyParser::reduce_to_mul_div_expression_14()
{
    ValueType retval;
    {retval = (this->theStack[this->theStack.size() - 1].value);}
    return retval;
}
const ValueType MyParser::terminalsTable[21] =
{
    ValueType(EOF),
    ValueType(TTFSlash),
    ValueType(TTStar),
    ValueType(TTMinus),
    ValueType(TTCharacter),
    ValueType(TTPlus),
    ValueType(TTString),
    ValueType(TTLLT),
    ValueType(TTId),
    ValueType(TTLNE),
    ValueType(TTNumber),
    ValueType(TTRParen),
    ValueType(TTSemicolon),
    ValueType(TTEof),
    ValueType(TTAssign),
    ValueType(TTLEq),
    ValueType(TTLLE),
    ValueType(TTLParen),
    ValueType(TTLGT),
    ValueType(TTLGE),
    ValueType(TTEMark),
};
const MyParser::ActionEntry MyParser::actionTable[48][21] =
{
    { // state 0
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 3, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 4, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 5, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 7, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 8, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 1
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 11, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 2
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_14, 1},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_14, 1},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_14, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_14, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_14, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 3
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_3, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_3, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_3, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_3, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_3, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 4
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_2, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_2, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_2, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_2, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_2, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 5
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 12, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 6
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 13, nullptr, 0},
        {MyParser::ActionType::Shift, 14, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_11, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_11, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_11, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 7
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_4, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_4, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_4, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_4, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_4, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 8
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 17, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 18, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 19, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 21, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 22, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 9
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 24, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 25, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 1, &MyParser::reduce_to_expression_8, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 10
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 3, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 4, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 5, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 7, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 8, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 11
        {MyParser::ActionType::Accept, 0, &MyParser::reduce_to_start_6, 2},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 0, &MyParser::reduce_to_start_6, 2},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 0, &MyParser::reduce_to_start_6, 2},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 0, &MyParser::reduce_to_start_6, 2},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 0, &MyParser::reduce_to_start_6, 2},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 0, &MyParser::reduce_to_start_6, 2},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 12
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 3, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 4, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 5, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 7, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 8, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 13
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 3, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 4, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 29, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 7, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 8, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 14
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 3, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 4, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 29, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 7, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 8, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 15
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 31, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 16
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_14, 1},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_14, 1},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_14, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_14, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_14, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 17
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_3, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_3, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_3, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_3, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_3, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 18
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_2, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_2, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_2, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_2, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_2, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 19
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 32, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 20
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 33, nullptr, 0},
        {MyParser::ActionType::Shift, 34, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_11, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_11, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_11, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 21
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_4, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_4, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_4, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_4, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_4, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 22
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 17, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 18, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 19, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 21, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 22, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 23
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 36, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 37, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 1, &MyParser::reduce_to_expression_8, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 24
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 3, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 4, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 29, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 7, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 8, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 25
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 3, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 4, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 29, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 7, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 8, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 26
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 40, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 27
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 1, &MyParser::reduce_to_expression_7, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 28
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_12, 3},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_12, 3},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_12, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_12, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_12, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 29
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 30
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_13, 3},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_13, 3},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_13, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_13, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_13, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 31
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_1, 3},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_1, 3},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_1, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_1, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_1, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 32
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 17, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 18, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 19, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 21, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 22, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 33
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 17, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 18, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 43, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 21, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 22, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 34
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 17, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 18, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 43, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 21, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 22, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 35
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 45, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 36
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 17, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 18, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 43, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 21, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 22, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 37
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 17, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 18, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 43, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 21, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 22, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 38
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 13, nullptr, 0},
        {MyParser::ActionType::Shift, 14, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_9, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_9, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_9, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 39
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 13, nullptr, 0},
        {MyParser::ActionType::Shift, 14, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_10, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_10, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_10, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 40
        {MyParser::ActionType::Accept, 0, &MyParser::reduce_to_start_5, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 0, &MyParser::reduce_to_start_5, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 0, &MyParser::reduce_to_start_5, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 0, &MyParser::reduce_to_start_5, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 0, &MyParser::reduce_to_start_5, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 0, &MyParser::reduce_to_start_5, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 41
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 1, &MyParser::reduce_to_expression_7, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 42
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_12, 3},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_12, 3},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_12, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_12, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_12, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 43
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_0, 1},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 44
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_13, 3},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_13, 3},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_13, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_13, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 3, &MyParser::reduce_to_mul_div_expression_13, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 45
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_1, 3},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_1, 3},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_1, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_1, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 2, &MyParser::reduce_to_factor_1, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 46
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 33, nullptr, 0},
        {MyParser::ActionType::Shift, 34, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_9, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_9, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_9, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
    { // state 47
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Shift, 33, nullptr, 0},
        {MyParser::ActionType::Shift, 34, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_10, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_10, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Reduce, 4, &MyParser::reduce_to_add_sub_expression_10, 3},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
        {MyParser::ActionType::Error, 0, nullptr, 0},
    },
};
const size_t MyParser::gotoTable[48][5] =
{
    { // state 0
        10,
        1,
        2,
        6,
        9,
    },
    { // state 1
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 2
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 3
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 4
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 5
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 6
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 7
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 8
        MyParser::ErrorState,
        15,
        16,
        20,
        23,
    },
    { // state 9
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 10
        MyParser::ErrorState,
        26,
        2,
        6,
        9,
    },
    { // state 11
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 12
        MyParser::ErrorState,
        27,
        2,
        6,
        9,
    },
    { // state 13
        MyParser::ErrorState,
        MyParser::ErrorState,
        28,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 14
        MyParser::ErrorState,
        MyParser::ErrorState,
        30,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 15
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 16
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 17
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 18
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 19
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 20
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 21
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 22
        MyParser::ErrorState,
        35,
        16,
        20,
        23,
    },
    { // state 23
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 24
        MyParser::ErrorState,
        MyParser::ErrorState,
        2,
        38,
        MyParser::ErrorState,
    },
    { // state 25
        MyParser::ErrorState,
        MyParser::ErrorState,
        2,
        39,
        MyParser::ErrorState,
    },
    { // state 26
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 27
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 28
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 29
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 30
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 31
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 32
        MyParser::ErrorState,
        41,
        16,
        20,
        23,
    },
    { // state 33
        MyParser::ErrorState,
        MyParser::ErrorState,
        42,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 34
        MyParser::ErrorState,
        MyParser::ErrorState,
        44,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 35
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 36
        MyParser::ErrorState,
        MyParser::ErrorState,
        16,
        46,
        MyParser::ErrorState,
    },
    { // state 37
        MyParser::ErrorState,
        MyParser::ErrorState,
        16,
        47,
        MyParser::ErrorState,
    },
    { // state 38
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 39
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 40
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 41
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 42
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 43
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 44
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 45
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 46
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
    { // state 47
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
        MyParser::ErrorState,
    },
};
size_t MyParser::translateToken(const ValueType &tok)
{
    for(size_t i = 0; i < sizeof(terminalsTable) / sizeof(terminalsTable[0]); i++)
    {
        if(terminalsTable[i] == tok)
            return i;
    }
    handleError("unknown token");
    return 0;
}
ValueType MyParser::parse()
{
    ValueType token = getToken();
    size_t ttok = translateToken(token);
    theStack.assign(1, ElementType(0, terminalsTable[0]));

    for(;;)
    {
        size_t state = theStack.back().state;
        switch(actionTable[state][ttok].type)
        {
        case ActionType::Shift:
            theStack.push_back(ElementType(actionTable[state][ttok].nextState, token));
            token = getToken();
            ttok = translateToken(token);
            break;
        case ActionType::Accept:
            return (this->*actionTable[state][ttok].reduceFn)();
        case ActionType::Reduce:
        {
            ValueType value = (this->*actionTable[state][ttok].reduceFn)();
            theStack.erase(theStack.begin() + (theStack.size() - actionTable[state][ttok].popCount), theStack.end());
            size_t symbol = actionTable[state][ttok].nextState;
            state = theStack.back().state;
            theStack.push_back(ElementType(gotoTable[state][symbol], value));
            break;
        }
        default:
            handleError("unexpected token");
            return terminalsTable[0];
        }
    }
}

map<string, ValueType> &ValueType::getSymbolTable()
{
    static map<string, ValueType> *pSymbolTable = NULL;
    if(!pSymbolTable)
        pSymbolTable = new map<string, ValueType>();
    return *pSymbolTable;
}


class ParserImp : public MyParser
{
    istream &is;
    int readEscapeSequence()
    {
        assert(is.peek() == '\\');
        is.get();
        switch(is.peek())
        {
        case EOF:
        case '\n':
            handleError("missing rest of escape sequence");
            return EOF;
        case '\'':
        case '\\':
        case '\"':
            return is.get();
        case 'a':
            is.get();
            return '\a';
        case 'b':
            is.get();
            return '\b';
        case 'f':
            is.get();
            return '\f';
        case 'n':
            is.get();
            return '\n';
        case 'r':
            is.get();
            return '\r';
        case 't':
            is.get();
            return '\t';
        case 'v':
            is.get();
            return '\v';
        case '0':
            is.get();
            return '\0';
        case 'x':
        {
            int value = 0;
            is.get();
            for(size_t i = 0; i < 2; i++)
            {
                if(!isxdigit(is.peek()))
                    handleError("missing hexadecimal error in escape sequence");
                value *= 0x10;
                if(isdigit(is.peek()))
                    value += is.get() - '0';
                else if(islower(is.peek()))
                    value += is.get() - 'a' + 0xA;
                else
                    value += is.get() - 'A' + 0xA;
            }
            return value;
        }
        default:
            handleError("invalid escape sequence");
            return EOF;
        }
    }
public:
    ParserImp(istream &is)
        : is(is)
    {
    }
protected:
    virtual ValueType getToken()
    {
        while(isspace(is.peek()))
            is.get();
        if(is.peek() == EOF)
            return ValueType(EOF);
        if(isalpha(is.peek()) || is.peek() == '_')
        {
            ValueType retval(TTId);
            while(isalnum(is.peek()) || is.peek() == '_')
                retval.svalue += is.get();
            return retval;
        }
        if(isdigit(is.peek()) || is.peek() == '.')
        {
            ValueType retval(TTNumber, "", 0);
            if(is.peek() == 0)
            {
                retval.svalue += is.get();
                if(is.peek() == 'x' || is.peek() == 'X')
                {
                    retval.svalue += is.get();
                    if(!isxdigit(is.peek()))
                        handleError("missing hexadecimal digit");
                    while(isxdigit(is.peek()))
                    {
                        retval.nvalue *= 0x10;
                        if(isdigit(is.peek()))
                            retval.nvalue += is.peek() - '0';
                        else if(islower(is.peek()))
                            retval.nvalue += 0xA + is.peek() - 'a';
                        else
                            retval.nvalue += 0xA + is.peek() - 'A';
                        retval.svalue += is.get();
                    }
                    return retval;
                }
            }
            while(isdigit(is.peek()))
            {
                retval.nvalue *= 10;
                retval.nvalue += is.peek() - '0';
                retval.svalue += is.get();
            }
            if(is.peek() == '.')
            {
                retval.svalue += is.get();
                if(!isdigit(is.peek()) && retval.svalue == ".")
                {
                    retval.type = TTPeriod;
                    return retval;
                }
                double divisor = 1;
                while(isdigit(is.peek()))
                {
                    divisor *= 10;
                    retval.svalue += is.peek();
                    retval.nvalue += (is.get() - '0') / divisor;
                }
            }
            if(is.peek() == 'e' || is.peek() == 'E')
            {
                retval.svalue += is.get();
                bool isExponentNegative = false;
                int exponent = 0;
                if(is.peek() == '+' || is.peek() == '-')
                {
                    isExponentNegative = (is.peek() == '-');
                    retval.svalue += is.get();
                }
                if(!isdigit(is.peek()))
                    handleError("missing digit");
                while(isdigit(is.peek()))
                {
                    exponent *= 10;
                    exponent += is.peek() - '0';
                    retval.svalue += is.get();
                }
                if(isExponentNegative)
                    exponent = -exponent;
                retval.nvalue *= std::pow(10, exponent);
            }
            return retval;
        }
        if(is.peek() == '\'')
        {
            ValueType retval = ValueType(TTCharacter);
            is.get();
            if(is.peek() == '\\')
                retval.svalue += (char)readEscapeSequence();
            else if(is.peek() == EOF || is.peek() == '\n' || is.peek() == '\r' || is.peek() == '\'')
                handleError("invalid character literal");
            else
                retval.svalue += is.get();
            if(is.peek() != '\'')
                handleError("missing closing \'");
            is.get();
            return retval;
        }
        if(is.peek() == '\"')
        {
            ValueType retval = ValueType(TTString);
            while(is.peek() == '\"') // concatenate strings
            {
                is.get();
                while(is.peek() != '\"' && is.peek() != EOF && is.peek() != '\r' && is.peek() != '\n')
                {
                    if(is.peek() == '\\')
                        retval.svalue += (char)readEscapeSequence();
                    else
                        retval.svalue += is.get();
                }
                if(is.peek() != '\"')
                    handleError("missing closing \"");
                is.get();
                while(isspace(is.peek()))
                    is.get();
            }
            return retval;
        }
        switch(is.peek())
        {
        case '+':
            is.get();
            return ValueType(TTPlus);
        case '-':
            is.get();
            return ValueType(TTMinus);
        case '*':
            is.get();
            return ValueType(TTStar);
        case '/':
            is.get();
            return ValueType(TTFSlash);
        case '(':
            is.get();
            return ValueType(TTLParen);
        case ')':
            is.get();
            return ValueType(TTRParen);
        case ';':
            is.get();
            return ValueType(TTSemicolon);
        case '=':
            is.get();
            if(is.peek() == '=')
            {
                is.get();
                return ValueType(TTLEq);
            }
            return ValueType(TTAssign);
        case '!':
            is.get();
            if(is.peek() == '=')
            {
                is.get();
                return ValueType(TTLNE);
            }
            return ValueType(TTEMark);
        case '<':
            is.get();
            if(is.peek() == '=')
            {
                is.get();
                return ValueType(TTLLE);
            }
            return ValueType(TTLLT);
        case '>':
            is.get();
            if(is.peek() == '=')
            {
                is.get();
                return ValueType(TTLGE);
            }
            return ValueType(TTLGT);
        default:
            handleError("invalid character");
            return ValueType(EOF);
        }
    }
};

int main()
{
    ParserImp parser(cin);
    try
    {
        parser.parse();
    }
    catch(exception &e)
    {
        cerr << "Error : " << e.what() << endl;
        return 1;
    }
    return 0;
}



