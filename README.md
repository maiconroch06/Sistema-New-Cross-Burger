#ifndef ORDER_HPP
#define ORDER_HPP

#include <iostream>
#include <string>

class Order {
private:
    int number;
    std::string client;
    std::string items[100];
    int itemsCount;
    float total;

public:
    Order(); // Construtor por omissão necessário
    Order(int number, const std::string& client, const std::string items[], int itemsCount, float total);
    ~Order();

    void printOrder() const;

    int getNumber() const;
    std::string getClient() const;
    float getTotal() const;
};

#endif

#include "../models/Order.hpp"

using namespace std;

Order::Order() {
    this->number = 0;
    this->client = "";
    this->items[100] = {};
    this->total = 0.0;
}

Order::Order(int number, const string& client, const string items[], int itemsCount, float total) {
    this->number = number;
    this->client = client;
    this->itemsCount = itemsCount;
    this->total = total;

    for (int i = 0; i < itemsCount && i < 100; i++) {
        this->items[i] = items[i];
    }
}

Order::~Order() {

}

void Order::printOrder() const {
    cout << "========== PEDIDO "<< this->getNumber() <<" ============" << endl;
    cout << " > " << this->getClient() << endl;
    for (int i = 0; i < 100; i++) {
        if (this->items[i].empty()) {
            break;
        }
        cout << " > " << this->items[i] << endl;
    }
    cout << " > " << this->getTotal() << endl;
    cout << "================================" << endl;
}

int Order::getNumber() const {
    return number;
}

std::string Order::getClient() const {
    return client;
}

float Order::getTotal() const {
    return total;
}

#ifndef _DOUBLY_LINKED_LIST_
#define _DOUBLY_LINKED_LIST_

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

        void insert(Order& order);          // insere um novo pedido inserido no início
        void insertEnd(Order& order);       // insere um pedido no final da lista
        void insertIndex(Order& order, int index);  // insere um pedido em uma posição específica da lista
        int removeValue(int number);        // remove um pedido pelo número do pedido
        int search(int number);             // busca um pedido pelo número do pedido

        bool isEmpty() const;        // verifica se a lista está vazia

        void nextOrder();            // exibe o proximo pedido
        void previousOrder();        // exibe o pedido anterior
        
        void printList() const;      // exibe todos os pedidos da lista
};

#endif

#include "../models/DoublyLinkedList.hpp"

using namespace std;

// construtor
DoublyLinkedList::DoublyLinkedList(/* args */) {
    head = nullptr;
    tail = nullptr;
}

// destrutor
DoublyLinkedList::~DoublyLinkedList() {

}

// insere um novo pedido inserido no início
void DoublyLinkedList::insert(Order& order) {
    NodeList* newNode = new NodeList();
    
    //Order order = Order(number, client, items, total);

    // O novo ponteiro guarda o objeto pedido.
    newNode->data = order;

    // O ponteiro next do novo nó aponta para o antigo head.
    newNode->next = head;
    newNode->previous = nullptr;
    
    
    // Se a lista estava vazia, o tail aponta para o novo primeiro nó.
    // Se a lista não estiver vaia, o ponteiro previous do antigo head aponta para o novo nó.
    if (tail == nullptr) {
        tail = newNode;
    } else {
        head->previous = newNode;
    }
    
    // O head aponta para o novo nó.
    head = newNode;

}

// // insere um pedido no final da lista
// void DoublyLinkedList::insertEnd(Order& order) {

// }

// // insere um pedido em uma posição específica da lista
// void DoublyLinkedList::insertIndex(Order& order, int index) {

// }

// // remove um pedido pelo número do pedido
// int DoublyLinkedList::removeValue(int number) {
// }

// // busca um pedido pelo número do pedido
// int DoublyLinkedList::search(int number) {
// }

// verifica se a lista está vazia
bool DoublyLinkedList::isEmpty() const {
    return head == nullptr;
}

// // exibe o proximo pedido
// void DoublyLinkedList::nextOrder() {
// }

// // exibe o pedido anterior
// void DoublyLinkedList::previousOrder() {
// }

// exibe todos os pedidos da lista
void DoublyLinkedList::printList() const {
    NodeList* current = head;

    while (current != nullptr) {
        current->data.printOrder();
        current = current->next;
    }
}

#include <iostream>
#include "models/Order.hpp"
#include "models/DoublyLinkedList.hpp"

using namespace std;

int main() {
    DoublyLinkedList listOrders;

    string items1[] = {"Hamburguer", "Batata Frita"};
    string items2[] = {"Pizza GG", "Coca Zero"};
    string items3[] = {"Milk Shake", "Batata Frita"};

    Order order1(1, "Maicon", items1, 2, 25.50f);
    Order order2(2, "Estudante", items2, 2, 68.50f);
    Order order3(3, "Rocha", items3, 2, 25.50f);

    listOrders.insert(order1);
    listOrders.insert(order2);
    listOrders.insert(order3);

    listOrders.printList();

    return 0;
}