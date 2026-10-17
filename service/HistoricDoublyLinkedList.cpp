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
int HistoricDoublyLinkedList::removeOrder(int number) {
    if (this->isEmpty()) {
        cerr << "\n # Erro: Lista vazia!" << endl;
        return -1;
    }

    NodeList* current = head;

    // Procura o pedido pelo número
    while (current != nullptr &&
           current->data.getNumber() != number) {
        current = current->next;
    }

    // Pedido não encontrado
    if (current == nullptr) {
        cerr << "\n # Erro: Pedido nao encontrado!" << endl;
        return -2;
    }

    // Atualiza o nó anterior ou o início da lista
    if (current->previous != nullptr) {
        current->previous->next = current->next;
    } else {
        head = current->next;
    }

    // Atualiza o próximo nó ou o final da lista
    if (current->next != nullptr) {
        current->next->previous = current->previous;
    } else {
        tail = current->previous;
    }

    // Se a lista ficou vazia, ambos devem ser nullptr
    if (head == nullptr) {
        tail = nullptr;
    }

    delete current;

    cout << "\nPedido removido com sucesso!" << endl;
    return 0;
}


// busca um pedido pelo número do pedido
NodeList* HistoricDoublyLinkedList::search(int number) const {
    if (isEmpty()) {
        cerr << "\n|          # Lista vazia!                       |" << endl;
        return nullptr;
    }

    NodeList* current = head;
    while (current != nullptr) {
        if (current->data.getNumber() == number) {
            current->data.showOrder();
            return current;
        }
        current = current->next;
    }
    // cerr << "\n|         # Erro: Pedido nao encontrado!       |" << endl;
    return nullptr;
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

    cout << "============== LISTAGEM DE PEDIDOS ==============" << endl;
    while (current != nullptr) {
        
        // Visualização detalhada de cada pedido presente na lista
        cout << "-------------------------------------------------" << endl;
        current->data.showOrder();
        cout << "-------------------------------------------------" << endl;
        
        // Faturamento - somatório dos valores totais dos pedido
        invoicing += current->data.getTotal();
        
        // Quantitade total de pedidos
        quantatyOrders++;
        
        // Navega para o proximo pedido
        current = current->next;
    }
    
    cout << "=-=-=-=-=-=-=-=-= RELATORIO GERAL =-=-=-=-=-=-=-=" << endl;
    cout << " > Quantidade Total de Pedidos: " << quantatyOrders << endl;
    cout << " > Faturamento: R$" << invoicing << endl;
    cout << "=================================================" << endl;

}

void HistoricDoublyLinkedList::menuSearchOrder() {
    if (this->isEmpty()) {
        cout << "\n # Historico de pedidos vazio! #" << endl;
        TerminalUtils::pause();
        return;
    }

    int numberOrder;

    cout << "\n > Informe o pedido: ";
    cin >> numberOrder;

    NodeList* node = this->search(numberOrder);

    // Verifica se o pedido foi encontrado
    if (node == nullptr) {
        cout << "\n # Erro: Pedido nao encontrado! #" << endl;
        TerminalUtils::pause();
        return;
    }

    TerminalUtils::clear();
    cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    node->data.showOrder();
    cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    TerminalUtils::pause();
}

void HistoricDoublyLinkedList::menuRemoveOrder() {
    int optionRemove, numberOrder;
    
    cout << "\n > Informe o pedido: ";
    cin >> numberOrder;

    NodeList* node = this->search(numberOrder);

    cout << "Passei aqui1!" << endl;

    if (node != nullptr)
    {
        cout << "Passei aqui2!" << endl;
        do {
            // TerminalUtils::clear();
            cout << "================ REMOVER PEDIDO ================" << endl;
            node->data.showOrder();
            cout << "------------------------------------------------" << endl;
            cout << " #    Deseja confirmar a remocao do pedido?   # " << endl;
            cout << "------------------------------------------------" << endl;
            cout << "| [1] Confirmar Acao             [0] Cancelar  |" << endl;
            cout << "================================================" << endl;
            cout << " > Escolha uma opcao: ";
    
            cin >> optionRemove;
    
            switch (optionRemove) {
                case 1: {
                    this->removeOrder(numberOrder);
                    return;
                }
                case 0:
                    cout << "\nOperacao cancelada." << endl;
                    TerminalUtils::pause();
                    break;
                    
                default:
                    cout << "\n # Erro: Opcao invalida!" << endl;
                    TerminalUtils::pause();
                    break;
            }
        } while (optionRemove != 0);
    } else {
        TerminalUtils::pause();
        return;
    }
}

// Funções de Exibição de Menu

void HistoricDoublyLinkedList::menuExibirHistoricOrders() {
    cout << "============= HISTORICO DE PEDIDOS =============" << endl;
    if (this->isEmpty()) {
        cout << "        # Historico de Pedidos Vazio #       " << endl;
        cout << "================================================" << endl;
        TerminalUtils::pause();
        return;
    }

    int optionHistoric;
    int indexHistoric = head->data.getNumber();

    do {
        TerminalUtils::clear();
        cout << "============= HISTORICO DE PEDIDOS =============" << endl;
        this->search(indexHistoric);
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Anterior     [0] Voltar     [2] Proximo  |" << endl;
        cout << "| [3] Deletar      [4] Relatorio  [5] Buscar   |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionHistoric;

        switch (optionHistoric) {
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

            case 3: {
                // Guarda o próximo pedido antes de remover o atual
                int next = this->nextOrder(indexHistoric);

                menuRemoveOrder();

                // Se o pedido atual foi removido, atualiza a navegação
                if (this->search(indexHistoric) == nullptr) {
                    if (this->isEmpty()) {
                        break;
                    }

                    // Se ainda houver pedidos, seleciona um válido
                    if (this->search(next) != nullptr) {
                        indexHistoric = next;
                    } else {
                        indexHistoric = head->data.getNumber();
                    }
                }
                break;
            }

            case 4: {
                TerminalUtils::clear();
                this->showOrders();
                TerminalUtils::pause();
                break;
            }
            
            case 5: {
                menuSearchOrder();
            }

            case 0:
                break;

            default:
                cerr << "\n # Erro: Opcao invalida!" << endl;
                break;
        }

    } while (optionHistoric != 0);
}