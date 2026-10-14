#include "../models/LinkedStack.hpp"
#include "../models/KitchenLinkedQueue.hpp"
#include "../models/HistoricDoublyLinkedList.hpp"
#include "../utils/TerminalUtils.hpp"

using namespace std;

// Construtor
KitchenLinkedQueue::KitchenLinkedQueue() {
    head = nullptr;
    tail = nullptr;
    quantatyOrders = 0;
    //counterOrders;
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
    if (isEmpty()) {
        //cerr << " # Erro: Order not found (Search)!" << endl;
        return nullptr;
    }

    NodeQueue* node = head;
    while (node != nullptr && node->data.getNumber() != number) {
        node = node->next;
    }

    if (node == nullptr) {
        //cerr << " # Erro: Pedido nao encontrado! (Search)" << endl;
        return nullptr;
    }

    node->data.showOrder();
    return node;
}

// verifica se a fila está vazia
bool KitchenLinkedQueue::isEmpty() const {
    return (head == nullptr);
}

// retorna o valor do primeiro elemento da fila sem removê-lo
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

    // Busca o nó na fila
    NodeQueue* node = this->search(numberOrder);

    // Validação de ponteiro nulo
    if (node == nullptr) {
        cout << "\n # Erro: Pedido nao encontrado! #" << endl;
        TerminalUtils::pause();
        return;
    }

    if (node->orderChanges.peek() != -1) {
        cerr << " Operacao cancelada! Nenhuma alteracao do pedido encontrada.";
        TerminalUtils::pause();
        return;
    }

    node->data = node->orderChanges.pop();
    cout << "\n> Ultima alteracao desfeita com sucesso!" << endl;
    TerminalUtils::pause();
}


