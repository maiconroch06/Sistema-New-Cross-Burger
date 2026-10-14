#ifndef _LINKED_STACK_HPP
#define _LINKED_STACK_HPP

#include <iostream>
#include "Order.hpp"

struct NodeStack {
    Order data;
    NodeStack* next;
};

class LinkedStack {
    private:
        NodeStack* top;
    public:
        LinkedStack();           // Construtor 
        ~LinkedStack();          // Destrutor
        
        void push(const Order& order);  // Adicionar ação na pilha
        Order pop();                    // Remover ação na pilha

        int peek() const;               // Buscar primeir pidido na pilha
        bool isEmpty() const;           // Verificar se a pilha está vaz

        void showCounterOrders() const;
};

#endif