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
        LinkedStack();                                     // Construtor vazio 
        LinkedStack(const LinkedStack& originStack);       // Construtor copia
        LinkedStack& operator=(const LinkedStack& originStack);
        ~LinkedStack();                                    // Destrutor
        
        void push(const Order& order);  // Adicionar ação na pilha
        Order pop();                    // Remover ação na pilha

        Order peek() const;             // Retorna o pedido do topo
        bool isEmpty() const;           // Verificar se a pilha está vaz

        void showCounterOrders() const;
};

#endif