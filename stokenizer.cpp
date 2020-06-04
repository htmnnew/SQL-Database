#include "stokenizer.h"
#include <string.h>
#include <iostream>
#include "constants.h"

STokenizer::STokenizer()
{
    build_default_state_array();
}

STokenizer::STokenizer(std::string text)
{
    build_default_state_array();
    setBlock(text);
}

STokenizer::STokenizer(const STokenizer& other)
{
    if(state_array)
    {
        for(int i = 0; i < state_rows; i++)
            delete [] state_array[i];
        delete [] state_array;
    }

    allocate_state_array(other.state_rows, other.state_cols);

    for(int i = 0; i < other.state_rows; i++)
        for(int j = 0; j < other.state_cols; j++)
            state_array[i][j] = other.state_array[i][j];

    state_rows = other.state_rows;
    state_cols = other.state_cols;

    block = other.block;
    std::string::iterator it;
    for(it = block.begin(); it != block.end(); ++it)
    {
        if(*it == *other.cursor)
        {
            cursor = it;
            break;
        }

        if(it == block.end())
            cursor = block.begin();
    }
}

STokenizer& STokenizer::operator=(const STokenizer& other)
{
    if(state_array)
    {
        for(int i = 0; i < state_rows; i++)
            delete [] state_array[i];
        delete [] state_array;
    }

    allocate_state_array(other.state_rows, other.state_cols);

    for(int i = 0; i < other.state_rows; i++)
        for(int j = 0; j < other.state_cols; j++)
            state_array[i][j] = other.state_array[i][j];

    state_rows = other.state_rows;
    state_cols = other.state_cols;

    block = other.block;
    std::string::iterator it;
    for(it = block.begin(); it != block.end(); ++it)
    {
        if(*it == *other.cursor)
        {
            cursor = it;
            break;
        }

        if(it == block.end())
            cursor = block.begin();
    }

    return *this;
}

STokenizer::~STokenizer()
{
    if(state_array)
    {
        for(int i = 0; i < state_rows; i++)
            delete [] state_array[i];
        delete [] state_array;
    }
}

bool STokenizer::hasNext()
{
    if(*cursor == '\0')
        return false;
    return true;
}

Token STokenizer::getNextToken()
{
    if(hasNext())
    {
        std::string::iterator walker = cursor;
        std::string::iterator tknCursor = cursor;
        int lastSuccessRow = 0;
        std::string tempToken;
        int type = -1;

        proccessMachine(lastSuccessRow, walker, tempToken);

        if(lastSuccessRow%2 != 0 && lastSuccessRow != -1)
            type = TYPE_NUMBER;
        else
        {
            lastSuccessRow = 6;
            tempToken.clear();
            walker = cursor;

            proccessMachine(lastSuccessRow, walker, tempToken);

            if(lastSuccessRow%2 != 0 && lastSuccessRow != -1)
                type = TYPE_ALPHA;
            else
            {
                tempToken.clear();
                type = TYPE_UNKNOWN;
                while(tknCursor != walker)
                {
                    tempToken += std::string(1, *tknCursor);
                    tknCursor++;
                }

                tempToken += std::string(1, *tknCursor);
                if(*walker != '\0')
                    walker++;

                if(tempToken == " ")
                    type = TYPE_SPACE;
                else if(tempToken == "\n")
                    type = TYPE_NEW_LINE;
                else if(tempToken == ",")
                    type = TYPE_COMMA;
            }
        }

        cursor = walker;
        return Token(tempToken, type);
    }

    return Token("\0", TYPE_UNKNOWN);

}

void STokenizer::proccessMachine(int &start_last_row, std::string::iterator &walker, std::string &token)
{
    int row = start_last_row;
    std::string::iterator tknCursor = walker;
    int lastSuccessRow = -1;

    do
    {
        row = state_array[row][*walker];

        if(row != -1)
        {
            walker++;
            if(row%2 != 0)
            {
                lastSuccessRow = row;
                while(tknCursor != walker)
                {
                    token = token + std::string(1, *tknCursor);
                    tknCursor++;
                }
            }
        }

    } while(row != -1 && walker != block.end());

    if(lastSuccessRow != -1)
        walker = tknCursor;
    start_last_row = lastSuccessRow;
}

void STokenizer::setBlock(std::string block)
{
    this->block = block;
    cursor = this->block.begin();
}

void STokenizer::build_default_state_array()
{
    state_rows = DEFAULT_MAX_ROWS;
    state_cols = DEFAULT_MAX_COLS;

    allocate_state_array(state_rows, state_cols);
    initialize_state_array(-1);

    //Fills Digits Collums and Complete Row 5
    fill_collums("014", DIGIT, 1);
    fill_row(2, DIGIT, 3);
    fill_collums("678", DIGIT, 8);
    fill_row(3, DIGIT, 3);
    fill_row(5, DIGIT, 5);
    fill_row(5, ALPHA, 5);
    fill_row(5, "-", 5);
    fill_row(5, ".", -1);
    fill_row(5, PUNCT, 5);


    //Finishes Rows 6, 7, 8
    fill_collums("678", "-.", 7);
    fill_collums("678", PUNCT, 7);
    fill_collums("678", ALPHA, 5);

    //Finishes Remaing Values
    fill_cell(0, '-', 4);
    fill_collum("014", '.', 2);

    //Leaving this not -1 will result in things
    //like 192.168.1.2 being split up into 192.168 .1 .2
    fill_cell(3, '.', 2);

    //Number Collums Filled
    fill_collums("0123", DIGIT, 1);
    fill_collums("45", DIGIT, 5);

    //Allows words ending in these to be seperated
    fill_row(5, "\",;?!\")({}[]", -1);
    fill_row(7, "\",;?!\")({}[]", -1);
    fill_row(6, ",", -1);

//    for(int c = state_cols; c < state_cols; c++)
//    {
//        for(int r = state_rows; r < state_rows; r++)
//            std::cout << state_array[r][c] << " ";
//        std::cout << std::endl;
//    }
}

void STokenizer::fill_row(int row, const char* collums, int value)
{
    for(int i = 0; i < strlen(collums); i++)
        state_array[row][collums[i]] = value;
}

void STokenizer::fill_cell(int row, char collum, int value)
{
    state_array[row][collum] = value;
}

void STokenizer::fill_collum(const char* rows, char collum, int value)
{
    for(int i = 0; i < strlen(rows); i++)
        state_array[rows[i]-'0'][collum] = value;
}

void STokenizer::fill_collums(const char* rows, const char* collums, int value)
{
    for(int i = 0; i < strlen(rows); i++)
    {
        for(int j = 0; j < strlen(collums); j++)
        {
            state_array[rows[i]-'0'][collums[j]] = value;
        }
    }
}

void STokenizer::allocate_state_array(int rows, int cols)
{
    state_array = new int*[rows];
    for(int i = 0; i < rows; i++)
        state_array[i] = new int[cols];
}

void STokenizer::initialize_state_array(int value)
{
    for(int i = 0; i < state_rows; i++)
        for(int j = 0; j < state_cols; j++)
            state_array[i][j] = value;
}
