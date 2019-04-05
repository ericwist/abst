// BSTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "BSTree.h"

int main()
{
    clock_t start, finish;
    double duration;
    
    //Test loading and printing integers to binary tree
#if 0
    int TreeKeys[48] = { 50,76,21,4,32,64,15,52,14,100,83,2,3,70,87,80,\
        150,176,121,104,132,164,115,152,114,200,183,102,103,170,187,180,\
        250,276,221,204,232,264,215,252,214,300,283,202,203,270,287,280 };
#else
    int TreeKeys[16] = { 10,11,12,13,14,15,16,1,2,3,4,5,6,7,8,9 };

#endif
    CBSTree<int> myTree;
    int input=0;
//    string sinput = "";
    int treesize = sizeof(TreeKeys) / sizeof(*TreeKeys);
    for (int i = 0; i < treesize; ++i) {
        myTree.addLeaf(TreeKeys[i]);
    }
    cout << "Tree has been filled\n";
    myTree.NormalizeTheTree();
    cout << "Tree has been normalized\n";
    int depth = myTree.getTreeDepth();
    cout << "Tree depth is " << depth << "\n";
    bool bret_symmetric = myTree.isTreeSymmetric();
    if (bret_symmetric) {
        cout << "The tree is symmetric\n";
    }
    else {
        cout << "The tree is NOT symmetric\n";
    }
    
    while (input != -1)
    {
        cout << "Printing the inOrderTraversals, with timing\n";

        start = clock();
        myTree.inOrderTraversalRecurse();
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("In order recursive took %2.9f seconds\n", duration);

        start = clock();
        myTree.inOrderTraversalUseStack();
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("In order using stack took %2.9f seconds\n", duration);
        cout << "IN ORDER TRAVERSAL:" << "\n";
        start = clock();
        myTree.inOrderTraversalNoRecurseNoCollections();
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("In order using while loop took %2.9f seconds\n", duration);
        
        int ismall = myTree.findSmallest();
        cout << "Smallest value is " << ismall << endl;
        
        int isKthsmallest = myTree.kthSmallestInBST(4);
        cout << "4th smallest value is " << isKthsmallest << endl;
        
        int tvalint = 87;
        CBSTree<int>* successor = myTree.inOrderSuccessor(tvalint);
        if (successor) {
            cout << "The successor of " << tvalint << " is " << successor->getValue() << endl;
        }
        else {
            cout << "Could not find successor." << endl;
        }
        
        cout << "Print level zigzag down." << "\n";
        start = clock();
        myTree.printLevelsZigzagDown();
        cout << "Print levels Left-to-Right." << "\n";
        myTree.printLevelsLeftToRight();
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("Print by tree levels took %2.9f seconds\n", duration);
        cout << endl;
#if 0
        start = clock();
        myTree.printByLevelUsingQueue();
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("Print by tree level using queue took %2.9f seconds\n", duration);
        cout << endl;
#endif
        cout << "Enter a value to delete. Enter -1 to stop the process\n";
        cout << "Delete Node: ";
        cin >> input;
        {
            if (input != -1)
            {
                cout << endl;
                start = clock();
                myTree.removeNode(input);
                finish = clock();
                duration = (double)(finish - start) / CLOCKS_PER_SEC;
                printf("Remove operation took %2.9f seconds\n", duration);
                cout << endl;
            }
        }
    }
#if 0
    cout << "Now use same code for BST of strings."<< endl;
    cout << endl;

    //Test loading and printing strings
    string TreeKeysStr[16] = { "one","two","three","johnny","joey","jerry","joanne","bob","boris","butthead","beavis","ann","robbie","derek","donald","nathan" };
    CBSTree<string> myTreeStr;
    cout << "Printing the tree in order\nBefore adding strings\n";
    myTreeStr.PrintInOrder();
    for (int i = 0; i < 16; ++i) {
        myTreeStr.addLeaf(TreeKeysStr[i]);
    }
    cout << "Printing the tree in order\nAfter adding strings\n";
    myTreeStr.PrintInOrder();
    cout << endl;
    cout << "Print one and children\n";
    string s = "one";
    myTreeStr.printChildren(s);
    cout << "Print by tree level." << endl;
    myTreeStr.printLevelOrder();
    while (sinput != "stop")
    {
        //string small = myTreeStr.findSmallest();
        //cout << "Smallest value is " << small << endl;
        string isKthsmallestStr = myTreeStr.kthSmallestInBST(4);
        cout << "4th smallest value is " << isKthsmallestStr << endl;
        string sval = "beavis";
        CBSTree<string>* successor = myTreeStr.inOrderSuccessor(sval);
        cout << "The successor of " << sval << " is " << successor->getValue() << endl;
        myTreeStr.findSubstrings("an");
        cout << "Printing the tree in order\nAfter adding strings\n";
        myTreeStr.PrintInOrder();
        cout << endl;
        cout << "Print one and children\n";
        string s = "one";
        myTreeStr.printChildren(s);
        cout << "Print by tree level." << endl;
        myTreeStr.printLevelOrder();
        cout << "Enter a value to delete. Enter 'stop' to stop the process\n";
        cout << "Delete Node: ";
        cin >> sinput;
        {
            if (sinput != "stop")
            {
                cout << endl;
                start = clock();
                myTreeStr.removeNode(sinput);
                finish = clock();
                duration = (double)(finish - start) / CLOCKS_PER_SEC;
                //cout << "Remove operation took " << duration << " seconds\n";
                printf("Remove operation took %2.9f seconds\n", duration);

                myTreeStr.PrintInOrder();
                cout << endl;
            }
        }
    }
#endif
    return 0; 
}
