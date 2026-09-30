#include "../models/HistoricDoublyLinkedList.hpp"

using namespace std;

// construtor
HistoricDoublyLinkedList::HistoricDoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

// destrutor
HistoricDoublyLinkedList::~HistoricDoublyLinkedList() {
    while (head != nullptr) {
        NodeList* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

// insere um novo pedido inserido no início
void HistoricDoublyLinkedList::insert(Order& order) {
    NodeList* newNode = new NodeList();
    
    // Prepara o Nó
    newNode->data = order;
    newNode->next = head;
    newNode->previous = nullptr;
    
    if (tail == nullptr) {        // Caso a lista esteja vazia, tail aponta para o Novo Nó
        tail = newNode;
    } else {                      // Caso a lista não esteja vazia, o proximo 
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

    if (isEmpty()) {
        newNode->previous = nullptr;
        head = newNode;
        tail = newNode;
    } else {
        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
    }
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
    newNode->previous->next = newNode;

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

    cout << "|         # Erro: Pedido nao encontrado!       |" << endl;

    return -2;
}

// busca um pedido pelo número do pedido
int HistoricDoublyLinkedList::search(int number) const {
    if (isEmpty()) {
        cout << "|          # ERRO: Lista vazia!        " << endl;
        return -1;
    }

    NodeList* current = head;
    while (current != nullptr) {
        if (current->data.getNumber() == number) {
            current->data.showOrder();
            return 0;
        }
        current = current->next;
    }

    cout << "|         # Erro: Pedido nao encontrado!       |" << endl;
    return -2;
}

// verifica se a lista está vazia
bool HistoricDoublyLinkedList::isEmpty() const {
    return head == nullptr;
}

// exibe o proximo pedido
int HistoricDoublyLinkedList::nextOrder(int index) const {
    if (isEmpty()) {
        cout << "\n # ERRO: Lista vazia!" << endl;
        return -1;
    }
    
    NodeList* current = head;
    while(current != nullptr) {
        if(current->data.getNumber() == index) {
            return current->data.getNumber() + 1;
        }
        current = current->next;
    }
    return 1;
}

// exibe o pedido anterior
int HistoricDoublyLinkedList::previousOrder(int index) const {
    if (isEmpty()) {
        cout << "\n # ERRO: Lista vazia!" << endl;
        return -1;
    }

    NodeList* current = head;
    while (current != nullptr && current->data.getNumber() != index) {
        current = current->next;
    }
    
    if (current == nullptr) {
        cout << "\n # Aviso: Voce esta no primeiro pedido!" << endl;
        return tail->data.getNumber();
    }

    return current->data.getNumber() - 1;
}

// exibe todos os pedidos da lista
void HistoricDoublyLinkedList::showOrders() const {
    NodeList* current = head;

    while (current != nullptr) {
        current->data.showOrder();
        cout << "| > Anterior: "<< current->previous << endl;
        cout << "| > Atual: " << current << endl;
        cout << "| > Proximo: "<< current->next << endl;
        
        current = current->next;
    }

}