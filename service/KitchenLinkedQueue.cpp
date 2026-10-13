#include "../models/KitchenLinkedQueue.hpp"
#include "../models/ActionsLinkedStack.hpp"
#include "../utils/TerminalUtils.hpp"

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



// // Funções de Exibição de Menu
// void KitchenLinkedQueue::menuOperacoesBalcao() {
//     int option = 1, numberOrder = head->data.getNumber();
    
//     do {
//         TerminalUtils::clear();

//         cout << "=============== GERENCIAR PEDIDO ===============" << endl;
//         this->search(numberOrder);
//         cout << "------------------------------------------------" << endl;
//         cout << "| [1] Adicionar Novo Pedido [4] Adicionar Item |" << endl;
//         cout << "| [2] Remover Pedido        [5] Remover Item   |" << endl;
//         cout << "| [3] Buscar Pedido         [0] Sair           |" << endl;
//         cout << "================================================" << endl;
//         cout << " > Escolha uma opcao: ";
//         cin >> option;
        
//         // Se escolheu 1, 2 ou 3: usuario volta para selecionar um pedido da fila
//         // Se escolheu 0: usuario volta para o menu de gerenciar pedido
//         switch (option) {
//             case 1:
//                 // Adicionar Novo Pedido
//                 menuRegisterOrder();
//                 break;
//             case 2:
//                 // Inativa um pedido
//                 numberOrder = menuRemoveOrder(numberOrder);
//                 break;
//             case 3: 
//                 numberOrder = menuSearchOrder();
//                 break;
//             case 0:
//                 cout << "\nOperacao cancelada." << endl;
//                 break;
//             default:
//                 cout << "\n # Erro: Opcao invalida!" << endl;
//                 break;
//         }
//     } while (option != 0);
// }

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
                //cout << "\nItem adicionado!" << endl;
                //TerminalUtils::pause();
                break;
                
                case 2:
                items.push_back("Batata Frita");
                quantatyItems[1]++;
                //cout << "\nItem adicionado!" << endl;
                //TerminalUtils::pause();
                break;
                
                case 3:
                items.push_back("Hamburguer");
                quantatyItems[2]++;
                //cout << "\nItem adicionado!" << endl;
                //TerminalUtils::pause();
                break;
                
                case 4:
                items.push_back("Pizza");
                quantatyItems[3]++;
                //cout << "\nItem adicionado!" << endl;
                //TerminalUtils::pause();
                break;
                
                case 5:
                items.push_back("Coca Zero");
                quantatyItems[4]++;
                //cout << "\nItem adicionado!" << endl;
                //TerminalUtils::pause();
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
        cout << "| [1] Adicionar Item           [0] Voltar      |" << endl;
        cout << "| [2] Remover Item                             |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionManagerOrder;
        
        switch (optionManagerOrder) {
            case 1:
                // Adicionar Novo Item ao Pedido
                menuAddItem(numberOrder); // Repassa o número do pedido diretamente
                break;
            case 2:
                // Remover Item do Pedido
                // menuRemoveItem(numberOrder);
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
    vector<string> items = node->data.getItems();
    vector<int> quantatyItems = node->data.getQuantatyItems();
    int orderNumber = node->data.getNumber();

    do {
        TerminalUtils::clear();
        carrinho(quantatyItems);

        cout << "=========== ADICIONAR ITEM AO PEDIDO #" << orderNumber << " ===========" << endl;
        cout << "| [1] Cachorro Quente         R$ 8.00          |" << endl;
        cout << "| [2] Batata Frita            R$ 6.00          |" << endl;
        cout << "| [3] Hamburguer              R$ 20.00         |" << endl;
        cout << "| [4] Pizza                   R$ 46.00         |" << endl;
        cout << "| [5] Coca Zero               R$ 12.00         |" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "| [10] Finalizar Alteracao     [0] Cancelar    |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionAddItem;

        switch (optionAddItem) {
            case 1:
                items.push_back("Cachorro Quente");
                if (quantatyItems.size() > 0) {
                    quantatyItems[0]++;
                }
                break;

            case 2:
                items.push_back("Batata Frita");
                if (quantatyItems.size() > 1) {
                    quantatyItems[1]++;
                }
                break;

            case 3:
                items.push_back("Hamburguer");
                if (quantatyItems.size() > 2) {
                    quantatyItems[2]++;
                }
                break;

            case 4:
                items.push_back("Pizza");
                if (quantatyItems.size() > 3) {
                    quantatyItems[3]++;
                }
                break;

            case 5:
                items.push_back("Coca Zero");
                if (quantatyItems.size() > 4) {
                    quantatyItems[4]++;
                }
                break;

            case 10: {
                if (items.empty()) {
                    cout << "\n # Erro: Adicione pelo menos um item ao pedido!" << endl;
                    TerminalUtils::pause();
                } else {
                    // salva a versão anterior na pilha de histórico (Undo)
                    node->stackOrders.push(node->data);

                    // instancia o objeto atualizado com cliente, itens e quantidades
                    Order updatedOrder(node->data.getClient(), items, quantatyItems);
                    updatedOrder.setNumber(orderNumber); // define o número do pedido

                    // sobrescreve o pedido atual na fila
                    node->data = updatedOrder;

                    cout << "\nPedido atualizado com sucesso!" << endl;
                    TerminalUtils::pause();
                    optionAddItem = 0;
                }
                break;
            }

            case 0:
                cout << "\nOperacao cancelada." << endl;
                break;

            default:
                cout << "\n # Erro: Opcao invalida!" << endl;
                TerminalUtils::pause();
                break;
        }

    } while (optionAddItem != 0);
}