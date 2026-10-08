#include "../models/HistoricDoublyLinkedList.hpp"
#include "../utils/TerminalUtils.hpp"

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
        cerr << "\n # Erro: Lista vazia!" << endl;
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
        cerr << "\n # Erro: Lista vazia!" << endl;
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

    cerr << "|         # Erro: Pedido nao encontrado!       |" << endl;
    return -2;
}

// busca um pedido pelo número do pedido
int HistoricDoublyLinkedList::search(int number) const {
    if (isEmpty()) {
        cerr << "|          # Erro: Lista vazia!                 |" << endl;
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

    cerr << "|         # Erro: Pedido nao encontrado!       |" << endl;
    return -2;
}

// verifica se a lista está vazia
bool HistoricDoublyLinkedList::isEmpty() const {
    return head == nullptr;
}

// exibe o proximo pedido
int HistoricDoublyLinkedList::nextOrder(int index) const {
    if (isEmpty()) {
        cerr << "\n # Erro: Lista vazia!" << endl;
        return -1;
    }

    NodeList* current = head;
    while (current != nullptr && current->data.getNumber() != index) {
        current = current->next;
    }
    
    if (current == nullptr) {
        cerr << "\n # Erro: Pedido nao encontrado!" << endl;
        return -2;
    }

    if (current->next == nullptr) {
        return head->data.getNumber();
    }

    return current->next->data.getNumber();
}

// exibe o pedido anterior
int HistoricDoublyLinkedList::previousOrder(int index) const {
    if (isEmpty()) {
        cerr << "\n # Erro: Lista vazia!" << endl;
        return -1;
    }

    NodeList* current = head;
    while (current != nullptr && current->data.getNumber() != index) {
        current = current->next;
    }
    
    if (current == nullptr) {
        cerr << "\n # Erro: Pedido nao encontrado!" << endl;
        return -2;
    }

    if (current->previous == nullptr) {
        return tail->data.getNumber();
    }

    return current->previous->data.getNumber();
}

// exibe todos os pedidos da lista
void HistoricDoublyLinkedList::showOrders() const {
    if (isEmpty()) {
        cerr << "Erro: Lista vazia!" << endl;
        return;
    }

    NodeList* current = head;
    int quantatyOrders = 0, invoicing = 0;

    cout << "============== LISTAGEM DE PEDIDOS =============" << endl;
    while (current != nullptr) {
        
        // Visualização detalhada pedido
        cout << "-------------------------------------------" << endl;
        current->data.showOrder();
        cout << "-------------------------------------------" << endl;
        
        // Faturamento - somatório dos valores totais dos pedido
        invoicing += current->data.getTotal();
        
        // Quantitade total de pedidos
        quantatyOrders++;
        
        // Navega para o proximo pedido
        current = current->next;
    }

    cout << " > Total de Pedidos: " << quantatyOrders << endl;
    cout << " > Faturamento: R$" << invoicing << endl;

}


// Funções de Exibição de Menu

void HistoricDoublyLinkedList::menuExibirHistoricoPedidos() {
    if (isEmpty()) {
        cout << "\n # Aviso: O historico de pedidos esta vazio!" << endl;
        return;
    }

    int optionHistorico;
    int indexHistoric = head->data.getNumber();

    do {
        TerminalUtils::clear();
        cout << "\n============= HISTORICO DE PEDIDOS =============" << endl;
        this->search(indexHistoric);
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Anterior   [0] Voltar   [2] Proximo     |" << endl;
        cout << "| [3] Exibir Relatorio                        |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionHistorico;

        switch (optionHistorico) {
            case 1: {
                int prev = this->previousOrder(indexHistoric);
                if (prev > 0) {
                    indexHistoric = prev;
                }
                break;
            }

            case 2: {
                int next = this->nextOrder(indexHistoric);
                if (next > 0) {
                    indexHistoric = next;
                }
                break;
            }

            case 3:
                TerminalUtils::clear();
                this->showOrders();
                TerminalUtils::pause();
                break;

            case 0:
                break;

            default:
                cerr << "\n # Erro: Opcao invalida!" << endl;
                break;
        }

    } while (optionHistorico != 0);
}