#include "../models/ActionsLinkedStack.hpp"

using namespace std;

ActionsLinkedStack::ActionsLinkedStack() {
    top = nullptr;
}

ActionsLinkedStack::~ActionsLinkedStack() {
    while (top != nullptr) {
        NodeStack* nextNode = top->next;
        delete top;
        top = nextNode;
    }
}

void ActionsLinkedStack::push(const Order& order) {
    NodeStack* newNode = new NodeStack();
    
    // Prepara o Nó
    newNode->data = order;
    newNode->next = top;
    
    top = newNode;
}

Order ActionsLinkedStack::pop() {
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

int ActionsLinkedStack::peek() const {
    if (isEmpty()) {
        cerr << " # Erro: Pilha vazia!" << endl;
        return -1;
    }

    top->data.showOrder();
    return 0;
}

bool ActionsLinkedStack::isEmpty() const {
    return top == nullptr;
}