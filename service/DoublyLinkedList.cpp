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

// insere um pedido no final da lista
void DoublyLinkedList::insertEnd(Order& order) {
    NodeList* newNode = new NodeList();

    newNode->data = order;
    newNode->next = nullptr;
    newNode->previous;

    tail->next = newNode;
    tail = newNode;

}

// // insere um pedido em uma posição específica da lista
// void DoublyLinkedList::insertIndex(Order& order, int index) {

// }

// remove um pedido pelo número do pedido
int DoublyLinkedList::removeValue(int number) {
    if (head == nullptr) {
        cout << "\n # ERRO: Lista vazia!" << endl;
        return -1;
    }

    NodeList* current = head;
    while (current != nullptr) {
        if (current->data.getNumber() == number) {
            if (current == head) {
                head = current->next;
            }
            if (current == tail) {
                tail = current->previous;
            }
            if (current->previous != nullptr) {
                current->previous->next = current->next;
            }
            if (current->next != nullptr) {
                current->next->previous = current->previous;
            }
            delete current;
            return 0;
        }
        current = current->next;

}

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