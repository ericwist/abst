// This is a type agnostic binary search tree class
// Author: Eric Wistrand
// Date  : 10/23/2018

#pragma once
#include <iostream>
#include <cstdlib>
#include "type_name.h"
using namespace std;

template<typename T> class CBSTree
{

private:
    T value;
    CBSTree* left;
    CBSTree* right;
    CBSTree* root;

    void AddLeafPrivate(const T& value, CBSTree* Ptr) {
        if (root == nullptr) {
            root = CreateLeaf(value);
        }
        else if (value < Ptr->value) {
            if (Ptr->left != nullptr)
            {
                AddLeafPrivate(value, Ptr->left);
            }
            else {
                Ptr->left = CreateLeaf(value);
            }
        }
        else if (value > Ptr->value) {
            if (Ptr->right != nullptr)
            {
                AddLeafPrivate(value, Ptr->right);
            }
            else {
                Ptr->right = CreateLeaf(value);
            }
        }
        else
        {
        cout << "The value " << value << " has already been added to the tree\n";
        }
    }
    void PrintInOrderPrivate(CBSTree* Ptr)
    {
        if (root != nullptr && Ptr != nullptr) {
            if (Ptr->left != nullptr)
            {
                PrintInOrderPrivate(Ptr->left);
            }
            cout << Ptr->value << " ";
            if (Ptr->right != nullptr)
            {
                PrintInOrderPrivate(Ptr->right);
            }
        }
        else {
            cout << "The tree is empty\n";
        }
    }
    CBSTree* ReturnNode(const T& value)
    {
        return ReturnNodePrivate(value, root);
    }
    CBSTree* ReturnNodePrivate(const T& value, CBSTree* Ptr)
    {
        if (Ptr != NULL)
        {
            if (Ptr->value == value)
            {
                return Ptr;
            }
            else
            {
                if (value < Ptr->value)
                {
                    return ReturnNodePrivate(value, Ptr->left);
                }
                else
                {
                    return ReturnNodePrivate(value, Ptr->right);
                }
            }
        }
        else
        {
            return NULL;
        }
    }
    T FindSmallestPrivate(CBSTree* Ptr)
    {
        if (root == NULL || Ptr == NULL)
        {
            cout << "The tree is empty or the leaf is empty\n";
            return NULL;
        }
        else
        {
            if (Ptr->left != NULL)
            {
                return FindSmallestPrivate(Ptr->left);
            }
            else
            {
                return Ptr->value;
            }
        }
    }
    void RemoveNodePrivate(const T& value, CBSTree* parent)
    {
        if (root->value == value)
        {
            RemoveRootMatch();
            cout << "match is in root\n";
        }
        else
        {
            if (value < parent->value && parent->left != NULL)
            {
                if (parent->left->value == value)
                {
                    RemoveMatch(parent, parent->left, true);
                    }
                else
                {
                    RemoveNodePrivate(value, parent->left);
                }
            }
            else if (value > parent->value && parent->right != NULL)
            {
                if (parent->right->value == value)
                {
                    RemoveMatch(parent, parent->right, false);
                }
                else
                {
                    RemoveNodePrivate(value, parent->right);
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
        if (root->left == NULL && root->right == NULL)
        {
            root = NULL;
            delete delPtr;
        }

        //root node has one child
        else if (root->left == NULL && root->right != NULL)
        {
            root = root->right;
            delPtr->right = NULL;
            delete delPtr;
            cout << "The root node with value" << rootValue << " was deleted. "
                    << "The new root contains value " << root->value << endl;
                    
        }
        else if (root->left != NULL && root->right == NULL)
        {
            root = root->left;
            delPtr->left = NULL;
            delete delPtr;
            cout << "The root node with value" << rootValue << " was deleted. "
                    << "The new root contains value " << root->value << endl;
        }

        //root node has two children
        else
        {
            smallestInRightSubtree = FindSmallestPrivate(root->right);
            RemoveNodePrivate(smallestInRightSubtree, root);
            root->value = smallestInRightSubtree;
            cout << "The root value containing value " << rootValue <<" was overwritten with value " << root->value << endl;
        }
    }
    void RemoveMatch(CBSTree* parent, CBSTree* match, bool left)
    {
        if (root != NULL)
        {
            CBSTree* delPtr;
            T matchValue = match->value;
            T smallestInRightSubtree;

            //matching node has zero children
            if (match->left == NULL && match->right == NULL)
            {
                delPtr = match;
                if (left == true)
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
                delete delPtr;
                cout << "Root Node: The node containing value " << matchValue << " was removed\n";
            }
            else if (match->left == NULL && match->right != NULL)
            {
                if (left == true)
                {
                    parent->left = match->right;
                }
                else
                {
                    parent->right = match->right;
                }
                match->right = NULL;
                delPtr = match;
                delete delPtr;
                cout << "Only right child existed: The node containing value " << matchValue << " was removed\n";
            }
            else if (match->left != NULL && match->right == NULL)
            {
                if (left == true)
                {
                    parent->left = match->left;
                }
                else
                {
                    parent->right = match->left;
                }
                match->left = NULL;
                delPtr = match;
                delete delPtr;
                cout << "Only left child existed: The node containing value " << matchValue << " was removed\n";
            }

            //Two Children
            else
            {
                smallestInRightSubtree = FindSmallestPrivate(match->right);
                RemoveNodePrivate(smallestInRightSubtree, match);
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
    CBSTree() { };
    CBSTree(const T &v) : value(v), left(nullptr), right(nullptr) { if (root == NULL) { root = this; } }
   
    CBSTree* CreateLeaf(const T& value)
    {
        CBSTree* node = new CBSTree(value);
        node->left = nullptr;
        node->right = nullptr;

        return node;
    }  
    
    void AddLeaf(const T& value)
    {
        AddLeafPrivate(value, root);
    }    
    
    void PrintInOrder() 
    {
        PrintInOrderPrivate(root);
    }

    T ReturnRootValue()
    {
        if (root != NULL)
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
        CBSTree* Ptr = ReturnNode(value);

        if (Ptr != NULL)
        {
            cout << "Parent Node = " << Ptr->value << endl;
            if (Ptr->left == NULL)
            {
                cout << "Left Child = NULL" << endl;
            }
            else
            {
                cout << "Left Child = " << Ptr->left->value << endl;
            }
            if (Ptr->right == NULL)
            {
                cout << "Right Child = NULL" << endl;
            }
            else
            {
                cout << "Right Child = " << Ptr->right->value << endl;
            }
        }
        else
        {
            cout << "Value " << value << " is not in the tree\n";
        }
    }
    T FindSmallest()
    {
        return FindSmallestPrivate(root);
    }
    void RemoveNode(const T& value) {
        if (root != NULL) {
            RemoveNodePrivate(value, root);
        }
        else
        {
            cout << "The tree is empty\n";
        }
    }

};
