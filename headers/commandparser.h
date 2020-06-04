#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include "parsetree.h"
#include "stokenizer.h"
#include <map>
#include <string>
#include <vector>

// Constants Used To Identify Tokens and Build
// the parse tree
const std::string CMD_ID = "command";
const std::string COL_ID = "columns";
const std::string TABLE_ID = "tables";
const std::string CONDITIONAL_ID = "conditionals";

// Enum representing column indices
// in the state_array
enum cmd_indices
{
    i_select = 0,
    i_from,
    i_where,
    i_comma,
    i_and,
    i_star,
    i_rand_str,
    i_equal,
};

class CommandParser
{
public:

    // Defualt Constructor/String Constructor
    CommandParser(std::string = std::string());

    // Function that actually does the parsing
    PTree parseCommand();

    // Function That Sets the command to be parsed
    void setCommand(const std::string& command);

    // Function that returns the command
    std::string getCommand();


private:

    const static int DEFAULT_MAX_ROWS = 100;
    const static int DEFAULT_MAX_COLS = 100;

    /* Description:
     *      Map used to convert string tokens into
     *      state_array column indices
     *
     * Pair:
     *      string - valid column string
     *      cmd_indices - integer from enum defined
     *                    above that represents a
     *                    column index in state_array
     */
    std::map<std::string, cmd_indices> string_indices;

    /* Description:
     *      Map that holds the indices of state_array
     *      rows used to add tokens to the parse tree
     *
     * Pair:
     *      int - state_array row
     *      string - identifier used to insert
     *               into the parse tree
     */
    std::map<int, std::string> row_insertion_identifier;

    // Vector used to identify success rows
    std::vector<int> success_rows;

    // State Array Pointer
    int** state_array;
    int max_rows, max_cols;

    // Vector Contained Tokens Built From Command String
    std::vector<std::string> t_command;
    STokenizer str_tokenizer;

    // Actual Command
    std::string command;

    // Function Used To Allocate/Initialize State Array
    // NOTE: In order to add more commands you must edit
    //       this function.
    void build_state_array();

    // Function used to initialize string_indices map
    // NOTE: In order to add more commands you must edit
    //       this function.
    void build_string_indices();

    // Function Used To Tokenize command into t_command
    // NOTE: In order to add more commands you must edit
    //       this function definition.
    void getTokens(const std::string& command);

    // Function Used To Get State Array Column Indices From String
    int getCmdIndex(const std::string& command);

    // Function Used To Get A List Of Identifiers From a Command
    // that are needed to intialize the parse tree
    std::vector<std::string> get_identifiers(int cmd);

};

#endif // COMMANDPARSER_H
