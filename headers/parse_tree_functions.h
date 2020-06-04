#ifndef BINARY_TREE_FUNCTIONS_H
#define BINARY_TREE_FUNCTIONS_H
#include <iostream>
#include "assert.h"
#include <vector>


//=================== Struct Definitions ===================
template <typename T>
struct sub_node
{
    sub_node(T item = T(), sub_node<T>* left = NULL, sub_node<T>* right = NULL):item(item), left(left), right(right) {}

    T item;
    sub_node<T>* left;
    sub_node<T>* right;
};

template <typename T>
struct root_node
{
    int tree_type;
    std::vector<sub_node<T>*> nodes;
};


//=================== Traverse Classes ===================
template <typename T>
class TraversePrint
{
public:
    void operator()(sub_node<T>* &node)
    {
        std::cout << "[" << node->item << "] ";
    }
};

template <typename T>
class TraverseDelete
{
public:
    void operator()(sub_node<T>* &node)
    {
        delete node;
        node = NULL;
    }
};

template <typename T>
class TraverseList
{
public:
    T skip;
    std::vector<T>* list;

    TraverseList(std::vector<T>* list, T identifier): list(list), skip(identifier) {}

    void operator()(sub_node<T>* &node)
    {
        if(node->item == skip)
            return;
        list->push_back(node->item);
    }
};


//=================== Functions Declarations ===================


/*==================================================
 *  Description:
 *      This function will insert a new sub tree
 *      into the root_node's vector member with the
 *      root of the new tree containing item T
 *
 * Param:
 *      node - non-null root_node
 *      T - identifier to insert
 *
 * Return:
 *      sub_node<T>* pointing to the root of the
 *      newly created sub tree
 *
 * Note:
 *      This is the only function specific to a
 *      parse tree. All other functions were copied
 *      over from BST project.
 */
template <typename T>
sub_node<T>* _insert_identifier(root_node<T>* &node, T);


/*==================================================
 * Note:
 *      All of the functions found below are 100%
 *      copied from the previously assigned Binary
 *      Search Tree project. The only thing that's
 *      changed is the name of the node structure.
 *==================================================*/

// BST Inerst Function
template <typename T>
sub_node<T>* _insert(sub_node<T>* &root, const T &item);


// BST Delete/Remove Node Function
template <typename T>
T _delete_node(sub_node<T>* &root, sub_node<T>* delete_me);

// BST Delete Tree Function
template <typename T>
void _delete_tree(sub_node<T>* &root);

// BST Search Function
template <typename T>
sub_node<T>* _search(sub_node<T>* &root, const T &item);

// BST In Order Traverse Function
template <class PROCESS, typename T>
void _in_order(PROCESS &f, const sub_node<T>* root);

// BST Post Order Traverse Function
template <class PROCESS, typename T>
void _post_order(PROCESS &f, const sub_node<T>* root);

// BST Pre Order Function
template <class PROCESS, typename T>
void _pre_order(PROCESS &f, const sub_node<T>* root);

// BST Find Parent Function
template <typename T>
sub_node<T>* _find_parent(sub_node<T>* &root, sub_node<T>* &findMe);

// BST Find Right Most Child Function
template <typename T>
sub_node<T>* _find_right_most(sub_node<T>* &root);

// BST Copy Function
template <typename T>
sub_node<T>* _copy(sub_node<T>* &root, sub_node<T>* const &other);



//=================== Function Definitions ====================

template <typename T>
sub_node<T>* _insert_identifier(root_node<T>* &node, T id)
{
    node->nodes.push_back(new sub_node<T>(id));
}

template <typename T>
sub_node<T>* _insert(sub_node<T>* &root, const T &item)
{
    if(!root)
        return root = new sub_node<T>(item);
    if(item < root->item)
        _insert(root->left, item);
    else
        _insert(root->right, item);
}

template <typename T>
T _delete_node(sub_node<T>* &root, sub_node<T>* delete_me)
{
    assert(root && delete_me);

    sub_node<T>* parent = _find_parent(root, delete_me);
    sub_node<T>* rightMost = _find_right_most(delete_me->left);
    T temp = delete_me->item;

    //If delete_me->left is null
    if(rightMost == NULL)
    {
        //If delete_me is not root link delete_me's parent to delete_me's children (only right)
        if(parent)
        {
            if(parent->left == delete_me)
                parent->left = delete_me->right;
            else
                parent->right = delete_me->right;
        }
        else //If delete_me is root set delete_me right to root
            root = delete_me->right;
    }
    else
    {
        //Get Parent of rightMost
        sub_node<T>* rightMostParent = _find_parent(root, rightMost);

        //Link Right Most Parent to Right Most Children (only left because right most)
        if(rightMostParent->left == rightMost)
            rightMostParent->left = rightMost->left;
        else
            rightMostParent->right = rightMost->left;

        //If delete_me is not root
        if(parent)
        {
            if(parent->left == delete_me)
                parent->left = rightMost;
            else
                parent->right = rightMost;
        }
        else //If delete_me is root
            root = rightMost;

        rightMost->left = delete_me->left;
        rightMost->right = delete_me->right;
    }

    delete delete_me;
    return temp;


}

template <typename T>
void _delete_tree(sub_node<T>* &root)
{
    TraverseDelete<T> deleter;
    _post_order(deleter, root);
    root = NULL;

}

template <typename T>
sub_node<T>* _search(sub_node<T>* &root, const T &item)
{
    if(!root)
        return NULL;

    if(root->item == item)
        return root;

    if(item < root->item)
       return _search(root->left, item);

    return _search(root->right, item);
}

template <class PROCESS, typename T>
void _in_order(PROCESS &f, sub_node<T>* root)
{
    if(!root)
        return;

    _in_order(f, root->left);
    f(root);
    _in_order(f, root->right);
}

template <class PROCESS, typename T>
void _post_order(PROCESS &f, sub_node<T>* root)
{
    if(!root)
        return;

    _post_order(f, root->left);
    _post_order(f, root->right);
    f(root);
}

template <class PROCESS, typename T>
void _pre_order(PROCESS &f, sub_node<T>* root)
{
    if(!root)
        return;

    f(root);
    _pre_order(f, root->left);
    _pre_order(f, root->right);
}

template <typename T>
sub_node<T>* _copy(const sub_node<T>* const &other)
{
    if(!other)
        return NULL;

    sub_node<T>* temp = new sub_node<T>(other->item);
    temp->left = _copy(other->left);
    temp->right = _copy(other->right);
    return temp;
}

template <typename T>
sub_node<T>* _find_parent(sub_node<T>* &root, sub_node<T>* &findMe)
{
    assert (root && findMe);

    if(root == findMe)
        return NULL;

    if(root->left == findMe || root->right == findMe)
        return root;

    if(findMe->item < root->item)
       return _find_parent(root->left, findMe);

    return _find_parent(root->right, findMe);
}

template <typename T>
sub_node<T>* _find_right_most(sub_node<T>* &root)
{
    if(!root)
        return NULL;

    if(root->right)
        return _find_right_most(root->right);
    else
        return root;
}

#endif // BINARY_TREE_FUNCTIONS_H
