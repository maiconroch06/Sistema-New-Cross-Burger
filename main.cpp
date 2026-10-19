#include <iostream>

#include "models/Order.hpp"
#include "models/LinkedStack.hpp"
#include "models/HistoricDoublyLinkedList.hpp"
#include "models/KitchenLinkedQueue.hpp"

#include "utils/TerminalUtils.hpp"

using namespace std;

// Protótipos das funções
int menuPrincipal();

int main() {
    HistoricDoublyLinkedList DoublyLinkedListOrders = HistoricDoublyLinkedList();
    KitchenLinkedQueue kitchenLinkedQueueOrders;

    Order order1("Maicon", {1, 1, 1, 1, 1});
    Order order2("Samuel", {2, 2, 2, 2, 2});
    Order order3("Danilo", {3, 3, 3, 3, 3});
    Order order4("Thiago", {1, 1, 0, 0, 0});
    Order order5("A", {1, 0, 5, 0, 0});

    kitchenLinkedQueueOrders.enqueue(order1);
    kitchenLinkedQueueOrders.enqueue(order2);
    kitchenLinkedQueueOrders.enqueue(order3);
    kitchenLinkedQueueOrders.enqueue(order4);
    kitchenLinkedQueueOrders.enqueue(order5);

    int optionMain;
    do {
        TerminalUtils::clear();
        optionMain = menuPrincipal();

        switch (optionMain) {
            case 1:
                kitchenLinkedQueueOrders.menuOperacoesBalcao();
                break;
            case 2:
                kitchenLinkedQueueOrders.menuKitchen(DoublyLinkedListOrders);
                break;
            case 3:
                kitchenLinkedQueueOrders.menuCounterOrders();
                break;
            case 4:
                DoublyLinkedListOrders.menuExibirHistoricOrders();
                break;
            case 0:
                cout << "\nSaindo do programa..." << endl;
                break;
            default:
                cout << "\n # ERRO: Opcao invalida!" << endl;
                break;
        }

    } while(optionMain != 0);

    return 0;
}


int menuPrincipal() {
    int option;

    cout << "============= NEW CROSS BURGER =============" << endl;
    cout << "| [1] Operacoes do Pedido                  |" << endl;
    cout << "| [2] Operacoes da Cozinha                 |" << endl;
    cout << "| [3] Pedidos do Balcao                    |" << endl;
    cout << "| [4] Exibir Historico de Pedidos          |" << endl;
    cout << "| [0] Sair                                 |" << endl;
    cout << "============================================" << endl;
    cout << " > Escolha uma opcao: ";

    cin >> option;

    return option;
}