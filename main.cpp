#include <iostream>
#include <vector>

#include "models/Order.hpp"
#include "models/LinkedStack.hpp"
#include "models/HistoricDoublyLinkedList.hpp"
#include "models/KitchenLinkedQueue.hpp"

#include "utils/TerminalUtils.hpp"

using namespace std;

// Protótipos das funções
int menuPrincipal();
    void operacoesBalcao();
    void cadastrarPedido();
    void removerPedido();
    void exibirHistoricOrders();

int main() {
    HistoricDoublyLinkedList DoublyLinkedListOrders = HistoricDoublyLinkedList();
    KitchenLinkedQueue kitchenLinkedQueueOrders;

    // Pedidos de exemplo
    /*Order order1(1, "Maicon", {"Hamburguer", "Batata Frita"}, 45.0f);
    Order order2(3, "Estudante", {"Pizza GG", "Coca Zero", "Sobremesa"}, 50.0f);
    Order order3(4, "Rocha", {"Milk Shake", "Batata Frita"}, 20.0f);

    kitchenLinkedQueueOrders.enqueue(order1);
    kitchenLinkedQueueOrders.enqueue(order2);
    kitchenLinkedQueueOrders.enqueue(order3);

    DoublyLinkedListOrders.insertEnd(order1);
    DoublyLinkedListOrders.insertEnd(order2);
    DoublyLinkedListOrders.insertEnd(order3);*/

    int optionMain;
    do {
        TerminalUtils::clear(); // Limpar terminal
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