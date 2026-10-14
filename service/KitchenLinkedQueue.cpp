#include "../models/KitchenLinkedQueue.hpp"
#include "../utils/TerminalUtils.hpp"

using namespace std;

KitchenLinkedQueue::KitchenLinkedQueue() {
    head = nullptr;
    tail = nullptr;
    quantatyOrders = 0;
}

KitchenLinkedQueue::~KitchenLinkedQueue() {
    while (head != nullptr) {
        NodeQueue* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

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

void KitchenLinkedQueue::dequeue() {
    if (isEmpty()) {
        cerr << "\n # Erro: Fila vazia!" << endl;
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

NodeQueue* KitchenLinkedQueue::search(int number) {
    if (isEmpty()) return nullptr;

    NodeQueue* node = head;
    while (node != nullptr && node->data.getNumber() != number) {
        node = node->next;
    }

    return node;
}

bool KitchenLinkedQueue::isEmpty() const {
    return (head == nullptr);
}

int KitchenLinkedQueue::peek() const {
    if (isEmpty()) {
        cerr << "\n # Erro: Fila vazia!" << endl;
        return -1;
    }
    head->data.showOrder();
    return 0;
}

void KitchenLinkedQueue::undoOrder(int numberOrder) {
    if (this->isEmpty()) {
        cout << " # Lista Vazia! #" << endl;
        TerminalUtils::pause();
        return;
    }

    NodeQueue* node = this->search(numberOrder);

    if (node == nullptr) {
        cout << "\n # Erro: Pedido nao encontrado! #" << endl;
        TerminalUtils::pause();
        return;
    }

    if (node->stackOrders.isEmpty()) {
        cout << "\n # Nenhuma alteracao para desfazer! #" << endl;
        TerminalUtils::pause();
        return;
    }

    node->data = node->stackOrders.pop();
    cout << "\n> Ultima alteracao desfeita com sucesso!" << endl;
    TerminalUtils::pause();
}

void KitchenLinkedQueue::showOrders() const {
    NodeQueue* current = head;

    while (current != nullptr) {
        cout << "    Numero: " << current->data.getNumber() << endl;
        cout << "      Cliente: " << current->data.getClient() << endl;
        if (current->next != nullptr) cout << "------------------------------------------------" << endl;
        current = current->next;
    }
}

int KitchenLinkedQueue::getQuantatyOrders() const {
    return quantatyOrders;
}

void KitchenLinkedQueue::setQuantatyOrders(int quantatyOrders) {
    this->quantatyOrders = quantatyOrders;
}

void KitchenLinkedQueue::removeOrder(int index) {
    if (isEmpty()) {
        cerr << "\n # Erro: Fila vazia!" << endl;
        return;
    }

    NodeQueue* current = head;
    NodeQueue* previous = nullptr;

    while (current != nullptr && current->data.getNumber() != index) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cerr << "\n # Erro: Pedido nao encontrado!" << endl;
        return;
    }

    if (current == head) {
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
    } else {
        previous->next = current->next;
        if (current == tail) {
            tail = previous;
        }
    }

    delete current;
    quantatyOrders--;
    cout << "\nPedido removido com sucesso!" << endl;
}