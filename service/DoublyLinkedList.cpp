#include "../models/DoublyLinkedList.hpp"

using namespace std;

// construtor
DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

// destrutor
DoublyLinkedList::~DoublyLinkedList() {
    NodeList* current = head;
    while (current != nullptr) {
        NodeList* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// insere um novo pedido inserido no início
void DoublyLinkedList::insert(Order& order) {
    NodeList* newNode = new NodeList();
    
    newNode->data = order;
    newNode->next = head;
    newNode->previous = nullptr;
    
    if (tail == nullptr) {
        tail = newNode;
    } else {
        head->previous = newNode;
    }
    
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