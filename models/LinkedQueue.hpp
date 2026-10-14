#ifndef _LINKED_QUEUE_
#define _LINKED_QUEUE_

#include <iostream>
#include "Order.hpp"
#include "LinkedStack.hpp"
#include "DoublyLinkedList.hpp"

struct NodeQueue {
    Order data;
    NodeQueue* next;
    LinkedStack orderChanges;     // pilha de alterações de um pedido
};

class LinkedQueue {
    private:
        NodeQueue* head;
        NodeQueue* tail;
        int quantatyOrders;             // contador de pedidos na fila
        
        LinkedStack counterOrders;      // pilha de alterações de um pedido

    public:
        LinkedQueue();
        ~LinkedQueue();
      
        void enqueue(Order& order);       // insere um novo elemento no final da fila
        void dequeue();                   // remove o primeiro elemento da fila

        NodeQueue* search(int number);

        bool isEmpty() const;             // verifica se a fila está vazia
        int peek() const;                 // retorna o valor do primeiro elemento da fila sem removê-lo

        void undoOrder(int numberOrder);
        
        void showOrders() const;          // exibe todos os pedidos da lista
        void removeOrder(int index);      // remover pedido

        int getQuantatyOrders() const;
        void setQuantatyOrders(int quantatyOrders);

        void carrinho(const vector<int>& quantatyItems);

        // Funções de Menu
        void menuOperacoesBalcao();
        void menuRegisterOrder();
        void menuRemoveOrder();
        void menuSearchOrder();
        void menuManageOrder();
        void menuAddItem(int numberOrder);
        void menuRemoveItem(int numberOrder);


        void menuKitchen(DoublyLinkedList historicList);
};

#endif