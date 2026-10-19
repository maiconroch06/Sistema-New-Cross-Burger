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
    counterOrders = LinkedStack();
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

    setQuantatyOrders(getQuantatyOrders() + 1);

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
    if (this->isEmpty()) {
        //cerr << "\n # Erro: Fila vazia!" << endl;
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
    if (this->isEmpty()) {
        //cerr << " # Erro: Pedido não encontrado!" << endl;
        return nullptr;
    }

    NodeQueue* node = head;
    while (node != nullptr && node->data.getNumber() != number) {
        node = node->next;
    }

    if (node == nullptr) {
        //cerr << " # Erro: Pedido nao encontrado!" << endl;
        return nullptr;
    }

    //node->data.showOrder();
    return node;
}

// verifica se a fila está vazia
bool KitchenLinkedQueue::isEmpty() const {
    return (head == nullptr);
}

// retorna o valor do primeiro elemento da fila sem removê-lo
int KitchenLinkedQueue::peek() const {
    if (isEmpty()) {
        //cerr << "\n # Erro: Fila vazia!" << endl;
        return -1;
    }
    head->data.showOrder();
    return 0;
}

// Desfazer uma alteração do pedido
void KitchenLinkedQueue::undoOrder(int numberOrder) {
    if (this->isEmpty()) {
        //cerr << " # Lista Vazia! #" << endl;
        return;
    }

    // Busca o nó na fila
    NodeQueue* node = this->search(numberOrder);

    // Validação de ponteiro nulo
    if (node == nullptr) {
        //cerr << "\n # Erro: Pedido nao encontrado! #" << endl;
        return;
    }

    // Verifica se pilha de alterações esta vazia
    if (node->orderChanges.isEmpty()) {
        //cerr << " Operacao cancelada! Nenhuma alteracao do pedido encontrada.";
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
        //cerr << "\n # Erro: Fila vazia!" << endl;
        return;
    }

    NodeQueue* current = head;
    NodeQueue* previous = nullptr;

    while (current != nullptr && current->data.getNumber() != index) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        //cerr << "\n # Erro: Pedido nao encontrado!" << endl;
        return;
    }

    // Remover no início
    if (current == head) {
        head = head->next;
        // 
        if (head == nullptr) {
            tail = nullptr;
        }
    } else {
        // Remover no meio
        previous->next = current->next;
        // Remover no fim
        if (current == tail) {
            tail = previous;
        }
    }

    delete current;
    quantatyOrders--;
    cout << "\n Pedido removido com sucesso!" << endl;
    TerminalUtils::pause();
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
        cout << "| [3] Acoes do Pedido                          |" << endl;
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
                TerminalUtils::pause();
                break;
            default:
                cerr << "\n # Erro: Opcao invalida!" << endl;
                TerminalUtils::pause();
                break;
        }
    } while (option != 0);
}

