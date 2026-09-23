#ifndef _DOUBLY_LINKED_LIST_
#define _DOUBLY_LINKED_LIST_

#include <iostream>
#include "Order.hpp"

using namespace std;

struct NodeList {
    Order data;
    NodeList* next;
    NodeList* previous;
};

class DoublyLinkedList {
    private:
        /* data */
    public:
        DoublyLinkedList(/* args */);
        ~DoublyLinkedList();
        
};

#endif