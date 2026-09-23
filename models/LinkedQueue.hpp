#ifndef _LINKED_QUEUE_
#define _LINKED_QUEUE_

#include <iostream>
#include "Order.hpp"

using namespace std;

struct NodeQueue {
    Order data;
    NodeQueue* next;
};

class LinkedQueue {
    private:
        /* data */
    public:
        LinkedQueue(/* args */);
        ~LinkedQueue();
      
        int enqueue();
        int dequeue();

        bool isEmpty();
        int peek();
        
};

#endif