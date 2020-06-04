#include "token.h"
#include <iostream>

Token::Token()
{
    tkn = "";
}

Token::Token(std::string token, int type)
{
    setToken(token);
    typ = type;
}

void Token::setToken(std::string token)
{
    tkn = token;
}

std::string Token::getToken()
{
    return tkn;
}

void Token::setType(int type)
{
    typ = type;
}

int Token::getType()
{
    return typ;
}

void Token::print(bool showType)
{
    if(tkn == "\n")
        std::cout<<"Token: "<<"\\n ";
    else
        std::cout<<"Token: "<<tkn;

    if(showType)
    {
        std::cout<<std::endl<<"Type: ";
        switch(typ)
        {
        case TYPE_ALPHA:
            std::cout<<"ALPHA";
            break;
        case TYPE_NUMBER:
            std::cout<<"NUMB";
            break;
        case TYPE_NEW_LINE:
            std::cout<<"NEW_LINE";
            break;
        case TYPE_SPACE:
            std::cout<<"SPACE";
            break;
        case TYPE_UNKNOWN:
            std::cout<<"UNKWN";
            break;
        case TYPE_NULL:
            std::cout<<"NULL";
            break;
        default:
            break;
        }
    }
}
