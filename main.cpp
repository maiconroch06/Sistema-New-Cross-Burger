#include <iostream>
#include "models/Order.hpp"
#include "models/ActionsLinkedStack.hpp"
#include "models/HistoricDoublyLinkedList.hpp"
#include "models/KitchenLinkedQueue.hpp"

using namespace std;

// Protótipos das Funções
int menuOperacoesPrincipais();

int main() {
    ActionsLinkedStack stackOrders;
    HistoricDoublyLinkedList listOrders;
    KitchenLinkedQueue queueOrders;

    Order order1(1, "Maicon", {"Hamburguer", "Batata Frita"}, 25.50f);
    Order order2(2, "Estudante", {"Pizza GG", "Coca Zero", "Sobremesa"}, 68.50f);
    Order order3(3, "Rocha", {"Milk Shake", "Batata Frita"}, 25.50f);

    listOrders.insertEnd(order1);
    listOrders.insertEnd(order2);
    listOrders.insertEnd(order3);
    
    int option;
    do {
        cout << "\n============= NEW CROSS BURGER =============" << endl;
        cout << "| [1] Gerenciar Pedido                     |" << endl;
        cout << "| [2] Visualizar Historico de Pedido       |" << endl;
        cout << "| [3] Operacoes Principais                 |" << endl;
        cout << "| [0] Sair                                 |" << endl;
        cout << "============================================" << endl;
        cout << " > Escolha uma opcao: ";
        cin >> option;
        
        switch (option) {
        case 1: {
            int option;
            do {
            cout << "\n============= GERENCIAR PEDIDO =============" << endl;
            cout << "| [1] Cadastrar Pedido                     |" << endl;
            cout << "| [2] Buscar Pedido                        |" << endl;
            cout << "| [3] Atualizar Pedido                     |" << endl;
            cout << "| [4] Deletar Pedido                       |" << endl;
            cout << "| [0] Voltar                               |" << endl;
            cout << "============================================" << endl;
            cout << " > Escolha uma opcao: ";
            cin >> option;

            switch (option) {
            case 1:
                int option;
                int quantity;
                string cliente;
                do {
                    cout << "============= CADASTRAR PEDIDO =============" << endl;
                    cout << "| [1] Cachorro Quente         R$ 5.00             |" << endl;
                    cout << "| [2] Batata Frita                         |" << endl;
                    cout << "| [3] Hambuger                             |" << endl;
                    cout << "| [4] Pizza                                |" << endl;
                    cout << "| [5] Coca Zero                            |" << endl;
                    cout << "------------------------------------------------" << endl;
                    cout << "|    [1] Anterior   [0] Voltar   [2] Proximo   |" << endl;
                    cout << "================================================" << endl;
                    cout << " > Escolha uma opcao: ";
                    cin >> option;
                    cout << " > Escolha uma quantidade: ";
                    cin >> quantity;
                    cout << " > Nome Cliente: ";
                    cin >> cliente;

                    switch (option) {
                    case 1:
                        listOrders.insertEnd("Cachorro Quente", cliente);
                        break;
                    case 2:
                    
                        break;
                    case 3:
                    
                        break;
                    case 4:
                    
                        break;
                    case 5:
                        
                        break;
                    
                    default:
                        cout << "\n # ERRO: Opcao invalida!\n" << endl;
                        break;
                    }

                    } while (option != 0);
                } while (option != 0);
                break;

            case 2:
                // Buscar Pedido
                break;
            case 3:
                // Atualizar Pedido
                break;
            case 4:
                // Deletar Pedido
                break;
            case 0:
                break;
            default:
                cout << "\n # ERRO: Opcao invalida!\n" << endl;
                break;
            }

            break;
        }
        case 2: {
            int option;
            int historicIndex = 1;
            do {
                cout << "\n============= HISTORICO DE PEDIDOS =============" << endl;
                listOrders.search(historicIndex);
                cout << "------------------------------------------------" << endl;
                cout << "|    [1] Anterior   [0] Voltar   [2] Proximo   |" << endl;
                cout << "================================================" << endl;
                cout << " > Escolha uma opcao: ";
                cin >> option;

                switch (option) {
                case 1:
                    historicIndex = listOrders.previousOrder(historicIndex);
                    break;
                    
                case 2:
                    historicIndex = listOrders.nextOrder(historicIndex);
                    break;

                case 3:
                    listOrders.showOrders();
                    break;
                    
                
                default:
                    break;
                }

            } while (option != 0);

            break;
        }
        case 3: {
            // Operações principais
            int option;
            cout << "\n============= OPERACOES PRINCIPAIS =============" << endl;
            cout << "| [1] Cadastrar Pedido                         |" << endl;
            cout << "| [0] Voltar                                   |" << endl;
            cout << "================================================" << endl;
            cout << " > Escolha uma opcao: ";
            cin >> option;

            switch (option) {
            case 1:
                /* code */
                break;
            case 2:
                /* code */
                break;
            
            default:
                break;
            }

            break;
        }
        case 0:
            cout << "\nEncerrando o sistema..." << endl;
            listOrders.~HistoricDoublyLinkedList(); // Liberar memoria
            break;
        default:
            cout << "\n # ERRO: Opcao invalida!\n" << endl;
            break;
        }

    } while (option != 0);

    return 0;
}
