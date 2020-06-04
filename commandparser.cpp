#include "commandparser.h"
#include "array2D_helper_functions.h"
#include <algorithm>
#include <iostream>

CommandParser::CommandParser(std::string command)
{
    // Build String:Index map
    build_string_indices();

    // Allcoate/Build state_array and
    // State related maps
    build_state_array();

    // Parse string command into tokens and insert
    // them into t_command
    getTokens(command);
}

PTree CommandParser::parseCommand()
{
    // Check if tokens is empty
    // if so return empty parse tree
    if(!t_command.size())
        return PTree();

    // Get Index Of First Command and corresponding
    // parse tree identifiers
    int i_cmd = getCmdIndex(t_command.at(0));
    std::vector<std::string> ids = get_identifiers(i_cmd);

    // Check if identifier vector is not empty
    // If it is empty it means your begining command
    // is invalid and we return an empty PTree()
    if(ids.size())
    {
        // Build PTree with i_cmd as type, using
        // command identifiers
        PTree cmd(i_cmd, ids);
        int row = 0;

        // Begin Looping Through Command Tokens in order to parse command
        for(std::vector<std::string>::iterator it = t_command.begin(); it != t_command.end(); ++it)
        {
            // Get Column Index t_command token represents
            int col = getCmdIndex(*it);

            // Get State_Array row value
            int next_row = state_array[row][col];

            // Debug Print
            //std::cout << "ROW: " << row << " Col: " << *it << "|" << col << " Next Row: " << next_row << std::endl;

            // If t_command token is valid
            if(next_row != -1)
            {
                if(row_insertion_identifier.find(row) != row_insertion_identifier.end())
                    cmd.Insert(row_insertion_identifier[row], *it);
                row = next_row;
            }
            // Else if current row is a success row, return valid parse tree
            else if(find(success_rows.begin(), success_rows.end(), row) != success_rows.end())
                return cmd;
            // Else return empty parse tree
            else return PTree();
        }

        // If Parsing Has Finished, Check if ending row is a success row
        if(find(success_rows.begin(), success_rows.end(), row) != success_rows.end())
            return cmd;
    }

    return PTree();
}

void CommandParser::setCommand(const std::string& command)
{
    this->command = command;
    getTokens(this->command);
}

std::string CommandParser::getCommand()
{
    return this->command;
}

