#include "../models/KitchenLinkedQueue.hpp" 

using namespace std;

// Construtor
KitchenLinkedQueue::~KitchenLinkedQueue() {
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

    tail->next = newNode;
    tail = newNode;
}

// remove o primeiro elemento da fila
void KitchenLinkedQueue::dequeue() {
    if(head = nullptr) {
        NodeQueue* auxPtr = head;
        head = auxPtr->next;
        delete[] auxPtr;
    }
}

// verifica se a fila está vazia
bool KitchenLinkedQueue::isEmpty() const {
    return (head == nullptr);
}

// retorna o valor do primeiro elemento da fila sem removê-lo
int KitchenLinkedQueue::peek() const {
    if(isEmpty()) {
        cout << "\n # Erro: lista" << endl;
        return -1;
    }
    head->data.showOrder();
    return 0;
}

int KitchenLinkedQueue::getQuantatyOrders() const {
    return quantatyOrders;
}

void KitchenLinkedQueue::setQuantatyOrders(int quantatyOrders) {
    this->quantatyOrders = quantatyOrders;
}
