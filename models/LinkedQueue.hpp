#ifndef _LINKED_QUEUE_
#define _LINKED_QUEUE_

#include <iostream>
#include "Order.hpp"

struct NodeQueue {
    Order data;
    NodeQueue* next;
};

class LinkedQueue {
    private:
        NodeQueue* head;
        NodeQueue* tail;
    public:
        LinkedQueue(/* args */);
        ~LinkedQueue();
      
        void enqueue(Order& order);     // insere um novo elemento no final da fila
        void dequeue();                 // remove o primeiro elemento da fila

        bool isEmpty() const;           // verifica se a fila está vazia
        NodeQueue* peek() const;        // retorna o valor do primeiro elemento da fila sem removê-lo
        
};

#endif