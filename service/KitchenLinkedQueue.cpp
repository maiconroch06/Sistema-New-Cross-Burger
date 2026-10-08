#include "../models/KitchenLinkedQueue.hpp"
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

void KitchenLinkedQueue::search(int number) const {
    if (isEmpty()) {
        cerr << "\n # Erro: Fila vazia!" << endl;
        return;
    }

    NodeQueue* current = head;
    while (current != nullptr && current->data.getNumber() != number) {
        current = current->next;
    }

    if (current == nullptr) {
        cerr << "|         # Erro: Pedido nao encontrado!       |" << endl;
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
        cout << "      Numero: " << current->data.getNumber() << endl;
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
    int option, numberOrder;
    
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

        if (option == 2 || option == 3 || option == 4) {
            cout << "\n > Informe o pedido: ";
            cin >> numberOrder;
        }
        
        switch (option) {
            case 1:
                // Adicionar Novo Pedido
                menuRegisterOrder();
                break;
            case 2:
                // Inativa um pedido
                menuRemoveOrder(numberOrder);
                break;
            case 3: 
                menuManageOrder(numberOrder);
                break;
            case 4: 
                menuSearchOrder(numberOrder);
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
        cout << "   (Nenhum item no carrinho)" << endl;
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

        cout << "============= CADASTRAR PEDIDO =================" << endl;
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
                cout << "\nItem adicionado!" << endl;
                break;

            case 2:
                items.push_back("Batata Frita");
                quantatyItems[1]++;
                cout << "\nItem adicionado!" << endl;
                break;

            case 3:
                items.push_back("Hamburguer");
                quantatyItems[2]++;
                cout << "\nItem adicionado!" << endl;
                break;

            case 4:
                items.push_back("Pizza");
                quantatyItems[3]++;
                cout << "\nItem adicionado!" << endl;
                break;

            case 5:
                items.push_back("Coca Zero");
                quantatyItems[4]++;
                cout << "\nItem adicionado!" << endl;
                break;

            case 10: {
                if (items.empty()) {
                    cout << "\n # Erro: Adicione pelo menos um item ao pedido!" << endl;
                } else {
                    Order order(client, items, quantatyItems);
                    this->enqueue(order);
                    
                    cout << "\nPedido cadastrado com sucesso!" << endl;
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


int KitchenLinkedQueue::menuRemoveOrder(int index) {
    int optionRemove;
    do {
        TerminalUtils::clear();
        cout << "================ REMOVER PEDIDO ================" << endl;
        cout << " #    Deseja confirmar a remocao do pedido?   # " << endl;
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Confirmar Acao             [0] Cancelar  |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
        
        cin >> optionRemove;

        switch (optionRemove) {
            case 1: {
                this->removeOrder(index);
                return 0;
            }
            case 0:
                cout << "\nOperacao cancelada." << endl;
                break;

            default:
                cout << "\n # Erro: Opcao invalida!" << endl;
                break;
        }
    } while (optionRemove != 0);
    return 0;
}

void KitchenLinkedQueue::menuSearchOrder(int numberOrder) {
    if (isEmpty()) {
        cerr << "\n Fila de Pedidos Vazia!" << endl;
        return;
    }

    TerminalUtils::clear();
    this->search(numberOrder);
    TerminalUtils::pause();
    
}

void KitchenLinkedQueue::menuManageOrder(int numberOrder) {
    int optionManagerOrder;
    
    do {
        TerminalUtils::clear();
        cout << "=============== GERENCIAR PEDIDO ===============" << endl;
        this->search(numberOrder);
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Adicionar Item           [0] Volta       |" << endl;
        cout << "| [2] Remover Item                             |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionManagerOrder;
        
        switch (optionManagerOrder) {
            case 1:
                // Adicionar Novo Item ao Pedido
                // menuAddItem();
                break;
            case 2:
                // Remove Item do Pedido
                // munuRemoveItem();
                break;
            case 0:
                cout << "\nOperacao cancelada." << endl;
                break;
            default:
                cout << "\n # Erro: Opcao invalida!" << endl;
                break;
        }
    } while (optionManagerOrder != 0);
}


// void KitchenLinkedQueue::menuAddItem() {
//     // tenho que manipular o pedido selecionado, então preciso do número do pedido
//     int numberOrder;
//     cout << "\nInforme o numero do pedido para adicionar item: ";
//     cin >> numberOrder;

//     // dessa forma, consigo acessar o pedido selecionado e acessar um item a ele
//     // mas devo fazer uma busca na lista de pedidos para encontrar o pedido correto e adicionar o item a ele
//     // essa função tem que me retornar o objeto pedido que selecionei, remove-lo da queue e aguardar para adicionar o objeto pedido novo

//     vector<string> items;

//     int optionAddItem;
//     do {
//         TerminalUtils::clear();

//         cout << "\n========= ADICIONAR ITEM AO PEDIDO =============" << endl;
//         cout << "| [1] Cachorro Quente         R$ 8.00          |" << endl;
//         cout << "| [2] Batata Frita            R$ 6.00          |" << endl;
//         cout << "| [3] Hamburguer              R$ 20.00         |" << endl;
//         cout << "| [4] Pizza                   R$ 46.00         |" << endl;
//         cout << "| [5] Coca Zero               R$ 12.00         |" << endl;
//         cout << "------------------------------------------------" << endl;
//         cout << "| [10] Finalizar Pedido         [0] Cancelar   |" << endl;
//         cout << "================================================" << endl;
//         cout << " > Escolha uma opcao: ";

//         cin >> optionAddItem;

//         switch (optionAddItem) {

//             case 1:
//                 items.push_back("Cachorro Quente");
//                 cout << "\nItem adicionado!" << endl;
//                 break;

//             case 2:
//                 items.push_back("Batata Frita");
//                 cout << "\nItem adicionado!" << endl;
//                 break;

//             case 3:
//                 items.push_back("Hamburguer");
//                 cout << "\nItem adicionado!" << endl;
//                 break;

//             case 4:
//                 items.push_back("Pizza");
//                 cout << "\nItem adicionado!" << endl;
//                 break;

//             case 5:
//                 items.push_back("Coca Zero");
//                 cout << "\nItem adicionado!" << endl;
//                 break;

//             case 10: {
//                 if (items.empty()) {
//                     cout << "\n # Erro: Adicione pelo menos um item ao pedido!" << endl;
//                 } else {
//                     Order order(client, items);

//                     this->enqueue(order);
//                     this->insertEnd(order);

//                     cout << "\nPedido cadastrado com sucesso!" << endl;

//                     optionAddItem = 0;
//                 }
//                 break;
//             }

//             case 0:
//                 cout << "\nCadastro cancelado." << endl;
//                 break;

//             default:
//                 cout << "\n # Erro: Opcao invalida!" << endl;
//                 break;
//         }

//     } while (optionAddItem != 0);
// }