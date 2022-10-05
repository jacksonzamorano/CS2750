//
//  DoubleLinkedNode.hpp
//  AirlineTicket
//
//  Created by Jackson Zamorano on 10/3/22.
//

#ifndef DoubleLinkedNode_hpp
#define DoubleLinkedNode_hpp

#include <stdio.h>

template <typename T> class DoubleLinkedNode {
public:
    DoubleLinkedNode* prev;
    DoubleLinkedNode* next;
    T* data;
};


#endif /* DoubleLinkedNode_hpp */
