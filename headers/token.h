#ifndef TOKEN_H
#define TOKEN_H
#include <string>

const static int TYPE_SPACE = 0;
const static int TYPE_NEW_LINE = 1;
const static int TYPE_NUMBER = 2;
const static int TYPE_ALPHA = 3;
const static int TYPE_UNKNOWN = 4;
const static int TYPE_NULL = 5;
const static int TYPE_COMMA = 6;

class Token
{
public:
    Token();
    Token(std::string token, int type);
    void setToken(std::string token);
    std::string getToken();
    void setType(int type);
    int getType();
    void print(bool showType);
private:
    std::string tkn;
    int typ;
};

#endif // TOKEN_H
