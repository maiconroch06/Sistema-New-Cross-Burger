#include "../models/KitchenLinkedQueue.hpp" 

using namespace std;

// Construtor
KitchenLinkedQueue::KitchenLinkedQueue() {
    head = nullptr;
    tail = nullptr;
    quantatyOrders = 0;
}

// Destrutor
KitchenLinkedQueue::~KitchenLinkedQueue() {
    while (head != nullptr) {
        NodeQueue* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

// insere um novo elemento no final da fila
void KitchenLinkedQueue::enqueue(Order& order) {
    NodeQueue* newNode = new NodeQueue();

    int number = getQuantatyOrders() + 1;
    order.setNumber(number);

    setQuantatyOrders(number);

    newNode->data = order;
    newNode->next = nullptr;

    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// remove o primeiro elemento da fila
void KitchenLinkedQueue::dequeue() {
    if (isEmpty()) {
        cout << "\n # ERRO: Fila vazia!" << endl;
        return;
    }

    NodeQueue* auxPtr = head;
    head = head->next;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete auxPtr;
    quantatyOrders--;
}

void KitchenLinkedQueue::search(int number) const {
    if (isEmpty()) {
        cout << "\n # ERRO: Fila vazia!" << endl;
        return;
    }

    NodeQueue* current = head;
    while (current != nullptr && current->data.getNumber() != number) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "|         # Erro: Pedido nao encontrado!       |" << endl;
        return;
    }

    current->data.showOrder();
}

// verifica se a fila está vazia
bool KitchenLinkedQueue::isEmpty() const {
    return (head == nullptr);
}

// retorna o valor do primeiro elemento da fila sem removê-lo
int KitchenLinkedQueue::peek() const {
    if (isEmpty()) {
        cout << "\n # Erro: Fila vazia!" << endl;
        return -1;
    }
    head->data.showOrder();
    return 0;
}

// exibe todos os pedidos da lista, porém, mostra apenas o número do pedido e o nome do cliente
void KitchenLinkedQueue::showOrders() const {
    NodeQueue* current = head;

    while (current != nullptr) {
        cout << "Nº Pedido: " << current->data.getNumber() << endl;
        cout << "Nome Clinte: " << current->data.getClient() << endl;
        cout << "----------------------------------------" << endl;
        current = current->next;
    }
}

int KitchenLinkedQueue::getQuantatyOrders() const {
    return quantatyOrders;
}

void KitchenLinkedQueue::setQuantatyOrders(int quantatyOrders) {
    this->quantatyOrders = quantatyOrders;
}