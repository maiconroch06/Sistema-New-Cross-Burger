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

    cout << "----------------------------------------" << endl;
    while (current != nullptr) {
        cout << "N Pedido: " << current->data.getNumber() << endl;
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

void KitchenLinkedQueue::removeOrder(int index) {
    if (isEmpty()) {
        cout << "\n # ERRO: Fila vazia!" << endl;
        return;
    }

    NodeQueue* current = head;
    NodeQueue* previous = nullptr;

    while (current != nullptr && current->data.getNumber() != index) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "\n # ERRO: Pedido nao encontrado!" << endl;
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
    int option = 1, numberOrder;
    
    do {
        if (isEmpty()) {
            cout << "\n Fila de Pedidos Vazia!" << endl;
            return;

        } else if (option == 1 || option == 2 || option == 3) {
            // Imprime apenas o numero e nome do cliente
            // de todos os pedidos na fila de pedidos
            this->showOrders();

            cout << "Selecione um pedido para gerencia-lo (N): ";
            cin >> numberOrder;

            // tratamento de erro

            // numero n encontrado
        }

        cout << "\n=============== GERENCIAR PEDIDO ===============" << endl;
        this->search(numberOrder);
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Adicionar Novo Pedido  [3] Voltar        |" << endl;
        cout << "| [2] Remover Pedido         [0] Sair          |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
        cin >> option;
        
        // Se escolheu 1, 2 ou 3: usuario volta para selecionar um pedido da fila
        // Se escolheu 0: usuario volta para o menu de gerenciar pedido
        switch (option) {
            case 1:
                // Adicionar Novo Pedido
                menuCadastrarPedido();
                break;
            case 2:
                // Inativa um pedido
                menuRemoverPedido(numberOrder);
                break;
            case 3:
                // Buscar Pedido

                break;
            case 0:
                cout << "\nOperacao cancelada." << endl;
                break;
            default:
                cout << "\n # ERRO: Opcao invalida!" << endl;
                break;
        }
    } while (option != 0);
}

void KitchenLinkedQueue::carrinho(const vector<int>& quantatyItems) {
    vector<string> menuNames = {"Cachorro Quente", "Batata Frita", "Hamburguer", "Pizza", "Coca Zero"};
    
    cout << "\n=== CARRINHO ATUAL ===" << endl;
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
}

void KitchenLinkedQueue::menuCadastrarPedido() {
    vector<string> items;
    vector<int> quantatyItems = {0, 0, 0, 0, 0};
    string client;

    cout << "\n============= NOVO PEDIDO =============" << endl;
    cout << " > Nome Cliente: ";
    cin >> ws;
    getline(cin, client);

    int optionCadastrar;
    do {
        // Exibe o carrinho simples
        carrinho(quantatyItems);

        cout << "\n============= CADASTRAR PEDIDO =================" << endl;
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
                    cout << "\n # ERRO: Adicione pelo menos um item ao pedido!" << endl;
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
                cout << "\n # ERRO: Opcao invalida!" << endl;
                break;
        }

    } while (optionCadastrar != 0);
}


void KitchenLinkedQueue::menuRemoverPedido(int index) {
    int optionRemove;
    do {
        cout << "\n================ REMOVER PEDIDO ================" << endl;
        cout << " # Deseja confirmar a remocao do pedido?" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Confirmar Acao             [0] Cancelar  |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
        
        cin >> optionRemove;

        switch (optionRemove) {
            case 1: {
                this->removeOrder(index);
                return;
            }
            case 0:
                cout << "\nOperacao cancelada." << endl;
                break;

            default:
                cout << "\n # ERRO: Opcao invalida!" << endl;
                break;
        }
    } while (optionRemove != 0);
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
//                     cout << "\n # ERRO: Adicione pelo menos um item ao pedido!" << endl;
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
//                 cout << "\n # ERRO: Opcao invalida!" << endl;
//                 break;
//         }

//     } while (optionAddItem != 0);
// }