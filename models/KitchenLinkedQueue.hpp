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
        int quantatyOrders;             // contador de pedidos na fila
    public:
        KitchenLinkedQueue();
        ~KitchenLinkedQueue();
      
        void enqueue(Order& order);     // insere um novo elemento no final da fila
        void dequeue();                 // remove o primeiro elemento da fila

        void search(int number) const;
        
        bool isEmpty() const;           // verifica se a fila está vazia
        int peek() const;              // retorna o valor do primeiro elemento da fila sem removê-lo
        
        void showOrders() const;                    // exibe todos os pedidos da lista

        int getQuantatyOrders() const;
        void setQuantatyOrders(int quantatyOrders);


};

#endif