#include <iostream>
#include "models/Order.hpp"
#include "models/HistoricDoublyLinkedList.hpp"

using namespace std;

int menuPrincipal();
int menuGerenciarPedido();
int menuVisualizarHistoricoPedido(HistoricDoublyLinkedList listOrders);

int main() {
    HistoricDoublyLinkedList listOrders;

    Order order1(1, "Maicon", {"Hamburguer", "Batata Frita"}, 25.50f);
    Order order2(2, "Estudante", {"Pizza GG", "Coca Zero", "Sobremesa"}, 68.50f);
    Order order3(3, "Rocha", {"Milk Shake", "Batata Frita"}, 25.50f);

    listOrders.insert(order1);
    listOrders.insert(order2);
    listOrders.insertEnd(order3);

    listOrders.printList();
    
    int option;
    do {
        // Menu principal
        option = menuPrincipal();

        switch (option) {
        case 1:
            // Menu de gerenciar pedido
            int option;
            option = menuGerenciarPedido();

            switch (option) {
            case 1:
                // Gerenciar Pedido

                break;
            case 2:
                // Visualizar Historico de Pedido
                break;
            case 3:
                // Operacoes Principais
                break;
            
            default:
                cout << "\n # ERRO: Opcao invalida!" << endl;
                break;
            }

            break;
        case 2:
            // Menu de visualizar historico de pedido
            int index = 0;
            do {
                option = menuVisualizarHistoricoPedido(listOrders, index);
            } while(option != 0);
            break;
        case 3:
            // Operacoes principais
            break;
        default:
            cout << "\n # ERRO: Opcao invalida!" << endl;
            break;
        }

    } while(option != 0);

    return 0;
}

int menuPrincipal() {
    int option;
    cout << "============= NEW CROSS BURGER =============" << endl;
    cout << "| [1] Gerenciar Pedido                     |";
    cout << "| [2] Visualizar Historico de Pedido       |";
    cout << "| [3] Operacoes Principais                 |";
    cout << "| [0] Sair                                 |";
    cout << "============================================" << endl;
    cout << " > Escolha uma opcao: ";
    cin >> option;
    return option;
}

int menuGerenciarPedido() {
    int option;
    cout << "============= NEW CROSS BURGER =============" << endl;
    cout << "| [1] Cadastrar Pedido                     |"; // Iniserir no fim
    cout << "| [2] Buscar Pedido                        |";
    cout << "| [2] Buscar Pedido                        |";
    cout << "| [3] Atualizar Pedido                     |";
    cout << "| [4] Deletar Pedido                       |";
    cout << "| [0] Voltar                               |";
    cout << "============================================" << endl;
    cout << " > Escolha uma opcao: ";
    cin >> option;
    return option;
}

int menuVisualizarHistoricoPedido(HistoricDoublyLinkedList listOrders, int index) {
    int option;
    cout << "============= NEW CROSS BURGER =============" << endl;
                        listOrders.search(index);
    cout << "| [1] Anterior   [0] Voltar   [2] Proximo  |";
    cout << "============================================" << endl;
    cout << " > Escolha uma opcao: ";
    cin >> option;
    return option;
}

int menuOperacoesPrincipais() {
    int option;
    cout << "============= NEW CROSS BURGER =============" << endl;
    cout << "| [1] Cadastrar Pedido                     |";
    cout << "| [2]                            |";
    cout << "| [0] Voltar                               |";
    cout << "============================================" << endl;
    cout << " > Escolha uma opcao: ";
    cin >> option;
    return option;
}