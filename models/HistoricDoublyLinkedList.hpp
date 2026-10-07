#ifndef _HISTORIC_DOUBLY_LINKED_LIST_
#define _HISTORIC_DOUBLY_LINKED_LIST_

#include <iostream>
#include "Order.hpp"

struct NodeList {
    Order data;
    NodeList* next;
    NodeList* previous;
};

class HistoricDoublyLinkedList {
    private:
        NodeList* head;
        NodeList* tail;
        
    public:
        HistoricDoublyLinkedList();
        ~HistoricDoublyLinkedList();

        void insert(Order& order);                  // insere um novo pedido inserido no início
        void insertEnd(Order& order);               // insere um pedido no final da lista
        void insertIndex(Order& order, int index);  // insere um pedido em uma posição específica da lista
        int removeValue(int number);                // remove um pedido pelo número do pedido
        int search(int number) const;               // busca um pedido pelo número do pedido

        bool isEmpty() const;                       // verifica se a lista está vazia

        int nextOrder(int index) const;             // exibe o proximo pedido
        int previousOrder(int index) const;         // exibe o pedido anterior
        
        void showOrders() const;                    // exibe todos os pedidos da lista

        // Funções do Menu Histórico
        void menuExibirHistoricoPedidos();
};

#endif