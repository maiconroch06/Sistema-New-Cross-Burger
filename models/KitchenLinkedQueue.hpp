#ifndef _KITCHEN_LINKED_QUEUE_
#define _KITCHEN_LINKED_QUEUE_

#include <iostream>
#include "Order.hpp"
#include "ActionsLinkedStack.hpp"

struct NodeQueue {
    Order data;
    NodeQueue* next;
    ActionsLinkedStack stackOrders;     // pilha de alterações de um pedido
};

class KitchenLinkedQueue {
    private:
        NodeQueue* head;
        NodeQueue* tail;
        int quantatyOrders;             // contador de pedidos na fila

    public:
        KitchenLinkedQueue();
        ~KitchenLinkedQueue();
      
        void enqueue(Order& order);       // insere um novo elemento no final da fila
        void dequeue();                   // remove o primeiro elemento da fila

        void search(int number) const;
        
        void addItem(int number);     // vai adicionar um ou mais item na lista de itens um pedido especifico
        void popItem(int number);     // vai remover um ou mais item na lista de itens um pedido especifico

        bool isEmpty() const;             // verifica se a fila está vazia
        int peek() const;                 // retorna o valor do primeiro elemento da fila sem removê-lo
        
        void showOrders() const;          // exibe todos os pedidos da lista
        void removeOrder(int index);               // remover pedido

        int getQuantatyOrders() const;
        void setQuantatyOrders(int quantatyOrders);

        void carrinho(const vector<int>& quantatyItems);

        // Funções de Menu
        void menuAddItem();
        void menuOperacoesBalcao();
        void menuCadastrarPedido();
        void menuRemoverPedido(int index);
};

#endif