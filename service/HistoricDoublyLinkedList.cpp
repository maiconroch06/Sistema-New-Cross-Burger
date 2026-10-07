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
    
    if (isEmpty()) {        // Caso a lista esteja vazia, tail aponta para o Novo Nó
        tail = newNode;
    } else {                // Caso a lista não esteja vazia, o proximo
        head->previous = newNode;
    }
    
    head = newNode;
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
    // Caso a posição seja no inicio
    if (index == 0) {
        insert(order);
        return;
    }

    if (isEmpty()) {
        cout << "\n # ERRO: Lista vazia!" << endl;
        return;
    }

    NodeList* current = head;
    
    // Vai percorrer até encontrar a possição de mudança
    for (int currentCount = 0; current != nullptr && currentCount < index; currentCount++) {
        current = current->next;
    }

    // Se o current for nulo, significa que o indice não foi encontrado
    if (current == nullptr) {
        insertEnd(order); // Inserir no fim caso o índice passe do tamanho
        return;
    }

    // Inserir no meio
    NodeList* newNode = new NodeList();
    newNode->data = order;
    newNode->next = current;
    newNode->previous = current->previous;

    if (current->previous != nullptr) {
        current->previous->next = newNode;
    } else {
        head = newNode;
    }

    current->previous = newNode;
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
        cout << "|          # ERRO: Lista vazia!                 |" << endl;
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
        return index;
    }

    NodeList* current = head;
    while (current != nullptr && current->data.getNumber() != index) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "\n # Erro: Pedido nao encontrado!" << endl;
        return index;
    }

    if (current->next == nullptr) {
        cout << "\n # Aviso: Voce ja esta no ultimo pedido!" << endl;
        return index;
    }

    return current->next->data.getNumber();
}

// exibe o pedido anterior
int HistoricDoublyLinkedList::previousOrder(int index) const {
    if (isEmpty()) {
        cout << "\n # ERRO: Lista vazia!" << endl;
        return index;
    }

    NodeList* current = head;
    while (current != nullptr && current->data.getNumber() != index) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "\n # Erro: Pedido nao encontrado!" << endl;
        return index;
    }

    if (current->previous == nullptr) {
        cout << "\n # Aviso: Voce ja esta no primeiro pedido!" << endl;
        return index;
    }

    return current->previous->data.getNumber();
}

// exibe todos os pedidos da lista
void HistoricDoublyLinkedList::showOrders() const {
    NodeList* current = head;

    while (current != nullptr) {
        current->data.showOrder();
        cout << "| > Anterior: " << current->previous << endl;
        cout << "| > Atual: " << current << endl;
        cout << "| > Proximo: " << current->next << endl;
        
        current = current->next;
    }
}


// Funções de Exibição de Menu

void HistoricDoublyLinkedList::menuExibirHistoricoPedidos() {
    int optionHistorico;
    int historicIndex = 1;

    do {
        cout << "\n============= HISTORICO DE PEDIDOS =============" << endl;

        this->search(historicIndex);

        cout << "------------------------------------------------" << endl;
        cout << "| [1] Anterior   [0] Voltar   [2] Proximo     |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionHistorico;

        switch (optionHistorico) {

            case 1:
                this->previousOrder(historicIndex);
                break;

            case 2:
                this->nextOrder(historicIndex);
                break;

            case 3:
                this->showOrders();
                break;

            case 0:
                break;

            default:
                cout << "\n # ERRO: Opcao invalida!" << endl;
                break;
        }

    } while (optionHistorico != 0);
}