#ifndef _KITCHEN_LINKED_QUEUE_
#define _KITCHEN_LINKED_QUEUE_

#include <iostream>
#include "Order.hpp"
#include "ActionsLinkedStack.hpp"

struct NodeQueue {
    Order data;
    NodeQueue* next;
    ActionsLinkedStack stackOrders;   // pilha de alteraçoes de um pedido
};

class KitchenLinkedQueue {
private:
    NodeQueue* head;
    NodeQueue* tail;
    int quantatyOrders;

public:
    KitchenLinkedQueue();
    ~KitchenLinkedQueue();

    void enqueue(Order& order);       // insere um novo elemento no final da fila
    void dequeue();                   // remove o primeiro elemento da fila

    NodeQueue* search(int number);
    void removeOrder(int index);      // remover pedido
    void undoOrder(int numberOrder);

    bool isEmpty() const;             // verifica se a fila está vazia
    int peek() const;                 // retorna o valor do primeiro elemento da fila sem removê-lo
    void showOrders() const;          // exibe todos os pedidos da lista

    int getQuantatyOrders() const;
    void setQuantatyOrders(int quantatyOrders);
};

#endif