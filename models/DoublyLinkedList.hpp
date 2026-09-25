#ifndef _DOUBLY_LINKED_LIST_
#define _DOUBLY_LINKED_LIST_

#include <iostream>
#include "Order.hpp"

struct NodeList {
    Order data;
    NodeList* next;
    NodeList* previous;
};

class DoublyLinkedList {
    private:
        NodeList* head;
        NodeList* tail;
    public:
        DoublyLinkedList(/* args */);
        ~DoublyLinkedList();

        void insert(Order& order);          // insere um novo pedido
        void insertEnd(Order& order);       // insere um pedido no final da lista
        void insertIndex(Order& order, int index);  // insere um pedido em uma posição específica da lista
        int removeValue(int number);        // remove um pedido pelo número do pedido
        int search(int number);             // busca um pedido pelo número do pedido

        bool isEmpty() const;   // verifica se a lista está vazia

        void nextOrder();       // exibe o proximo pedido
        void previousOrder();   // exibe o pedido anterior
        
};

#endif