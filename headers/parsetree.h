#ifndef PARSETREE_H
#define PARSETREE_H
#include "parse_tree_functions.h"

/* Note: I missed the day our proffessor explained
 *       parse trees, so this class might be totally
 *       different then how he said to make it.
 */

class PTree
{
public:
    PTree();
    PTree(const int& type, const std::vector<std::string>& identifiers);
    PTree(const PTree& other);
   ~PTree();

    PTree& operator=(const PTree& other);

    // Returns tree type
    int getType() { return root->tree_type; }

    // Sets tree type
    void setType(const int& type) { root->tree_type = type; }

    // Function Used To Add Identifier Sub Tree to PTree
    void InsertIdentifier(const std::string& identifier);

    // Function Used To Insert Item into Identifier Sub Tree
    bool Insert(const std::string& identifier, const std::string& item);

    // Function Used To Remove Identifier Sub Tree
    void RemoveIdentifier(const std::string& identifier);

    // Function Used To Remove Item from Identifier Sub Tree
    void Remove(const std::string& identifier, const std::string& item);

    // Function Used To Clear PTree Completely
    void Clear();

    // Function Used To Retreive Sub Tree based on identifier
    sub_node<std::string>* getSubTree(const std::string& identifier) const;

    // Function Returns a Vector containing all items within Identifier Sub Tree
    std::vector<std::string> getList(const std::string& identifier) const;

    // Checks If PTree is empty
    bool Empty();

    friend std::ostream& operator<<(std::ostream& out, const PTree& tree);
private:
    root_node<std::string>* root;
};

#endif // PARSETREE_H
