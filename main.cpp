#include <iostream>
#include <vector>

#include "models/Order.hpp"
#include "models/ActionsLinkedStack.hpp"
#include "models/HistoricDoublyLinkedList.hpp"
#include "models/KitchenLinkedQueue.hpp"

using namespace std;

// Protótipos das funções
int menuPrincipal();
int menuGerenciarPedido();
int menuCadastrarPedido();
int menuOperacoesPrincipais();

int main() {
    ActionsLinkedStack stackOrders;
    HistoricDoublyLinkedList listOrders;
    KitchenLinkedQueue queueOrders;

    // Pedidos de exemplo
    Order order1(1, "Maicon", {"Hamburguer", "Batata Frita"}, 45.0);
    Order order2(2, "Estudante", {"Pizza GG", "Coca Zero", "Sobremesa"}, 50.0);
    Order order3(3, "Rocha", {"Milk Shake", "Batata Frita"}, 20.0);

    listOrders.insertEnd(order1);
    listOrders.insertEnd(order2);
    listOrders.insertEnd(order3);

    int option;

    do {
        option = menuPrincipal();

        switch (option) {

            // GERENCIAR PEDIDO - Menu Principal
            case 1: {
                int optionGerenciar;

                do {
                    optionGerenciar = menuGerenciarPedido();

                    switch (optionGerenciar) {

                        // CADASTRAR PEDIDO - Menu Gerenciar Pedido
                        case 1: {
                            vector<string> items;
                            string client;

                            cout << "\n============= NOVO PEDIDO =============" << endl;
                            cout << " > Nome Cliente: ";
                            cin >> client;

                            int optionCadastrar;

                            do {
                                optionCadastrar = menuCadastrarPedido();

                                switch (optionCadastrar) {

                                    case 1:
                                        items.push_back("Cachorro Quente");
                                        cout << "\nItem adicionado!" << endl;
                                        break;

                                    case 2:
                                        items.push_back("Batata Frita");
                                        cout << "\nItem adicionado!" << endl;
                                        break;

                                    case 3:
                                        items.push_back("Hamburguer");
                                        cout << "\nItem adicionado!" << endl;
                                        break;

                                    case 4:
                                        items.push_back("Pizza");
                                        cout << "\nItem adicionado!" << endl;
                                        break;

                                    case 5:
                                        items.push_back("Coca Zero");
                                        cout << "\nItem adicionado!" << endl;
                                        break;

                                    case 10:
                                        if (items.empty()) {
                                            cout << "\n # ERRO: Adicione pelo menos um item ao pedido!" << endl;
                                        } else {
                                            Order order(client, items);

                                            queueOrders.enqueue(order);
                                            listOrders.insertEnd(order);

                                            cout << "\nPedido cadastrado com sucesso!" << endl;

                                            // Sai do cadastro
                                            optionCadastrar = 0;
                                        }
                                        break;

                                    case 0:
                                        cout << "\nCadastro cancelado." << endl;
                                        break;

                                    default:
                                        cout << "\n # ERRO: Opcao invalida!" << endl;
                                        break;
                                }

                            } while (optionCadastrar != 0);

                            break;
                        }

                        // BUSCAR PEDIDO - Menu Gerenciar Pedido
                        case 2:
                            cout << "\nBuscar Pedido - ainda nao implementado." << endl;
                            break;

                        // ATUALIZAR PEDIDO - Menu Gerenciar Pedido
                        case 3:
                            cout << "\nAtualizar Pedido - ainda nao implementado." << endl;
                            break;

                        // DELETAR PEDIDO - Menu Gerenciar Pedido
                        case 4:
                            cout << "\nDeletar Pedido - ainda nao implementado." << endl;
                            break;

                        case 0:
                            break;

                        default:
                            cout << "\n # ERRO: Opcao invalida!" << endl;
                            break;
                    }

                } while (optionGerenciar != 0);

                break;
            }

            // HISTÓRICO DE PEDIDOS - Menu Principal
            case 2: {
                int optionHistorico;
                int historicIndex = 1;

                do {
                    cout << "\n============= HISTORICO DE PEDIDOS =============" << endl;

                    listOrders.search(historicIndex);

                    cout << "------------------------------------------------" << endl;
                    cout << "| [1] Anterior   [0] Voltar   [2] Proximo     |" << endl;
                    cout << "| [3] Exibir todos os pedidos                  |" << endl;
                    cout << "================================================" << endl;
                    cout << " > Escolha uma opcao: ";

                    cin >> optionHistorico;

                    switch (optionHistorico) {

                        case 1:
                            historicIndex =
                                listOrders.previousOrder(historicIndex);
                            break;

                        case 2:
                            historicIndex =
                                listOrders.nextOrder(historicIndex);
                            break;

                        case 3:
                            listOrders.showOrders();
                            break;

                        case 0:
                            break;

                        default:
                            cout << "\n # ERRO: Opcao invalida!" << endl;
                            break;
                    }

                } while (optionHistorico != 0);

                break;
            }

            // OPERAÇÕES PRINCIPAIS - Menu Principal
            case 3: {
                int optionOperacoes;

                do {
                    optionOperacoes = menuOperacoesPrincipais();

                    switch (optionOperacoes) {

                        case 1:
                            cout << "\nCadastrar Pedido - utilize o menu Gerenciar Pedido." << endl;
                            break;

                        case 0:
                            break;

                        default:
                            cout << "\n # ERRO: Opcao invalida!" << endl;
                            break;
                    }

                } while (optionOperacoes != 0);

                break;
            }

            // SAIR - Menu Principal
            case 0:
                cout << "\nEncerrando o sistema..." << endl;
                break;

            default:
                cout << "\n # ERRO: Opcao invalida!" << endl;
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



int menuCadastrarPedido() {
    int option;

    cout << "\n============= CADASTRAR PEDIDO =================" << endl;
    cout << "| [1] Cachorro Quente         R$ 8.00          |" << endl;
    cout << "| [2] Batata Frita            R$ 6.00          |" << endl;
    cout << "| [3] Hamburguer              R$ 20.00         |" << endl;
    cout << "| [4] Pizza                   R$ 46.00         |" << endl;
    cout << "| [5] Coca Zero               R$ 12.00         |" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "| [10] Confirmar              [0] Cancelar     |" << endl;
    cout << "================================================" << endl;
    cout << " > Escolha uma opcao: ";

    cin >> option;

    return option;
}



int menuOperacoesPrincipais() {
    int option;

    cout << "\n============= OPERACOES PRINCIPAIS =============" << endl;
    cout << "| [1] Cadastrar Pedido                         |" << endl;
    cout << "| [0] Voltar                                   |" << endl;
    cout << "================================================" << endl;
    cout << " > Escolha uma opcao: ";

    cin >> option;

    return option;
}
