#include <iostream>
#include "commandparser.h"

using namespace std;
void test_parse_tree();

/*--------------------------------------
 *               WARNING
 * --------------------------------------
 * With the current implementation
 * any keywords (e.g. SELECT, AND, FROM)
 * used for column and table names will
 * will return an error (empty PTree)
 * when parsed.
 *
 * You might be able to fix this, if
 * you want to, by changing the value
 * of all -1 cells (EXCEPT ,) in the
 * state_array on row 1 to the value
 * of 2 and the -1 cells (NOT ,) on row
 * 4 to the value of 5.
 *
 * To view the state_array and edit
 * it go to the function
 * build_state_array() in the
 * ParseCommand class.
 *
 * Note: I haven't had time to test
 * this fix. Good Luck!
 * --------------------------------------*/

int main(int argc, char *argv[])
{

    //test_parse_tree();
    std::string args;

    while(true)
    {
        cout << endl << endl << "===================================\n[Command]: ";

        getline(cin, args);
        fflush(stdin);

        CommandParser Cparser(args);
        PTree select = Cparser.parseCommand();

        if(!select.Empty()){
            cout << endl << select << endl << endl;
        }
        else
            cout << "Error: Invalid Command!\n\n";

        // Here is an example of the getList function
        // If the identifier parameter is not found within
        // the tree, or the column list is empty, the function
        // will return an empty vector.
        cout << "Get List Example\nColumn List: ";
        vector<string> col_list = select.getList(COL_ID);

        for(vector<string>::iterator it = col_list.begin(); it != col_list.end(); ++it)
            cout << *it << " ";
        cout << endl << endl;
    }
    return 1;
}

void test_parse_tree(){
    PTree pt;
    cout << "Created PTree\n";

    pt.InsertIdentifier(CMD_ID);
    pt.InsertIdentifier(COL_ID);
    pt.InsertIdentifier(TABLE_ID);
    pt.InsertIdentifier(CONDITIONAL_ID);
    cout << "Added Identifiers:\n\n";
    cout << pt << endl << endl;

    pt.Insert(CMD_ID, "select");
    pt.Insert(COL_ID, "firstName");
    pt.Insert(COL_ID, "lastName");
    pt.Insert(TABLE_ID, "names");

    cout << pt << endl << endl;

    vector<string> ids;
    ids.push_back(CMD_ID);
    ids.push_back(COL_ID);
    ids.push_back(TABLE_ID);
    ids.push_back(CONDITIONAL_ID);

    cout << "Calling vector constuctor\n";
    PTree pt1(0, ids);
    cout << pt1 << endl << endl;
}
