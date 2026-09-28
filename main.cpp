#include <iostream>
#include "models/Order.hpp"
#include "models/HistoricDoublyLinkedList.hpp"

using namespace std;

int main() {
    HistoricDoublyLinkedList listOrders;

    Order order1(1, "Maicon", {"Hamburguer", "Batata Frita"}, 25.50f);
    Order order2(2, "Estudante", {"Pizza GG", "Coca Zero", "Sobremesa"}, 68.50f);
    Order order3(3, "Rocha", {"Milk Shake", "Batata Frita"}, 25.50f);

    listOrders.insert(order1);
    listOrders.insert(order2);
    listOrders.insertEnd(order3);

    listOrders.printList();
    NodeList* first = head;

    listOrders.nextOrder(first&);
    listOrders.previousOrder(first&);
    int option;
    do {


        switch (option) {
        case 1:
            //menuGerenciarPedido();
            int option;
            do {
                cout << "============= NEW CROSS BURGER ==============" << endl;
                cout << "| [1] Cadastrar Pedido"; // Iniserir no fim
                cout << "| [2] Buscar Pedido";
                cout << "| [3] Cadastrar Pedido";
                cout << "| [4] Buscar Pedido";
                cout << "| [0] Sair";
                cout << "=============================================" << endl;
                cout << " > Escolha uma opcao: ";
                cin >> option;

                switch (option) {
                case 1:
                    /* code */
                    break;
                
                default:
                    break;
                }

            } while (option != 0);

            break;
        case 2:
            //menuCadastrarPedido();
            break;
        
        default:
            break;
        }

    } while(option != 0);

    return 0;
}