// Carrinho dos Pedidos do Cliente
void KitchenLinkedQueue::carrinho(const vector<int>& quantatyItems) {
    vector<string> menuNames = {"Cachorro Quente", "Batata Frita", "Hamburguer", "Pizza", "Coca Zero"};

    cout << "=-=-=-=-=-=-=-=  CARRINHO ATUAL  =-=-=-=-=-=-=-=" << endl;
    bool vazio = true;
    for (int i = 0; i < menuNames.size(); ++i) {
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
        cout << "| [10] Finalizar   [9] Desfazer  [0] Cancelar  |" << endl;
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

            case 9: {
                if (items.empty()) {
                    cerr << "\n # Erro: Nao ha itens no carrinho para desfazer!" << endl;
                    TerminalUtils::pause();
                } else {
                    // O último item é pego para exibição
                    string lastItem = items.back();
                    // O último item inserido é removido
                    items.pop_back();

                    // Decrementa a quantidade correspondente ao item removido
                    if (lastItem == "Cachorro Quente") quantatyItems[0]--;
                    else if (lastItem == "Batata Frita") quantatyItems[1]--;
                    else if (lastItem == "Hamburguer") quantatyItems[2]--;
                    else if (lastItem == "Pizza") quantatyItems[3]--;
                    else if (lastItem == "Coca Zero") quantatyItems[4]--;

                    cout << "\n" << lastItem << " removido" << endl;
                    TerminalUtils::pause();
                }
                break;
            }

            case 10: {
                if (items.empty()) {
                    cerr << "\n # Erro: Adicione pelo menos um item ao pedido!" << endl;
                    TerminalUtils::pause();
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
                TerminalUtils::pause();
                break;

            default:
                cout << "\n # Erro: Opcao invalida!" << endl;
                TerminalUtils::pause();
                break;
        }

    } while (optionCadastrar != 0);
}


// Remover Pedido do cliente
void KitchenLinkedQueue::menuRemoveOrder() {
    if (this->isEmpty()) {
        cout << "======================= REMOVER PEDIDO ======================" << endl;
        cout << "                       # Lista Vazia! #                      " << endl;
        cout << " # Adicione um novo pedido antes de fazer alguma operacao! # " << endl;
        cout << "=============================================================";
        TerminalUtils::pause();
        return;
    }

    int optionRemove, numberOrder;

    cout << "\n > Informe o pedido: ";
    cin >> numberOrder;

    do {
        TerminalUtils::clear();
        cout << "================ REMOVER PEDIDO ================" << endl;
        if (this->search(numberOrder) == nullptr) {
            cout << "            # Pedido nao encontrado! #          " << endl;
            cout << "================================================" << endl;
            TerminalUtils::pause();
            return;
        }

        this->search(numberOrder)->data.showOrder();
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
    return;
}

// Buscar Pedido
void KitchenLinkedQueue::menuSearchOrder() {
    if (this->isEmpty()) {
        cout << "======================= BUSCAR PEDIDO =======================" << endl;
        cout << "                       # Lista Vazia! #                      " << endl;
        cout << " # Adicione um novo pedido antes de fazer alguma operacao! # " << endl;
        cout << "=============================================================";
        TerminalUtils::pause();
        return;
    }

    int numberOrder;

    cout << "\n > Informe o pedido: ";
    cin >> numberOrder;

    cout << "================= BUSCAR PEDIDO ================" << endl;
    if (this->search(numberOrder) == nullptr) {
        cout << "            # Pedido nao encontrado! #          " << endl;
        cout << "================================================" << endl;
        TerminalUtils::pause();
        return;
    }

    TerminalUtils::clear();
    cout << "=-=-=-=-=-=-=-= BUSCAR  PEDIDO =-=-=-=-=-=-=-=-=" << endl;
    this->search(numberOrder)->data.showOrder();
    cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    TerminalUtils::pause();

}

// Gerenciando Ações do Pedido
void KitchenLinkedQueue::menuManageOrder() {
    if (this->isEmpty()) {
        cout << "======================= ACOES DO PEDIDO =====================" << endl;
        cout << "                       # Lista Vazia! #                      " << endl;
        cout << " # Adicione um novo pedido antes de fazer alguma operacao! # " << endl;
        cout << "=============================================================";
        TerminalUtils::pause();
        return;
    }

    int optionManagerOrder = -1, numberOrder;

    cout << "\n > Informe o pedido: ";
    cin >> numberOrder;

    do {
        TerminalUtils::clear();
        cout << "================ ACOES DO PEDIDO ===============" << endl;
        if (this->search(numberOrder) == nullptr) {
            cout << "            # Pedido nao encontrado! #          " << endl;
            cout << "================================================" << endl;
            TerminalUtils::pause();
            return;
        }
        this->search(numberOrder)->data.showOrder();

        cout << "------------------------------------------------" << endl;
        cout << "| [1] Adicionar Item           [3] Desfazer    |" << endl;
        cout << "| [2] Remover Item             [0] Voltar      |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        // Sempre que ocorrer algum erro no cin
        if (!(cin >> optionManagerOrder)) {
            cin.clear();                   // Limpa o cin e acaba com o erro
            cin.ignore(1000, '\n');        // Pega o que foi digitado e remove o \n
            optionManagerOrder = -1;            // Reseta a variavel do menu
        }

        switch (optionManagerOrder) {
            case 1:
                menuAddItem(numberOrder);
                break;
            case 2:
                menuRemoveItem(numberOrder);
                break;
            case 3:
                // volta a uma versão anterior do pedido - acessando o nó
                undoOrder(numberOrder);
                break;
            case 0:
                cout << "\n Voltando ao menu anterior." << endl;
                TerminalUtils::pause();
                break;
            default:
                cout << "\n # Erro: Opcao invalida!" << endl;
                TerminalUtils::pause();
                break;
        }
    } while (optionManagerOrder != 0);

}

// Adicionando Item no pedido
void KitchenLinkedQueue::menuAddItem(int numberOrder) {
    if (this->isEmpty()) {
        cout << "======================= ADICIONAR ITEM ======================" << endl;
        cout << "                       # Lista Vazia! #                      " << endl;
        cout << " # Adicione um novo pedido antes de fazer alguma operacao! # " << endl;
        cout << "=============================================================";
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

    int optionAddItem = -1;

    Order orderBackup = node->data;
    LinkedStack orderChangesBackup(node->orderChanges);

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

        // Sempre que ocorrer algum erro no cin
        if (!(cin >> optionAddItem)) {
            cin.clear();                   // Limpa o cin e acaba com o erro
            cin.ignore(1000, '\n');        // Pega o que foi digitado e remove o \n
            optionAddItem = -1;            // Reseta a variavel do menu
        }
        
        if (optionAddItem >= 1 && optionAddItem <= 5) {
            node->orderChanges.push(node->data);
            node->data.addItem(optionAddItem - 1);

        } else if (optionAddItem == 0) {
            node->data = orderBackup;
            node->orderChanges = orderChangesBackup;

            return;
        } else if (optionAddItem == 10) {
            // alterações ja foram salvas quando adicionadas
            return;
        } else {
            cerr << "\n # Erro: Opcao invalida!" << endl;
            TerminalUtils::pause();
        }

    } while (optionAddItem != 0 && optionAddItem != 10);

}

// Removendo Item no pedido
void KitchenLinkedQueue::menuRemoveItem(int numberOrder) {
    if (this->isEmpty()) {
        cout << "======================== REMOVER ITEM =======================" << endl;
        cout << "                       # Lista Vazia! #                      " << endl;
        cout << " # Adicione um novo pedido antes de fazer alguma operacao! # " << endl;
        cout << "=============================================================";
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

    int optionRemoveItem = -1;

    Order orderBackup = node->data;
    LinkedStack orderChangesBackup(node->orderChanges);

    int orderNumber = node->data.getNumber();
    vector<string> items = node->data.getItems();

    do {
        TerminalUtils::clear();
        if (node == nullptr) {
            cout << "================= REMOVER ITEM =================" << endl;
            cout << "               # Pedido Excluido #              " << endl;
            cout << "================================================" << endl;
            TerminalUtils::pause();
            return;
        }

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

        // Sempre que ocorrer algum erro no cin
        if (!(cin >> optionRemoveItem)) {
            cin.clear();                   // Limpa o cin e acaba com o erro
            cin.ignore(1000, '\n');        // Pega o que foi digitado e remove o \n
            optionRemoveItem = -1;            // Reseta a variavel do menu
        }

        if (optionRemoveItem >= 1 && optionRemoveItem <= 5) {
            node->orderChanges.push(node->data);
            node->data.removeItem(optionRemoveItem - 1);

        } else if (optionRemoveItem == 0) {
            node->data = orderBackup;
            node->orderChanges = orderChangesBackup;

            return;
        } else if (optionRemoveItem == 10) {
            if (node->data.getTotal() == 0) {
                this->removeOrder(orderNumber);
            }
            return;
        } else {
            cerr << "\n # Erro: Opcao invalida!" << endl;
            TerminalUtils::pause();
        }

    } while (optionRemoveItem != 0 && optionRemoveItem != 10);

}

// Enviando peidido realizado para o histórico e pilha
void KitchenLinkedQueue::prepareOrder(HistoricDoublyLinkedList& historicList) {
    if (this->isEmpty()) {
        cout << " # Fila Vazia! #" << endl;
        TerminalUtils::pause();
        return;
    }

    Order order = this->head->data;
    TerminalUtils::pause();
    counterOrders.push(order);
    historicList.insertEnd(order);
    this->dequeue();
}

// Escolhar mandar o pedido ser preparado
void KitchenLinkedQueue::menuKitchen(HistoricDoublyLinkedList& historicList) {
    int option;

    do {
        TerminalUtils::clear();
        cout << "============== PEDIDOS EM PRODUCAO =============" << endl;
        
        if (this->isEmpty()) {
            cout << "    # Pilha de 'Pedidos em Producao' Vazia! #   " << endl;
            cout << "================================================" << endl;
            TerminalUtils::pause();
            return;
        }
        this->showOrders();

        cout << "------------------------------------------------" << endl;
        cout << "|  [1] Entregar                    [0] Sair    |" << endl;
        cout << "================================================" << endl;

        cout << " > Escolher uma opcao: ";
        cin >> option;

        switch (option) {
            case 1: {
                prepareOrder(historicList);
                break;
            }
            case 0:
                return;
        default:
            cerr << "\n # Erro: Opcao invalida!" << endl;
            TerminalUtils::pause();
            break;
        }

    } while (option != 0);
}

// Mostrando os pedidos do balcão
void KitchenLinkedQueue::menuCounterOrders() {
    int option;

    do {
        TerminalUtils::clear();
        cout << "=============== PEDIDOS PRONTOS ===============" << endl;

        if (this->counterOrders.isEmpty()) {
            cout << "        # Pilha de 'Pedidos Pronto' Vazia #       " << endl;
            cout << "===============================================" << endl;
            TerminalUtils::pause();
            return;
        }
        this->counterOrders.showCounterOrders();
            
        cout << "------------------------------------------------" << endl;
        cout << "|  [1] Entregar                    [0] Sair    |" << endl;
        cout << "================================================" << endl;

        cout << " > Escolher uma opcao: ";
        cin >> option;

        switch (option) {
            case 1: {
                this->counterOrders.pop();
                break;
            }
            case 0:
                return;
        default:
            cerr << "\n # Erro: Opcao invalida!" << endl;
            TerminalUtils::pause();
            break;
        }

    } while (option != 0);
}  