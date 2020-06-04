#ifndef STOKENIZER_H
#define STOKENIZER_H
#include "token.h"
#include <string>

class STokenizer
{
public:

    STokenizer();
    STokenizer(std::string text);

    STokenizer(const STokenizer& other);
    STokenizer& operator=(const STokenizer& other);
    ~STokenizer();

    bool hasNext();
    Token getNextToken();
    void setBlock(std::string block);

private:
    const static int DEFAULT_MAX_ROWS = 9;
    const static int DEFAULT_MAX_COLS = 256;

    void build_default_state_array();
    void fill_row(int row, const char* collums, int value);
    void fill_cell(int row, char collum, int value);
    void fill_collum(const char* rows, char collum, int value);
    void fill_collums(const char* rows, const char* collums, int value);
    void initialize_state_array(int value);
    void allocate_state_array(int rows, int cols);

    void proccessMachine(int &start_last_row, std::string::iterator &walker, std::string &token);

    std::string::iterator cursor;
    std::string block;

    int state_rows, state_cols;
    int** state_array;
};

#endif // STOKENIZER_H