// exibe todos os pedidos da lista, porém, mostra apenas o número do pedido e o nome do cliente
void KitchenLinkedQueue::showOrders() const {
    NodeQueue* current = head;

    while (current != nullptr) {
        cout << "    Numero: " << current->data.getNumber() << endl;
        cout << "      Clinte: " << current->data.getClient() << endl;
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

// Funções de Exibição de Menu
void KitchenLinkedQueue::menuOperacoesBalcao() {
    int option;

    do {
        TerminalUtils::clear();

        cout << "============ GERENCIAR FILA PEDIDOS ============" << endl;
        this->showOrders();
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Adicionar Novo Pedido  [4] Buscar Pedido |" << endl;
        cout << "| [2] Remover Pedido         [0] Sair          |" << endl;
        cout << "| [3] Gerenciar Pedido                         |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
        cin >> option;

        switch (option) {
            case 1:
                // Adicionar Novo Pedido
                menuRegisterOrder();
                break;
            case 2:
                // Inativa um pedido
                menuRemoveOrder();
                break;
            case 3:
                menuManageOrder();
                break;
            case 4:
                menuSearchOrder();
                break;
            case 0:
                cout << "\nOperacao cancelada." << endl;
                break;
            default:
                cout << "\n # Erro: Opcao invalida!" << endl;
                break;
        }
    } while (option != 0);
}

void KitchenLinkedQueue::carrinho(const vector<int>& quantatyItems) {
    vector<string> menuNames = {"Cachorro Quente", "Batata Frita", "Hamburguer", "Pizza", "Coca Zero"};

    cout << "=-=-=-=-=-=-=-=  CARRINHO ATUAL  =-=-=-=-=-=-=-=" << endl;
    bool vazio = true;
    for (size_t i = 0; i < menuNames.size(); ++i) {
        if (i < quantatyItems.size() && quantatyItems[i] > 0) {
            cout << "   - " << menuNames[i] << ": " << quantatyItems[i] << endl;
            vazio = false;
        }
    }
    if (vazio) {
        cout << "           (Nenhum item no carrinho)" << endl;
    }
    cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
}

void KitchenLinkedQueue::menuRegisterOrder() {
    vector<string> items;
    vector<int> quantatyItems = {0, 0, 0, 0, 0};
    string client;

    TerminalUtils::clear();
    cout << "=-=-=-=-=-=-= NOVO PEDIDO =-=-=-=-=-=-=" << endl;
    cout << " > Nome Cliente: ";
    cin >> ws;
    getline(cin, client);

    int optionCadastrar;
    do {
        TerminalUtils::clear();

        // Exibe o carrinho simples
        carrinho(quantatyItems);

        cout << "=============== CADASTRAR PEDIDO ===============" << endl;
        cout << "| [1] Cachorro Quente         R$ 8.00          |" << endl;
        cout << "| [2] Batata Frita            R$ 6.00          |" << endl;
        cout << "| [3] Hamburguer              R$ 20.00         |" << endl;
        cout << "| [4] Pizza                   R$ 46.00         |" << endl;
        cout << "| [5] Coca Zero               R$ 12.00         |" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "| [10] Finalizar Pedido         [0] Cancelar   |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
        cin >> optionCadastrar;

        switch (optionCadastrar) {

            case 1:
                items.push_back("Cachorro Quente");
                quantatyItems[0]++; // Incrementa direto na opcao escolhida
                break;

            case 2:
                items.push_back("Batata Frita");
                quantatyItems[1]++;
                break;

            case 3:
                items.push_back("Hamburguer");
                quantatyItems[2]++;
                break;

            case 4:
                items.push_back("Pizza");
                quantatyItems[3]++;
                break;

            case 5:
                items.push_back("Coca Zero");
                quantatyItems[4]++;
                break;

            case 10: {
                if (items.empty()) {
                    cout << "\n # Erro: Adicione pelo menos um item ao pedido!" << endl;
                } else {
                    Order order(client, items, quantatyItems);
                    this->enqueue(order);

                    TerminalUtils::clear();
                    cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
                    cout << "          Pedido cadastrado com sucesso!        " << endl;
                    cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
                    TerminalUtils::pause();
                    optionCadastrar = 0;
                }
                break;
            }

            case 0:
                cout << "\nCadastro cancelado." << endl;
                break;

            default:
                cout << "\n # Erro: Opcao invalida!" << endl;
                break;
        }

    } while (optionCadastrar != 0);
}


void KitchenLinkedQueue::menuRemoveOrder() {
    if (this->isEmpty()) {  // Caso a lista esteja vazia
        cout << " # Lista Vazia! #" << endl;
        cout << " # Adicione um novo pedido antes de fazer alguma operacao! #";
        TerminalUtils::pause();
        return;
    }

    int optionRemove, numberOrder;

    cout << "\n > Informe o pedido: ";
    cin >> numberOrder;

    do {
        TerminalUtils::clear();
        cout << "================ REMOVER PEDIDO ================" << endl;
        this->search(numberOrder);
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
                break;

            default:
                cout << "\n # Erro: Opcao invalida!" << endl;
                break;
        }
    } while (optionRemove != 0);
    return;
}

void KitchenLinkedQueue::menuSearchOrder() {
    if (this->isEmpty()) {  // Caso a lista esteja vazia
        cout << " # Lista Vazia! #" << endl;
        cout << " # Adicione um novo pedido antes de fazer alguma operacao! #";
        TerminalUtils::pause();
        return;
    }

    int numberOrder;

    cout << "\n > Informe o pedido: ";
    cin >> numberOrder;

    TerminalUtils::clear();
    cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    this->search(numberOrder);
    cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    TerminalUtils::pause();

}

void KitchenLinkedQueue::menuManageOrder() {
    if (this->isEmpty()) {
        cout << " # Lista Vazia! #" << endl;
        cout << " # Adicione um novo pedido antes de fazer alguma operacao! #";
        TerminalUtils::pause();
        return;
    }

    int optionManagerOrder, numberOrder;

    cout << "\n > Informe o pedido: ";
    cin >> numberOrder;

    do {
        TerminalUtils::clear();
        cout << "=============== GERENCIAR PEDIDO ===============" << endl;
        NodeQueue* node = this->search(numberOrder);

        if (node == nullptr) {
            cout << "\n # Pedido nao encontrado! #" << endl;
            cout << "================================================" << endl;
            TerminalUtils::pause();
            return;
        }

        cout << "------------------------------------------------" << endl;
        cout << "| [1] Adicionar Item           [3] Desfazer    |" << endl;
        cout << "| [2] Remover Item             [0] Voltar      |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionManagerOrder;

        switch (optionManagerOrder) {
            case 1:
                menuAddItem(numberOrder);
                break;
            case 2:
                menuRemoveItem(numberOrder);
                break;
            case 3:
                undoOrder(numberOrder);
                break;
            case 0:
                cout << "\nVoltando ao menu anterior." << endl;
                break;
            default:
                cout << "\n # Erro: Opcao invalida!" << endl;
                TerminalUtils::pause();
                break;
        }
    } while (optionManagerOrder != 0);
}


void KitchenLinkedQueue::menuAddItem(int numberOrder) {
    if (this->isEmpty()) {
        cout << " # Lista Vazia! #" << endl;
        TerminalUtils::pause();
        return;
    }

    // Busca o nó na fila
    NodeQueue* node = this->search(numberOrder);

    // Validação de ponteiro nulo
    if (node == nullptr) {
        cout << "\n # Erro: Pedido nao encontrado! #" << endl;
        TerminalUtils::pause();
        return;
    }

    int optionAddItem;
    int orderNumber = node->data.getNumber();
    vector<string> items = node->data.getItems();

    do {
        TerminalUtils::clear();
        carrinho(node->data.getQuantatyItems());

        cout << "================ ADICIONAR ITEM ================" << endl;
        cout << "| [1] Cachorro Quente         R$ 8.00          |" << endl;
        cout << "| [2] Batata Frita            R$ 6.00          |" << endl;
        cout << "| [3] Hamburguer              R$ 20.00         |" << endl;
        cout << "| [4] Pizza                   R$ 46.00         |" << endl;
        cout << "| [5] Coca Zero               R$ 12.00         |" << endl;
        cout << "------------------- PEDIDO #" << orderNumber << " ------------------" << endl;
        cout << "| [10] Finalizar Alteracao     [0] Cancelar    |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionAddItem;

        if (optionAddItem >= 1 && optionAddItem <= 5) {
            // salva estado para na pilha
            node->orderChanges.push(node->data);

            // altera diretamente no pedido do nó
            node->data.addItem(optionAddItem - 1);
        }

    } while (optionAddItem != 0 && optionAddItem != 10);
}

void KitchenLinkedQueue::menuRemoveItem(int numberOrder) {
    if (this->isEmpty()) {
        cout << " # Lista Vazia! #" << endl;
        TerminalUtils::pause();
        return;
    }

    // Busca o nó na fila
    NodeQueue* node = this->search(numberOrder);

    // Validação de ponteiro nulo
    if (node == nullptr) {
        cout << "\n # Erro: Pedido nao encontrado! #" << endl;
        TerminalUtils::pause();
        return;
    }

    int optionAddItem;
    int orderNumber = node->data.getNumber();
    vector<string> items = node->data.getItems();

    do {
        TerminalUtils::clear();
        carrinho(node->data.getQuantatyItems());

        cout << "================= REMOVER ITEM =================" << endl;
        cout << "| [1] Cachorro Quente         R$ 8.00          |" << endl;
        cout << "| [2] Batata Frita            R$ 6.00          |" << endl;
        cout << "| [3] Hamburguer              R$ 20.00         |" << endl;
        cout << "| [4] Pizza                   R$ 46.00         |" << endl;
        cout << "| [5] Coca Zero               R$ 12.00         |" << endl;
        cout << "------------------- PEDIDO #" << orderNumber << " ------------------" << endl;
        cout << "| [10] Finalizar Alteracao     [0] Cancelar    |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionAddItem;

        if (optionAddItem == 0) {

        } else if (optionAddItem >= 1 && optionAddItem <= 5) {
            // salva estado para na pilha
            node->orderChanges.push(node->data);

            // altera diretamente no pedido do nó
            node->data.removeItem(optionAddItem - 1);
            if(node->data.getItems().empty()) {
                this->removeOrder(orderNumber);
                return;
            }
        }



    } while (optionAddItem != 0 && optionAddItem != 10);
}



// void KitchenLinkedQueue::menuKitchen(HistoricDoublyLinkedList historicList) {
//     if (this->isEmpty()) {
//         cout << " # Lista Vazia! #" << endl;
//         cout << " # Aguarde novos pedidos! #";
//         TerminalUtils::pause();
//         return;
//     }

//     int option, numberOrder;

//     // cout << "\n > Informe o pedido: ";
//     // cin >> numberOrder;

//     do {
//         TerminalUtils::clear();
//         cout << "=============== PEDIDOS PRONTOS ===============" << endl;
//         counterOrders.showCounterOrders();
//         // NodeStack* node =
//         // if (node == nullptr) {
//         //     cout << "\n # Pedido nao encontrado! #" << endl;
//         //     cout << "================================================" << endl;
//         //     TerminalUtils::pause();
//         //     return;
//         // }

//         historicList.showOrders();
//         cout << "------------------------------------------------" << endl;
//         cout << "| [1] Preparar Pedido          [0] Sair        |" << endl;
//         cout << "| [2] Cancelar Preparo                         |" << endl;
//         cout << "================================================" << endl;

//         if (option >= 1 && option <= 2) {
//             cout << "\n > Informe o pedido: ";
//             cin >> numberOrder;

            

//         }

//     } while (option != 0);
// }
