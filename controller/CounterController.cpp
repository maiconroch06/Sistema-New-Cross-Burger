#include "CounterController.hpp"
#include "../view/MenuViews.hpp"
#include "../utils/TerminalUtils.hpp"
#include <iostream>

using namespace std;

CounterController::CounterController(KitchenLinkedQueue& queue) : fila(queue) {
    menuNames = {"Cachorro Quente", "Batata Frita", "Hamburguer", "Pizza", "Coca Zero"};
}

void CounterController::runMenuCounter() {
    int option;
    do {
        TerminalUtils::clear();
        fila.showOrders();
        MenuViews::drawMenuCounter();

        cin >> option;

        switch (option) {
            case 1: menuRegisterOrder(); break;
            case 2: menuRemoveOrder(); break;
            case 3: menuManageOrder(); break;
            case 4: menuSearchOrder(); break;
            case 0: cout << "\nOperacao cancelada." << endl; break;
            default: 
                cout << "\n # Erro: Opcao invalida!" << endl;
                TerminalUtils::pause();
                break;
        }
    } while (option != 0);
}

void CounterController::menuRegisterOrder() {
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
        MenuViews::drawCart(menuNames, quantatyItems);
        MenuViews::drawHeader("CADASTRAR PEDIDO");
        MenuViews::drawMenu();
        cout << "------------------------------------------------" << endl;
        cout << "| [10] Finalizar Pedido         [0] Cancelar   |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
        cin >> optionCadastrar;

        if (optionCadastrar >= 1 && optionCadastrar <= 5) {
            items.push_back(menuNames[optionCadastrar - 1]);
            quantatyItems[optionCadastrar - 1]++;
        } else if (optionCadastrar == 10) {
            if (items.empty()) {
                cout << "\n # Erro: Adicione pelo menos um item ao pedido!" << endl;
                TerminalUtils::pause();
            } else {
                Order order(client, items, quantatyItems);
                fila.enqueue(order);

                TerminalUtils::clear();
                cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
                cout << "          Pedido cadastrado com sucesso!        " << endl;
                cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
                TerminalUtils::pause();
                optionCadastrar = 0;
            }
        }
    } while (optionCadastrar != 0);
}

void CounterController::menuRemoveOrder() {
    if (fila.isEmpty()) {
        cout << " # Lista Vazia! #" << endl;
        TerminalUtils::pause();
        return;
    }

    int numberOrder, optionRemove;
    cout << "\n > Informe o pedido: ";
    cin >> numberOrder;

    NodeQueue* node = fila.search(numberOrder);
    if (node == nullptr) {
        cout << "\n # Pedido nao encontrado! #" << endl;
        TerminalUtils::pause();
        return;
    }

    do {
        TerminalUtils::clear();
        MenuViews::drawHeader("REMOVER PEDIDO");
        node->data.showOrder();
        cout << "------------------------------------------------" << endl;
        cout << " #    Deseja confirmar a remocao do pedido?   # " << endl;
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Confirmar Acao             [0] Cancelar  |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
        cin >> optionRemove;

        if (optionRemove == 1) {
            fila.removeOrder(numberOrder);
            TerminalUtils::pause();
            return;
        }
    } while (optionRemove != 0);
}

void CounterController::menuSearchOrder() {
    if (fila.isEmpty()) {
        cout << " # Lista Vazia! #" << endl;
        TerminalUtils::pause();
        return;
    }

    int numberOrder;
    cout << "\n > Informe o pedido: ";
    cin >> numberOrder;

    TerminalUtils::clear();
    cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    NodeQueue* node = fila.search(numberOrder);
    if (node == nullptr) {
        cout << " # Pedido nao encontrado! #" << endl;
    }
    cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    TerminalUtils::pause();
}

void CounterController::menuManageOrder() {
    if (fila.isEmpty()) {
        cout << " # Lista Vazia! #" << endl;
        TerminalUtils::pause();
        return;
    }

    int numberOrder;
    cout << "\n > Informe o pedido: ";
    cin >> numberOrder;

    NodeQueue* node = fila.search(numberOrder);
    if (node == nullptr) {
        cout << "\n # Pedido nao encontrado! #" << endl;
        TerminalUtils::pause();
        return;
    }

    int option;
    do {
        TerminalUtils::clear();
        MenuViews::drawHeader("GERENCIAR PEDIDO #" + to_string(numberOrder));
        node->data.showOrder();
        MenuViews::drawMenuManageOrder();
        cin >> option;

        switch (option) {
            case 1: menuAddItem(node); break;
            case 2: menuRemoveItem(node); break;
            case 3: fila.undoOrder(numberOrder); break;
            case 0: cout << "\nVoltando ao menu anterior." << endl; break;
            default:
                cout << "\n # Erro: Opcao invalida!" << endl;
                TerminalUtils::pause();
                break;
        }
    } while (option != 0);
}

void CounterController::menuAddItem(NodeQueue* node) {
    int option;
    do {
        TerminalUtils::clear();
        MenuViews::drawCart(menuNames, node->data.getQuantatyItems());
        MenuViews::drawHeader("ADICIONAR ITEM");
        MenuViews::drawMenu();                  // Cardapio
        cout << "------------------- PEDIDO #" << node->data.getNumber() << " ------------------" << endl;
        cout << "| [10] Finalizar Alteracao     [0] Cancelar    |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
        cin >> option;

        if (option >= 1 && option <= 5) {
            node->stackOrders.push(node->data); // Salva para Undo
            node->data.addItem(option - 1);     // Altera pedido
        }
    } while (option != 0 && option != 10);
}

void CounterController::menuRemoveItem(NodeQueue* node) {
    int option;
    do {
        TerminalUtils::clear();
        MenuViews::drawCart(menuNames, node->data.getQuantatyItems());
        MenuViews::drawHeader("REMOVER ITEM");
        MenuViews::drawMenu();                 // Cardapio
        cout << "------------------- PEDIDO #" << node->data.getNumber() << " ------------------" << endl;
        cout << "| [10] Finalizar Alteracao     [0] Cancelar    |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
        cin >> option;

        if (option >= 1 && option <= 5) {
            node->stackOrders.push(node->data); // Salva para Undo
            node->data.removeItem(option - 1);  // Altera pedido
        }
    } while (option != 0 && option != 10);
}