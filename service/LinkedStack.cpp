#include "../models/LinkedStack.hpp"

using namespace std;

LinkedStack::LinkedStack() {
    top = nullptr;
}

// Cópia do Construtor
LinkedStack::LinkedStack(const LinkedStack& originStack) {
    top = nullptr;

    if (originStack.top != nullptr) {
        NodeStack* currentOther = originStack.top;
        NodeStack* lastInserted = nullptr;
        
        while (currentOther != nullptr) {
            NodeStack* newNode = new NodeStack();
            newNode->data = currentOther->data;
            newNode->next = nullptr;

            if (top == nullptr) {
                top = newNode;
            } else {
                lastInserted->next = newNode;
            }
            lastInserted = newNode;
            currentOther = currentOther->next;
        }
    }
}

// Operador de Atribuição (usado para backups - Add + Remove -> Items)
LinkedStack& LinkedStack::operator=(const LinkedStack& originStack) {
    if (this == &originStack) {
        return *this;
    }

    // 1. Limpa os nós existentes da pilha atual
    while (top != nullptr) {
        NodeStack* nextNode = top->next;
        delete top;
        top = nextNode;
    }

    // 2. Copia profundamente os nós da pilha de origem
    if (originStack.top != nullptr) {
        NodeStack* currentOther = originStack.top;
        NodeStack* lastInserted = nullptr;

        while (currentOther != nullptr) {
            NodeStack* newNode = new NodeStack();
            newNode->data = currentOther->data;
            newNode->next = nullptr;

            if (top == nullptr) {
                top = newNode;
            } else {
                lastInserted->next = newNode;
            }
            lastInserted = newNode;
            currentOther = currentOther->next;
        }
    }

    return *this;
}

// Destrutor
LinkedStack::~LinkedStack() {
    while (top != nullptr) {
        NodeStack* nextNode = top->next;
        delete top;
        top = nextNode;
    }
}

// Inserindo pedido na pilha
void LinkedStack::push(const Order& order) {
    NodeStack* newNode = new NodeStack();
    
    // Prepara o Nó
    newNode->data = order;
    newNode->next = top;
    
    top = newNode;
}

// Removendo pedido do topo da pilha
Order LinkedStack::pop() {
    if (isEmpty()) {
        cerr << " # Erro: Pilha vazia!" << endl;
        return Order();
    }

    // Pega Nó e Pedido
    NodeStack* nodeRemove = top;
    Order orderRemove = nodeRemove->data;
    
    // Desreferencia o nó topo, que será removido, para o proximo nó topo
    top = top->next;
    
    // Libera memoria do nó do antigo topo 
    delete nodeRemove;

    // retorna pedido
    return orderRemove;
}

// Retornando pedido do topo da pilha
Order LinkedStack::peek() const {
    if (isEmpty()) {
        cerr << " # Erro: Pilha vazia!" << endl;
        return Order();
    }

    return top->data;
}

// Verificando se a pilha está vazia
bool LinkedStack::isEmpty() const {
    return top == nullptr;
}

// Mostrando itens da Pilha
void LinkedStack::showCounterOrders() const {
    NodeStack* current = top;

    while (current != nullptr) {
        cout << "    Numero: " << current->data.getNumber() << endl;
        cout << "      Clinte: " << current->data.getClient() << endl;
        if (current->next != nullptr) cout << "------------------------------------------------" << endl;
        current = current->next;
    }
}