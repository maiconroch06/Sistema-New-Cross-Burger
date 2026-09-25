#ifndef LINKED_STACK_HPP
#define LINKED_STACK_HPP

#include <iostream>
#include "Order.hpp"

struct NodeStack {
    Order data;
    NodeStack* next;
};

class LinkedStack {
    private:
        NodeStack* head;
        NodeStack* tail;
    public:
        LinkedStack(/* args */);
        ~LinkedStack();
        
        void push(const Order& order);  //
        Order pop();                    //

        bool isEmpty() const;
        int peek() const;
};
