#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <vector>
#include "set.h"
#include "pair.h"
#include "record.h"

using namespace std;


class table
{
public:
    table();





private:
    string tablename;
    vector<Pair<string,int> > col_index;
    vector<set<Pair<string,vector<int> > >*> index_array;
    string TwoD_temp[1][2];
    vector<record> _Database;
};

#endif // TABLE_H
