// BSTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "BSTree.h"

using namespace std;

int main()
{
    clock_t start, finish;
    double duration;
    //Test loading and printing integers
    int TreeKeys[16] = {50,76,21,4,32,64,15,52,14,100,83,2,3,70,87,80 };
    CBSTree<int> myTree;
    int input=0;
    string sinput = "";;
    cout << "Printing the tree in order\nBefore adding numbers\n";
    myTree.PrintInOrder();
    for (int i = 0; i < 16; ++i) {
        myTree.AddLeaf(TreeKeys[i]);
    }
    cout << "Printing the tree in order\nAfter adding numbers\n";
    myTree.PrintInOrder();
    cout << endl;
    
    int ismall = myTree.FindSmallest();
    cout << "Smallest value is " << ismall << endl;
    int k = 4;
    int isKthsmallest = myTree.kthSmallestInBST(k);
    cout << k << "th smallest value is " << isKthsmallest << endl;

    cout << "Enter a value to delete. Enter -1 to stop the process\n";
    while (input != -1)
    {
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

    string small = myTreeStr.FindSmallest();
    cout << "Smallest value is " << small << endl;

    k = 4;
    string isKthsmallestStr = myTreeStr.kthSmallestInBST(k);
    cout << k << "th smallest value is " << isKthsmallestStr << endl;

    cout << "Enter a value to delete. Enter 'stop' to stop the process\n";
    while (sinput != "stop")
    {
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

    return 0; 
}
