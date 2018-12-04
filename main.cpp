// BSTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "BSTree.h"
#include "array.h"
using namespace std;

int main()
{
    clock_t start, finish;
    double duration;
#if 1
    // int array
    int TreeKeys[18] = {50,76,21,4,32,21,15,50,0,14,100,83,0,2,3,70,87,80};
    // load array
    CArray<int> a(18);
    for (int i = 0; i < 18; ++i) {
        a.setArray(i, TreeKeys[i]);
    }
    a.dumpArray();
    std::cout << "Move zeros to end array\n";
    int numberOfZeros = a.moveZerosToEnd();
    std::cout << numberOfZeros << " zeros found in array\n"; 
    a.dumpArray();
    std::cout << "Sort array\n";
    a.Sort();
    a.dumpArray();
    std::cout << "Reverse array\n";
    a.reverseArray();
    a.dumpArray();
    // string array
    string TreeKeysStr[16] = {"one","two","three","johnny","joey","jerry","joanne","bob","boris","butthead","beavis","ann","robbie","derek","donald","nathan"};
    // load array
    CArray<string> astr(16);
    for (int i = 0; i < 16; ++i) {
        astr.setArray(i, TreeKeysStr[i]);
    }
    astr.dumpArray();
    std::cout << "Sort array\n";
    astr.bubbleSort();
    astr.dumpArray();
    std::cout << "Reverse array\n";
    astr.reverseArray();
    astr.dumpArray();

#else
    //Test loading and printing integers to binary tree
    int TreeKeys[16] = { 50,76,21,4,32,64,15,52,14,100,83,2,3,70,87,80 };
    CBSTree<int> myTree;
    int input=0;
    string sinput = "";
    cout << "Printing the tree in order\nBefore adding numbers\n";
    myTree.PrintInOrder();
    for (int i = 0; i < 16; ++i) {
        myTree.AddLeaf(TreeKeys[i]);
    }
    cout << "Printing the tree in order\nAfter adding numbers\n";
    myTree.PrintInOrder();
    bool bret_symmetric = myTree.isTreeSymmetric();
    if (bret_symmetric) {
        cout << "The tree is symmetric\n";
    }
    else {
        cout << "The tree is NOT symmetric\n";
    }
    

    
    while (input != -1)
    {
        int ismall = myTree.FindSmallest();
        cout << "Smallest value is " << ismall << endl;
        int isKthsmallest = myTree.kthSmallestInBST(4);
        cout << "4th smallest value is " << isKthsmallest << endl;
        int tvalint = 87;
        CBSTree<int>* successor = myTree.inOrderSuccessor(tvalint);
        if (successor != nullptr) {
            cout << "The successor of " << tvalint << " is " << successor->getValue() << endl;
        }
        else {
            cout << "Could not find successor." << endl;
        }
        cout << "Print by tree level." << endl;
        myTree.printLevelOrder();
        cout << endl;        
        cout << "Enter a value to delete. Enter -1 to stop the process\n";
        cout << "Delete Node: ";
        cin >> input;
        {
            if (input != -1)
            {
                cout << endl;
                start = clock();
                myTree.RemoveNode(input);
                finish = clock();
                duration = (double)(finish - start) / CLOCKS_PER_SEC;
                //cout << "Remove operation took " << duration << " seconds\n";
                printf("Remove operation took %2.9f seconds\n", duration);

                myTree.PrintInOrder();
                cout << endl;
            }
        }
    }

    cout << "Now use same code for BST of strings."<< endl;
    cout << endl;

    //Test loading and printing strings
    string TreeKeysStr[16] = { "one","two","three","johnny","joey","jerry","joanne","bob","boris","butthead","beavis","ann","robbie","derek","donald","nathan" };
    CBSTree<string> myTreeStr;
    cout << "Printing the tree in order\nBefore adding strings\n";
    myTreeStr.PrintInOrder();
    for (int i = 0; i < 16; ++i) {
        myTreeStr.AddLeaf(TreeKeysStr[i]);
    }
    cout << "Printing the tree in order\nAfter adding strings\n";
    myTreeStr.PrintInOrder();
    cout << endl;
    cout << "Print one and children\n";
    string s = "one";
    myTreeStr.PrintChildren(s);
    cout << "Print by tree level." << endl;
    myTreeStr.printLevelOrder();
    while (sinput != "stop")
    {
        string small = myTreeStr.FindSmallest();
        cout << "Smallest value is " << small << endl;
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
        myTreeStr.PrintChildren(s);
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
                myTreeStr.RemoveNode(sinput);
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


