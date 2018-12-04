// This is a type agnostic array class
// Author: Eric Wistrand
// Date  : 11/28/2018

#pragma once
#include <iostream>
#include <cstdlib>
#include "type_name.h"

using namespace std;

template<typename T> class CArray {
private:
    int size;
    T *m_array;

public:
    CArray(int s)
        :size(s)
    {
        m_array = new T[size];
        memset(m_array, 0, size*(sizeof(m_array)/sizeof(m_array[0])));
    }

    void setArray(int elem, const T& val) {
        m_array[elem] = val;
    }

    void dumpArray() {
        cout << "Dump contents of array" << endl;
        for (int i = 0; i < size; ++i) {
            cout << m_array[i] << " ";
        }
        cout << endl;
    }

    void reverseArray() {
        if (m_array == nullptr){
            return;
        }
        T temp;
        T *e = &m_array[size - 1];
        T *b = &m_array[0];

        while (e > b) {
            temp = *e;
            *e = *b;
            *b = temp;
            ++b;
            --e;
        }
        return;
    }
    //only for integers
     struct{
        bool operator()(const T a,const T b) const
        {
            return a < b;
        }
    }customLess;
    void Sort() {
        int n = sizeof(m_array) / sizeof(m_array[0]);
        sort(m_array, m_array + (size*n), customLess);
    }
    // this works for both string and int.  
    void bubbleSort() {
        T temp;
        for (int i = 1; i < size; i++) {
            for (int j = (size - 1); j >= i; j--) {
                if (m_array[j-1] > m_array[j]) {
                    temp = m_array[j - 1];
                    m_array[j - 1] = m_array[j];
                    m_array[j] = temp;
                }
            }
        }
    }
    int moveZerosToEnd() {
        if (m_array == nullptr) {
            return 0;
        }
        int count = 0;
        for (int i = 0; i < size; ++i)
        {
            if (m_array[i] != 0)
            {
                m_array[count++] = m_array[i];
            }
        }
        while (count < size)
        {
            m_array[count++] = 0;
        }
    }
};

//std::size_t found = pTree->value.find(val);
//if (found != std::string::npos)
//std::cout << "*Substring* '" << val << "' found in: " << pTree->value << '\n';
