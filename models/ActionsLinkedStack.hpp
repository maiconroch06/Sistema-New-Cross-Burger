#ifndef _ACTIONS_LINKED_STACK_HPP
#define _ACTIONS_LINKED_STACK_HPP

#include <iostream>
#include "Order.hpp"

struct NodeStack {
    Order data;
    NodeStack* next;
};

class ActionsLinkedStack {
    private:
        NodeStack* top;
    public:
        ActionsLinkedStack();           // Construtor 
        ~ActionsLinkedStack();          // Destrutor
        
        void push(const Order& order);  // Adicionar ação na pilha
        Order pop();                    // Remover ação na pilha

        int peek() const;               // Buscar primeir pidido na pilha
        bool isEmpty() const;           // Verificar se a pilha está vaz
};

#endif