// This is a type agnostic binary search tree class
// Author: Eric Wistrand
// Date  : 10/23/2018
// 11/05/2018 - added _RECURSIVE_ define, and some non-recursive versions of things - ejw

#pragma once
#include <iostream>
#include <cstdlib>
#include <stack>
#include "type_name.h"
#define _RECURSIVE_
using namespace std;

template<typename T> class CBSTree
{

private:
    T value;
    CBSTree* left;
    CBSTree* right;
    CBSTree* root;

    void AddLeafRecursive(const T& value, CBSTree* pTree) {
        if (root == nullptr) {
            root = CreateLeaf(value);
        }
        else if (value < pTree->value) {
            if (pTree->left != nullptr)
            {
                AddLeafRecursive(value, pTree->left);
            }
            else {
                pTree->left = CreateLeaf(value);
            }
        }
        else if (value > pTree->value) {
            if (pTree->right != nullptr)
            {
                AddLeafRecursive(value, pTree->right);
            }
            else {
                pTree->right = CreateLeaf(value);
            }
        }
        else
        {
        cout << "The value " << value << " has already been added to the tree\n";
        }
    }
    void PrintInOrderRecursive(CBSTree* pTree)
    {
#if 0
        if (root != nullptr && pTree != nullptr) {
            if (pTree->left != nullptr)
            {
                PrintInOrderRecursive(pTree->left);
            }
            cout << pTree->value << " ";
            if (pTree->right != nullptr)
            {
                PrintInOrderRecursive(pTree->right);
            }
        }
        else {
            cout << "The tree is empty\n";
    }
#else
        if (root == nullptr) {
            cout << "The tree is empty\n";
        }
        if (pTree != nullptr) {
            if (pTree->left) {
                PrintInOrderRecursive(pTree->left);
            }
            cout << pTree->value << " ";
            if (pTree->right) {
                PrintInOrderRecursive(pTree->right);
            }
        }
#endif
    }
    CBSTree* ReturnNode(const T& value)
    {
        return ReturnNodeRecursive(value, root);
    }
    CBSTree* ReturnNodeRecursive(const T& value, CBSTree* pTree)
    {
        if (pTree != nullptr)
        {
            if (pTree->value == value)
            {
                return pTree;
            }
            else
            {
                if (value < pTree->value)
                {
                    return ReturnNodeRecursive(value, pTree->left);
                }
                else
                {
                    return ReturnNodeRecursive(value, pTree->right);
                }
            }
        }
        else
        {
            return nullptr;
        }
    }
    T FindSmallestRecursive(CBSTree* pTree)
    {
        if (root == nullptr || pTree == nullptr)
        {
            cout << "The tree is empty or the leaf is empty\n";
            return (T)NULL;
        }
        else
        {
            if (pTree->left != nullptr)
            {
                return FindSmallestRecursive(pTree->left);
            }
            else
            {
                return pTree->value;
            }
        }
    }
    void RemoveNodeRecursive(const T& value, CBSTree* parent)
    {
        if (root->value == value)
        {
            RemoveRootMatch();
            cout << "match is in root\n";
        }
        else
        {
            if (value < parent->value && parent->left != nullptr)
            {
                if (parent->left->value == value)
                {
                    RemoveMatch(parent, parent->left, true);
                    }
                else
                {
                    RemoveNodeRecursive(value, parent->left);
                }
            }
            else if (value > parent->value && parent->right != nullptr)
            {
                if (parent->right->value == value)
                {
                    RemoveMatch(parent, parent->right, false);
                }
                else
                {
                    RemoveNodeRecursive(value, parent->right);
                }
            }
            else
            {
                cout << "The value " << value << " was not in the tree\n";
            }
        }
    }
    void RemoveRootMatch() {
        CBSTree* delPtr = root;
        T rootValue = root->value;
        T smallestInRightSubtree;

        //root as zero children
        if (root->left == nullptr && root->right == nullptr)
        {
            root = nullptr;
            delete delPtr;
        }

        //root node has one child
        else if (root->left == nullptr && root->right != nullptr)
        {
            root = root->right;
            delPtr->right = nullptr;
            delete delPtr;
            cout << "The root node with value" << rootValue << " was deleted. "
                    << "The new root contains value " << root->value << endl;
                    
        }
        else if (root->left != nullptr && root->right == nullptr)
        {
            root = root->left;
            delPtr->left = nullptr;
            delete delPtr;
            cout << "The root node with value" << rootValue << " was deleted. "
                    << "The new root contains value " << root->value << endl;
        }

        //root node has two children
        else
        {
            smallestInRightSubtree = FindSmallestRecursive(root->right);
            RemoveNodeRecursive(smallestInRightSubtree, root);
            root->value = smallestInRightSubtree;
            cout << "The root value containing value " << rootValue <<" was overwritten with value " << root->value << endl;
        }
    }
    void RemoveMatch(CBSTree* parent, CBSTree* match, bool left)
    {
        if (root != nullptr)
        {
            CBSTree* delPtr;
            T matchValue = match->value;
            T smallestInRightSubtree;

            // matching node has zero children
            if (match->left == nullptr && match->right == nullptr)
            {
                delPtr = match;
                if (left == true)
                {
                    parent->left = nullptr;
                }
                else
                {
                    parent->right = nullptr;
                }
                delete delPtr;
                cout << "Root Node: The node containing value " << matchValue << " was removed\n";
            }
            // only right child exists
            else if (match->left == nullptr && match->right != nullptr)
            {
                if (left == true)
                {
                    parent->left = match->right;
                }
                else
                {
                    parent->right = match->right;
                }
                match->right = nullptr;
                delPtr = match;
                delete delPtr;
                cout << "Only right child existed: The node containing value " << matchValue << " was removed\n";
            }
            //only left child exists
            else if (match->left != nullptr && match->right == nullptr)
            {
                if (left == true)
                {
                    parent->left = match->left;
                }
                else
                {
                    parent->right = match->left;
                }
                match->left = nullptr;
                delPtr = match;
                delete delPtr;
                cout << "Only left child existed: The node containing value " << matchValue << " was removed\n";
            }
            //two Children
            else
            {
                smallestInRightSubtree = FindSmallestRecursive(match->right);
                RemoveNodeRecursive(smallestInRightSubtree, match);
                match->value = smallestInRightSubtree;

                cout << "Two Children:The node containing value " << matchValue << " was removed\n";
            }
        }
        else
        {
            cout << "Cannot remove match. The tree is empty\n";
        }
    }

public:
    CBSTree() { }
    CBSTree(const T &v) : value(v), left(nullptr), right(nullptr) { if (root == nullptr) { root = this; } }
   
    CBSTree* CreateLeaf(const T& value)
    {
        CBSTree* node = new CBSTree(value);
        node->left = nullptr;
        node->right = nullptr;

        return node;
    }  
    
    void AddLeaf(const T& value)
    {
        AddLeafRecursive(value, root);
    }    
    
    void PrintInOrder() 
    {
#ifdef _RECURSIVE_
        PrintInOrderRecursive(root);
#else // NON-RECURSIVE
        // check if root is null
        if (root == nullptr) { cout << "Tree is empty." << endl; return; }
        // move to the bottom of the list
        std::stack<CBSTree*> st;
        CBSTree* pTree = root;
        // load stack while traversing left
        while (pTree) {
            st.push(pTree);
            pTree = pTree->left;
        }

        // move up the tree and print as we go...
        while (!st.empty() && nullptr != (pTree = st.top())) {
            st.pop();
            cout << pTree->value << " ";
            //right side of tree 
            if (pTree->right) {
                pTree = pTree->right;
                while (pTree) {
                    st.push(pTree);
                    pTree = pTree->left;
                }
            }
        }
        cout << endl;
#endif
    }

    T ReturnRootValue()
    {
        if (root != nullptr)
        {
            return root->value;
        }
        else
        {
            return NULL;
        }
    }

void PrintChildren(const T& value)
    {
        CBSTree* pTree = ReturnNode(value);

        if (pTree != nullptr)
        {
            cout << "Parent Node = " << pTree->value << endl;
            if (pTree->left == nullptr)
            {
                cout << "Left Child = NULL" << endl;
            }
            else
            {
                cout << "Left Child = " << pTree->left->value << endl;
            }
            if (pTree->right == nullptr)
            {
                cout << "Right Child = NULL" << endl;
            }
            else
            {
                cout << "Right Child = " << pTree->right->value << endl;
            }
        }
        else
        {
            cout << "Value " << value << " is not in the tree\n";
        }
    }
    T FindSmallest()
    {
#ifdef _RECURSIVE_
        return FindSmallestRecursive(root);
#else  //NON-RECURSIVE
        CBSTree* pTree = root;
        while (pTree->left) {
            pTree = pTree->left;
        }
        return pTree->value;
#endif

    }
    void RemoveNode(const T& value) {
        if (root != nullptr) {
            RemoveNodeRecursive(value, root);
        }
        else
        {
            cout << "The tree is empty\n";
        }
    }
    T kthSmallestInBST(int k) {
        std::stack<CBSTree*> st;
        CBSTree* pTree = root;

        //load stack while traversing left
        while (pTree) {
            st.push(pTree);
            pTree = pTree->left;
        }

        // get items out in reverse order
        // decrement k to zero if we reach zero it means we found it.
        // if not it mean we have to move the right side of the tree
        while (nullptr != (pTree = st.top())) {
            st.pop();
            if (--k == 0) {
                //st.stackIndex = 0;
                break;
            }

            //right side of tree 
            if (pTree->right) {
                pTree = pTree->right;
                while (pTree) {
                    st.push(pTree);
                    pTree = pTree->left;
                }
            }
        }
        return pTree->value;
    }
};
