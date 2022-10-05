//
//  DoubleLinkedList.hpp
//  AirlineTicket
//
//  Created by Jackson Zamorano on 10/3/22.
//

#ifndef DoubleLinkedList_hpp
#define DoubleLinkedList_hpp

#include <stdio.h>
#include <functional>
#include "DoubleLinkedNode.hpp"

using std::function;

template <class T>
class DoubleLinkedList {
private:
    DoubleLinkedNode<T>* head;
public:
    DoubleLinkedNode<T>* getHead();
    void insertHead(T* item);
    T* valueWhere(function<bool (const T&)> fn);
    int indexWhere(function<bool (const T&)> fn);
    void each(function<void (const T&)> fn);
//    DoubleLinkedNode<T>*
};

#endif /* DoubleLinkedList_hpp */
