// This is a type agnostic binary search tree class
// Author: Eric Wistrand
// Date  : 10/23/2018
// 11/05/2018 - added _RECURSIVE_ define, and some non-recursive versions of things - ejw

#pragma once
#include <iostream>
#include <cstdlib>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include "type_name.h"
#include "macros.h"
//#define _RECURSIVE_
using namespace std;

template<typename T> class CBSTree
{
private:
    T value;
    CBSTree* left;
    CBSTree* right;
    CBSTree* parent;
    CBSTree* root;
    int size;
    void AddLeafRecursive(const T& value, CBSTree* pTree) {

         if (value < pTree->value) {
            if (pTree->left)
            {
                AddLeafRecursive(value, pTree->left);
            }
            else {
                pTree->left = createLeaf(value);
                pTree->left->parent = pTree;
                //cout << "Adding left value: " << value << " whose parent value is: " << pTree->value << "\n";
                //cout << endl;
            }
        }
        else if (value > pTree->value) {
            if (pTree->right)
            {
                AddLeafRecursive(value, pTree->right);
            }
            else {
                pTree->right = createLeaf(value);
                pTree->right->parent = pTree;
                //cout << "Adding right value: " << value << " whose parent value is: " << pTree->value << "\n";
                //cout << endl;
            }
        }
        else
        {
        cout << "The value " << value << " has already been added to the tree\n";
        }
    }

    int maxDepth(CBSTree* p)
    {
        if (p == nullptr)
            return 0;
        else
        {
            int lDepth = maxDepth(p->left);
            int rDepth = maxDepth(p->right);

            if (lDepth > rDepth) 
            {
                return(lDepth + 1);
            }
            else 
            {
                return(rDepth + 1);
            }
        }
    }

    void PrintInOrderRecursive(CBSTree* pTree)
    {
        if (pTree) {
            if (pTree->left) {
                PrintInOrderRecursive(pTree->left);
            }
            cout << pTree->value << " ";
            if (pTree->right) {
                PrintInOrderRecursive(pTree->right);
            }
        }
    }

    CBSTree* ReturnNode(const T& value)
    {
        return ReturnNodeRecursive(value, root);
    }

    CBSTree* ReturnNodeRecursive(const T& value, CBSTree* pTree)
    {
        if (pTree)
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
            if (pTree->left)
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
            if (value < parent->value && parent->left)
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
            else if (value > parent->value && parent->right)
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

    void RemoveRootMatch()
    {
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
        else if (root->left == nullptr && root->right)
        {
            root = root->right;
            delPtr->right = nullptr;
            delete delPtr;
            cout << "The root node with value" << rootValue << " was deleted. "
                    << "The new root contains value " << root->value << endl;
                    
        }
        else if (root->left && root->right == nullptr)
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
        if (root)
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
            else if (match->left == nullptr && match->right)
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
            else if (match->left && match->right == nullptr)
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

    bool areTreesMirrorImages(CBSTree *pTree1, CBSTree *pTree2)
    {
        // base cases
        if (pTree1 == nullptr && pTree2 == nullptr)
            return true;

        if (pTree1 == nullptr || pTree2 == nullptr)
            return false;

        if (pTree1->value != pTree2->value)
            return false;

        // compare the left side of pTree1 to the right side of pTree2
        if (areTreesMirrorImages(pTree1->left, pTree2->right) == false)
            return false;

        // ... and compare the right side of pTree1 to the left side of pTree2
        return areTreesMirrorImages(pTree1->right, pTree2->left);
    }

    bool areTreesIdentical(CBSTree *pTree1, CBSTree *pTree2)
    {

        if (pTree1 == nullptr && pTree2 == nullptr)
            return true;

        if (pTree1 == nullptr || pTree2 == nullptr)
            return false;

        if (pTree1->value != pTree2->value)
            return false;

        return (pTree1->value == pTree2->value &&
            areTreesIdentical(pTree1->left, pTree2->left) &&
            areTreesIdentical(pTree1->right, pTree2->right));
    }

    void printGivenLevel(CBSTree* pTree, int level)
    {
        if (pTree == nullptr)
            return;
        if (level == 1)
            cout << pTree->value << " ";
        else if (level > 1)
        {
            printGivenLevel(pTree->left, level - 1);
            printGivenLevel(pTree->right, level - 1);
        }
    }

    void storeBSTNodes(CBSTree* node, vector<CBSTree*> &nodes)
    {
        if (!node)
            return;
        storeBSTNodes(node->left, nodes);
        nodes.push_back(node);
        storeBSTNodes(node->right, nodes);

    }

    CBSTree* buildTreeUtil(vector<CBSTree*> &nodes, int start, int end)
    {
        if (start > end)
            return nullptr;

        int mid = (start + end) / 2;
        
        CBSTree* local_root = nodes[mid];

        local_root->left = buildTreeUtil(nodes, start, mid-1);
        local_root->right = buildTreeUtil(nodes, mid + 1, end);

        return local_root;
    }
public:
    CBSTree() {}
    CBSTree(const T &v, CBSTree* r) : value(v), left(nullptr), right(nullptr), parent(nullptr), root(r)
    {
        if (root == nullptr)
        {
            root = this;
        }
    }
    T getValue() { return value; }
    ~CBSTree() {
        //SAFE_DELETE();
    }
    CBSTree* createLeaf(const T& value)
    {
        CBSTree* node = new CBSTree(value, root);
        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;
        ++size;
        return node;
    }  
    
    void addLeaf(const T& value)
    {
        if (root == nullptr) {
            root = createLeaf(value);
            return;
        }
        AddLeafRecursive(value, root);
    }    
    
    T returnRootValue()
    {
        if (root)
        {
            return root->value;
        }
        else
        {
            return NULL;
        }
    }

    void printChildren(const T& value)
    {
        CBSTree* pTree = ReturnNode(value);

        if (pTree)
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

    T findSmallest()
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

    void removeNode(const T& value) {
        if (root) {
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
        // if not it means we have to move the right side of the tree
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
    
    bool isTreeSymmetric() {
        if (root == nullptr)
            return true;
        return areTreesMirrorImages(root->left, root->right);
    }

    void findSubstrings(const T& val)
    {
        if (root == nullptr) { cout << "Tree is empty." << endl; return; }
        std::queue<CBSTree*> queue;
        queue.push(root);
        while (queue.size())
        {
            CBSTree * pTree = queue.front();
            queue.pop();
            if (pTree->left) {
                queue.push(pTree->left);
            }

            std::size_t found = pTree->value.find(val);
            if (found != std::string::npos)
                std::cout << "*Substring* '" << val << "' found in: " << pTree->value << '\n';

            if (pTree->right) {
                queue.push(pTree->right);
            }
        }
    }

    void printByLevelUsingQueue() {
        if (root == nullptr) { cout << "Tree is empty." << endl; return; }
        std::queue<CBSTree*> queue;
        queue.push(root);
        while (queue.size()) {
            CBSTree * pTree = queue.front();
            queue.pop();
            if (pTree->left) {
                queue.push(pTree->left);
            }
            cout << pTree->value << " ";
            if (pTree->right) {
                queue.push(pTree->right);
            }
        }
        cout << endl;
    }

    void printLevelOrderRecurse()
    {
        int h = maxDepth(root);
        for (int i = 1; i <= h; i++)
        {
            printGivenLevel(root, i);
            cout << endl;
        }
    }
    
    CBSTree * inOrderSuccessor(const T& value)
    {
        CBSTree* pTree = nullptr;
        if (nullptr == (pTree = ReturnNode(value))){
            cout << "Node with value: " << value << " does not exist." << endl;
            return nullptr;
        }
        cout << "Looking for successor of : " << value << endl;
        //if right side exists, loop to leftmost, then return
        if (pTree->right) {
            pTree = pTree->right;
            while (pTree->left) {
                pTree = pTree->left;
            }
            return pTree;
        }
        // There was nothing on the right 
        // so go up to parent to look for next
        CBSTree* p = pTree->parent;
        while (p && pTree == p->right)
        {
            pTree = p;
            p = p->parent;
        }
        return p;
    }



    //define and code the three ways of traversing BST.
    //1. In-Order
void inOrderTraversalNoRecurseNoCollections()
{
    if (root == nullptr) { cout << "Tree is empty." << endl; return; }
    CBSTree *cur, *pre;
    cur = root;
    while (cur)
    {
        if (cur->left == nullptr) {
            cout << cur->value << " ";
            cur = cur->right;
        }
        else
        {
            // Find the inorder predeccessor of cur
            pre = cur->left;
            while ((pre->right) && (pre->right != cur))
                pre = pre->right;

            // Set cur as right child of its inorder predecessor
            if (pre->right == nullptr) 
            {
                pre->right = cur; // Set, but restore below
                cur = cur->left;
            }
            else
            {
                // restore to original tree
                pre->right = nullptr;
                cout << cur->value << " ";
                cur = cur->right;
            }
        }
    }
    cout << endl;
}
void inOrderTraversalRecurse()
{
    if (root == nullptr) { cout << "Tree is empty." << endl; return; }
    PrintInOrderRecursive(root);
    cout << endl;
}

void inOrderTraversalUseStack()
{
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
}
    //2. Pre-Order
    //3. Post-Order

void printLevelsZigzagDown()
{
    // direction boolean
    bool right = true;

    // declare two stacks
    stack<CBSTree*>curr;
    stack<CBSTree*>next;

    curr.push(root);

    while (!curr.empty())
    {
        // Pop out of stack
        CBSTree* temp = curr.top();
        curr.pop();

        if (temp)
        {
            cout << temp->getValue() << " ";

            //
            if (right)
            {
                if (temp->left)
                    next.push(temp->left);
                if (temp->right)
                    next.push(temp->right);
            }
            else
            {
                if (temp->right)
                    next.push(temp->right);
                if (temp->left)
                    next.push(temp->left);
            }
        }
        if (curr.empty())
        {
            right = !right;
            swap(curr, next);
            cout << endl;
        }
    }
}

void printLevelsLeftToRight()
{
    // declare two queues
    queue<CBSTree*>curr;
    queue<CBSTree*>next;

    curr.push(root);

    while (!curr.empty())
    {
        // Pop out of queue
        CBSTree* temp = curr.front();
        curr.pop();
        if (temp) {
            cout << temp->getValue() << " ";
            if (temp->left)
                next.push(temp->left);
            if (temp->right)
                next.push(temp->right);
        }
        if (curr.empty())
        {
            swap(curr, next);
            cout << endl;
        }
    }
}

int getTreeDepth()
{
    return maxDepth(root);
}

CBSTree* buildTree()
{
    vector<CBSTree*> nodes;
    storeBSTNodes(root, nodes);
    int n = nodes.size();
    return buildTreeUtil(nodes, 0, n - 1);
}

void NormalizeTheTree()
{
    root = buildTree();
}

};
