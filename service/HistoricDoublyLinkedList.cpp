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

    return;

}

// insere um pedido no final da lista
void HistoricDoublyLinkedList::insertEnd(Order& order) {
    NodeList* newNode = new NodeList();

    newNode->data = order;
    newNode->next = nullptr;
    newNode->previous = tail;

    tail->next = newNode;
    tail = newNode;

    // caso a lista esteja vazia, o novo nó será o head
    if (isEmpty()) {
        head = newNode;
    }

    return;

}

// insere um pedido em uma posição específica da lista
void HistoricDoublyLinkedList::insertIndex(Order& order, int index) {
    if (isEmpty()) {
        cout << "\n # ERRO: Lista vazia!" << endl;
        return;
    }

    // Caso a posição seja no inicio
    if (index == 0) {
        insert(order);
        return;
    }

    NodeList* current = head;
    
    // Vai percorrer até encontrar a possição de mudança
    for(int currentCount = 0 ; current != nullptr && currentCount != index ; currentCount++) {
        current = current->next;
    }

    // Se o current for nulo, significa que o indice não foi encontrado
    if (current == nullptr) {
        cerr << "\n # Erro: indice nao encontrado!" << endl;
        return;
    }

    // Inserir no fim
    if (current == tail) {
        insertEnd(order);
        return;   
    }

    // Inserir no meio
    NodeList* newNode = new NodeList();
    newNode->data = order;

    newNode->next = current;
    newNode->previous = current->previous;
    
    current->previous = newNode;

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