void CommandParser::build_state_array()
{
    // Current State Array Configuration:
    /*===========================================================
     *  | Select | Random Str | * | , | From | Where | And | = |
     * -|--------|------------|---|---|------|-------|-----|---|
     * 0|    1   |     -1     |-1 |-1 |  -1  |  -1   | -1  |-1 |   Check For Starting Commands (e.g. Select Create Drop)
     * -|--------|------------|---|---|------|-------|-----|---|
     * 1|   -1   |      2     | 3 |-1 |  -1  |  -1   | -1  |-1 | Check For * Or Column Name (Add w/e token used in this row to column list/PTree) ---|
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |
     * 2|   -1   |     -1     |-1 | 1 |   4  |  -1   | -1  |-1 | If last token was a Column Name check for , or From                                 |
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |
     * 3|   -1   |     -1     |-1 |-1 |   4  |  -1   | -1  |-1 | If last token was * check for From                                                  |
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |
     * 4|   -1   |      5     | 6 |-1 |  -1  |  -1   | -1  |-1 | Check For * Or Table Name (Add w/e token used in this row to table list/PTree)      | - Specific Rows Used For Select Command
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |   (Note: More Will Be Needed For Conditionals)
     * 5|   -1   |     -1     |-1 | 4 |  -1  |   7   | -1  |-1 | If last token was a Table Name check for , or Where (Success Row)                   |
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |
     * 6|   -1   |     -1     |-1 |-1 |  -1  |   7   | -1  |-1 | If last token was * check for Where (Success Row)                                   |
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |
     * 7|        |            |   |   |      |       |     |   | Begin Conditional Parsing-----------------------------------------------------------|
     * -|--------|------------|---|---|------|-------|-----|---|
     * 8|        |            |   |   |      |       |     |   |
     * -|--------|------------|---|---|------|-------|-----|---|
     * 9|        |            |   |   |      |       |     |   |
     * -|--------|------------|---|---|------|-------|-----|---|
     *10|        |            |   |   |      |       |     |   |
     * -|--------|------------|---|---|------|-------|-----|---|
     *11|        |            |   |   |      |       |     |   |
     * -|--------|------------|---|---|------|-------|-----|---|
     *12|        |            |   |   |      |       |     |   |
     * -|--------|------------|---|---|------|-------|-----|---|
     */


    max_rows = DEFAULT_MAX_ROWS;
    max_cols = DEFAULT_MAX_COLS;

    allocate_array(state_array, max_rows, max_cols);
    initialize_array(state_array, max_rows, max_cols, -1);

    // Select State Array
    // Success States: Row 5, Row 6, Row 10
    // Add To Command List: Row 0 | CMD_ID
    // Add To Column List: Row 1 | COL_ID
    // Add To Table List: Row 4 | TABLE_ID
    fill_cell(state_array, 0, i_select, 1);
    fill_cell(state_array, 1, i_rand_str, 2);
    fill_cell(state_array, 1, i_star, 3);
    fill_cell(state_array, 2, i_comma, 1);
    fill_cell(state_array, 2, i_from, 4);
    fill_cell(state_array, 3, i_from, 4);
    fill_cell(state_array, 4, i_rand_str, 5);
    fill_cell(state_array, 4, i_star, 6);
    fill_cell(state_array, 5, i_comma, 4);

    fill_cell(state_array, 5, i_where, 7);
    fill_cell(state_array, 6, i_where, 7);
    fill_cell(state_array, 7, i_rand_str, 8);
    fill_cell(state_array, 8, i_equal, 9);
    fill_cell(state_array, 9, i_rand_str, 10);




    success_rows.push_back(5);
    success_rows.push_back(6);
    success_rows.push_back(10);
    row_insertion_identifier.insert(std::pair<int, std::string>(0, CMD_ID));
    row_insertion_identifier.insert(std::pair<int, std::string>(1, COL_ID));
    row_insertion_identifier.insert(std::pair<int, std::string>(4, TABLE_ID));
    row_insertion_identifier.insert(std::pair<int, std::string>(4, CONDITIONAL_ID));
}

void CommandParser::build_string_indices()
{
    string_indices.insert(std::pair<std::string, cmd_indices>("select", i_select));
    string_indices.insert(std::pair<std::string, cmd_indices>("from", i_from));
    string_indices.insert(std::pair<std::string, cmd_indices>("where", i_where));
    string_indices.insert(std::pair<std::string, cmd_indices>(",", i_comma));
    string_indices.insert(std::pair<std::string, cmd_indices>("and", i_and));
    string_indices.insert(std::pair<std::string, cmd_indices>("*", i_star));

    string_indices.insert(std::pair<std::string, cmd_indices>("=", i_equal));
}

void CommandParser::getTokens(const std::string& command)
{
    this->command = command;
    t_command.clear();
    str_tokenizer.setBlock(this->command);

    while(str_tokenizer.hasNext())
    {
        Token token = str_tokenizer.getNextToken();
        if(token.getType() != TYPE_SPACE)
        {
            std::string str = token.getToken();
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);
            t_command.push_back(str);
        }
    }
}

int CommandParser::getCmdIndex(const std::string& command)
{
    std::map<std::string, cmd_indices>::iterator i_cmd = string_indices.find(command);

    if(i_cmd != string_indices.end())
        return (*i_cmd).second;

    return i_rand_str;
}

std::vector<std::string> CommandParser::get_identifiers(int cmd)
{
    std::vector<std::string> returnMe;

    switch(cmd)
    {
    case i_select:
        returnMe.push_back(CMD_ID);
        returnMe.push_back(COL_ID);
        returnMe.push_back(TABLE_ID);
        returnMe.push_back(CONDITIONAL_ID);
        return returnMe;
    default:
        return returnMe;
    }
}
