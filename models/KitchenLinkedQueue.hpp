#ifndef _KITCHEN_LINKED_QUEUE_
#define _KITCHEN_LINKED_QUEUE_

#include <iostream>
#include "Order.hpp"

struct NodeQueue {
    Order data;
    NodeQueue* next;
};

class KitchenLinkedQueue {
    private:
        NodeQueue* head;
        NodeQueue* tail;
    public:
        KitchenLinkedQueue();
        ~KitchenLinkedQueue();
      
        void enqueue(Order& order);     // insere um novo elemento no final da fila
        void dequeue();                 // remove o primeiro elemento da fila

        bool isEmpty() const;           // verifica se a fila está vazia
        int peek() const;              // retorna o valor do primeiro elemento da fila sem removê-lo      
};

#endif