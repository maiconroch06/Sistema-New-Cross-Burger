#include "../models/LinkedStack.hpp"

using namespace std;

LinkedStack::LinkedStack() {
    top = nullptr;
}

LinkedStack::~LinkedStack() {
    while (top != nullptr) {
        NodeStack* nextNode = top->next;
        delete top;
        top = nextNode;
    }
}

void LinkedStack::push(const Order& order) {
    NodeStack* newNode = new NodeStack();
    
    // Prepara o Nó
    newNode->data = order;
    newNode->next = top;
    
    top = newNode;
}

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

int LinkedStack::peek() const {
    if (isEmpty()) {
        cerr << " # Erro: Pilha vazia!" << endl;
        return -1;
    }

    top->data.showOrder();
    return 0;
}

bool LinkedStack::isEmpty() const {
    return top == nullptr;
}

void LinkedStack::showCounterOrders() const {
    NodeStack* current = top;

    while (current != nullptr) {
        cout << "    Numero: " << current->data.getNumber() << endl;
        cout << "      Clinte: " << current->data.getClient() << endl;
        if (current->next != nullptr) cout << "------------------------------------------------" << endl;
        current = current->next;
    }
}