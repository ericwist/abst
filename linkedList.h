// This is a type agnostic array class
// Author: Eric Wistrand
// Date  : 11/28/2018

#pragma once
#include <iostream>
#include <cstdlib>
#include "type_name.h"

using namespace std;

template<typename T> class CLinkedList
{
private:
    T data;
    T* next;
public:
    CLinkedList() {}
    CLinkedList(const T &v) : value(v), next(nullptr) {}
    T getValue() { return value; }
};