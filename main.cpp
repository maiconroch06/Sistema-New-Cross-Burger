#include <iostream>
#include <vector>

#include "models/Order.hpp"
#include "models/ActionsLinkedStack.hpp"
#include "models/HistoricDoublyLinkedList.hpp"
#include "models/KitchenLinkedQueue.hpp"

#include "utils/TerminalUtils.hpp"

using namespace std;

// Protótipos das funções
int menuPrincipal();
    void operacoesBalcao();
    void cadastrarPedido();
    void removerPedido();
    void exibirHistoricoPedidos();

int main() {
    HistoricDoublyLinkedList HistoricDoublyLinkedListOrders;
    KitchenLinkedQueue kitchenLinkedQueueOrders;

    // Pedidos de exemplo
    Order order1(1, "Maicon", {"Hamburguer", "Batata Frita"}, 45.0f);
    Order order2(3, "Estudante", {"Pizza GG", "Coca Zero", "Sobremesa"}, 50.0f);
    Order order3(4, "Rocha", {"Milk Shake", "Batata Frita"}, 20.0f);

    kitchenLinkedQueueOrders.enqueue(order1);
    kitchenLinkedQueueOrders.enqueue(order2);
    kitchenLinkedQueueOrders.enqueue(order3);

    HistoricDoublyLinkedListOrders.insertEnd(order1);
    HistoricDoublyLinkedListOrders.insertEnd(order2);
    HistoricDoublyLinkedListOrders.insertEnd(order3);

    int optionMain;
    do {
        TerminalUtils::clear(); // Limpar terminal
        optionMain = menuPrincipal();

        switch (optionMain) {
            case 1:
                kitchenLinkedQueueOrders.menuOperacoesBalcao();
                break;
            case 2:
                // Implementar operações da cozinha
                
                break;
            case 3:
                HistoricDoublyLinkedListOrders.menuExibirHistoricoPedidos();
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
    cout << "| [1] Operacoes do Balcao                  |" << endl;
    cout << "| [2] Operacoes da Cozinha                 |" << endl;
    cout << "| [3] Exibir Historico de Pedidos          |" << endl;
    cout << "| [0] Sair                                 |" << endl;
    cout << "============================================" << endl;
    cout << " > Escolha uma opcao: ";

    cin >> option;

    return option;
}