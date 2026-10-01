#include <iostream>
#include "models/Order.hpp"
#include "models/ActionsLinkedStack.hpp"
#include "models/HistoricDoublyLinkedList.hpp"
#include "models/KitchenLinkedQueue.hpp"

using namespace std;

// Protótipos das Funções
int menuPrincipal();
int menuGerenciarPedido();
int menuOperacoesPrincipais();

int main() {
    ActionsLinkedStack stackOrders;
    HistoricDoublyLinkedList listOrders;
    KitchenLinkedQueue queueOrders;

    Order order1("Maicon", {"Hamburguer", "Batata Frita"});
    Order order2("Estudante", {"Pizza GG", "Coca Zero", "Sobremesa"});
    Order order3("Rocha", {"Milk Shake", "Batata Frita"});

    listOrders.insertEnd(order1);
    listOrders.insertEnd(order2);
    listOrders.insertEnd(order3);
    
    int option;
    do {
        // Gerenciar Pedido, Visualizar Historico, 
        option = menuPrincipal();
        switch (option) {
            case 1: {
                int option;
                do {
                    // Cadastrar, Pesquisar, Remover, Atualizar e Exibir Todos os pedidos
                    option = menuGerenciarPedido();
                    switch (option) {
                        case 1:
                            int option;
                            int quantity;
                            string client;

                            Order order;
                            vector<string> items;
                            
                            // Um for deve ser implementado, seguindo a seguinte logica: confirmando se vai ser cadastrado um pedido novo ou não.
                            cout << " > Nome Cliente: ";
                            cin >> client;
                            // Se repetirá quantas vezes quiser para selecionar uma comida no cardapio
                            do {

                                cout << "============= CADASTRAR PEDIDO =================" << endl;
                                cout << "| [1] Cachorro Quente         R$ 5.00          |" << endl;
                                cout << "| [2] Batata Frita            R$ 6.00          |" << endl;
                                cout << "| [3] Hambuger                R$ 20.00         |" << endl;
                                cout << "| [4] Pizza                   R$ 46.00         |" << endl;
                                cout << "| [5] Coca Zero               R$ 9.00          |" << endl;
                                cout << "------------------------------------------------" << endl;
                                cout << "|     [10] Confirmar          [0] Cancelar     |" << endl;
                                cout << "================================================" << endl;
                                cout << " > Escolha uma opcao: ";
                                cin >> option;
                                cout << " > Escolha uma quantidade: ";
                                cin >> quantity;
                                
                                switch (option) {
                                case 1:
                                    items.push_back("Cachorro Quente");
                                    break;
                                case 2:
                                    items.push_back("Batata Frita");
                                    break;
                                case 3:
                                    items.push_back("Hambuger");
                                    break;
                                case 4:
                                    items.push_back("Pizza");
                                    break;
                                case 5:
                                    items.push_back("Coca Zero");
                                    break;
                                case 10:  // Pedido foi confirmado e sai
                                    order = Order(client, items);
                                    queueOrders.enqueue(order);
                                    break;
                                
                                default:
                                cout << "\n # ERRO: Opcao invalida!\n" << endl;
                                break;
                            }
                            
                            } while (option != 0 || option == 10);
                            
                        }
                            break;
                        } while (option != 0);

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

                } while (option != 0); // Menu Gerenciar Pedido
                break;
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


int menuPrincipal() {
    int option;
    cout << "\n============= NEW CROSS BURGER =============" << endl;
    cout << "| [1] Gerenciar Pedido                     |" << endl;
    cout << "| [2] Visualizar Historico de Pedido       |" << endl;
    cout << "| [3] Operacoes Principais                 |" << endl;
    cout << "| [0] Sair                                 |" << endl;
    cout << "============================================" << endl;
    cout << " > Escolha uma opcao: ";
    cin >> option;
    return option;
}

int menuGerenciarPedido() {
    int option;
    cout << "\n============= GERENCIAR PEDIDO =============" << endl;
    cout << "| [1] Cadastrar Pedido                     |" << endl;
    cout << "| [2] Buscar Pedido                        |" << endl;
    cout << "| [3] Atualizar Pedido                     |" << endl;
    cout << "| [4] Deletar Pedido                       |" << endl;
    cout << "| [0] Voltar                               |" << endl;
    cout << "============================================" << endl;
    cout << " > Escolha uma opcao: ";
    cin >> option;
    return option;
}