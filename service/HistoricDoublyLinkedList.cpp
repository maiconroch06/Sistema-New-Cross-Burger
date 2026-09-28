#include "../models/HistoricDoublyLinkedList.hpp"

using namespace std;

// construtor
HistoricDoublyLinkedList::HistoricDoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

// destrutor
HistoricDoublyLinkedList::~HistoricDoublyLinkedList() {
    NodeList* current = head;
    while (current != nullptr) {
        NodeList* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// insere um novo pedido inserido no início
void HistoricDoublyLinkedList::insert(Order& order) {
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
void HistoricDoublyLinkedList::insertEnd(Order& order) {
    NodeList* newNode = new NodeList();

    newNode->data = order;
    newNode->next = nullptr;
    newNode->previous = tail;

    tail->next = newNode;
    tail = newNode;

}

// insere um pedido em uma posição específica da lista
void HistoricDoublyLinkedList::insertIndex(Order& order, int index) {

// O metodo pode ser melhor reutilizando funções já prontas

    if (isEmpty()) {
        cout << "\n # ERRO: Lista vazia!" << endl;
        return;
    }

    NodeList* newNode = new NodeList();
    newNode->data = order;

    // Caso a posição seja no inicio
    if (index == 0) {
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
        return;
    }

    NodeList* current = head;
    
    // Vai percorrer até encontrar a possição de mudança
    for(int currentCount = 0 ; current != nullptr && currentCount != index ; currentCount++) {
        current = current->next;
    }
    
    if (current == nullptr) {
        cerr << "\n # Erro: indice nao encontrado!" << endl;
        return;
    }

    // Ele vai assumir a posição do qual o indice foi definido

    // Inserir no meio
    

    // Inserir no fim
    if (current == tail) {
        newNode->next = nullptr;
        newNode->previous = tail;

        tail->next = newNode;
        tail = newNode;
    }

    return;

}

// remove um pedido pelo número do pedido
int HistoricDoublyLinkedList::removeValue(int number) {
    if (isEmpty()) {
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

    cout << "\n # Erro: Pedido nao encontrado!" << endl;
    return -2;
}

// busca um pedido pelo número do pedido
int HistoricDoublyLinkedList::search(int number) {
    if (isEmpty()) {
        cout << "\n # ERRO: Lista vazia!" << endl;
        return -1;
    }

    NodeList* current = head;
    while (current != nullptr) {
        if (current->data.getNumber()) {
            current->data.printOrder();
            return 0;
        }
        current = current->next;
    }

    cout << "\n # Erro: Pedido nao encontrado!" << endl;
    return -2;
}


// verifica se a lista está vazia
bool HistoricDoublyLinkedList::isEmpty() const {
    return head == nullptr;
}

// exibe o proximo pedido
void HistoricDoublyLinkedList::nextOrder() {
    if (isEmpty()) {
        cout << "\n # ERRO: Lista vazia!" << endl;
        return;
    }

}

// exibe o pedido anterior
void HistoricDoublyLinkedList::previousOrder() {
}

// exibe todos os pedidos da lista
void HistoricDoublyLinkedList::printList() const {
    NodeList* current = head;

    while (current != nullptr) {
        current->data.printOrder();
        current = current->next;
    }
}