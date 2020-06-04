#include "parsetree.h"
#include <algorithm>

PTree::PTree()
{
    root = new root_node<std::string>();
}

PTree::PTree(const int& type, const std::vector<std::string>& identifiers)
{
    root = new root_node<std::string>();
    root->tree_type = type;

    for(std::string str : identifiers)
        _insert_identifier(root, str);
}

PTree::PTree(const PTree& other)
{
    root = new root_node<std::string>();

    for(typename std::vector<sub_node<std::string>*>::iterator it = other.root->nodes.begin(); it != other.root->nodes.end(); it++)
        root->nodes.push_back(_copy(*it));
}

PTree::~PTree()
{
    if(root && root->nodes.size())
        Clear();
    delete root;
}

PTree& PTree::operator=(const PTree& other)
{
    if(root->nodes.size())
        Clear();

    for(typename std::vector<sub_node<std::string>*>::iterator it = other.root->nodes.begin(); it != other.root->nodes.end(); it++)
        root->nodes.push_back(_copy(*it));
}

void PTree::InsertIdentifier(const std::string& identifier)
{
    _insert_identifier(root, identifier);
}

bool PTree::Insert(const std::string& identifier, const std::string& item)
{
    sub_node<std::string>* sub = getSubTree(identifier);

    if(!sub)
        return false;

    return _insert(sub, item);
}

void PTree::RemoveIdentifier(const std::string& identifier)
{
    sub_node<std::string>* id_node = getSubTree(identifier);

    if(id_node)
    {
        root->nodes.erase(std::find(root->nodes.begin(), root->nodes.end(), id_node));
        _delete_tree(id_node);
    }
}

void PTree::Remove(const std::string& identifier, const std::string& item)
{
    sub_node<std::string>* id_node = getSubTree(identifier);

    if(!id_node)
        return;

    sub_node<std::string>* item_node = _search(id_node, item);

    if(item_node)
        _delete_node(id_node, item_node);
}

sub_node<std::string>* PTree::getSubTree(const std::string& identifier) const
{
    for(typename std::vector<sub_node<std::string>*>::iterator it = root->nodes.begin(); it != root->nodes.end(); it++)
    {
        if((*it)->item == identifier)
            return *it;
    }

    return nullptr;
}

std::vector<std::string> PTree::getList(const std::string& identifier) const
{
    sub_node<std::string>* id_node = getSubTree(identifier);

    if(!id_node)
        return std::vector<std::string>();

    std::vector<std::string> list;
    TraverseList<std::string> get_list(&list, identifier);

    _in_order(get_list, id_node);
    return list;
}

void PTree::Clear()
{
    for(typename std::vector<sub_node<std::string>*>::iterator it = root->nodes.begin(); it != root->nodes.end(); it++)
        _delete_tree(*it);
    root->nodes.clear();
}

bool PTree::Empty()
{
    if(!root->nodes.size())
        return true;

    for(typename std::vector<sub_node<std::string>*>::iterator it = root->nodes.begin(); it != root->nodes.end(); it++)
    {
        if((*it)->left || (*it)->right)
            return false;
    }
    return true;

}

std::ostream& operator<<(std::ostream& out, const PTree& tree)
{
    for(typename std::vector<sub_node<std::string>*>::iterator it = tree.root->nodes.begin(); it != tree.root->nodes.end(); ++it)
    {
        out << (*it)->item << ": \n";
        std::vector<std::string> list = tree.getList((*it)->item);
        for(std::string str : list)
            out << "   " << str << std::endl;
        out << std::endl;
    }

    return out;
}
