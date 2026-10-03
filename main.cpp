#include <iostream>
#include <vector>

#include "models/Order.hpp"
#include "models/ActionsLinkedStack.hpp"
#include "models/HistoricDoublyLinkedList.hpp"
#include "models/KitchenLinkedQueue.hpp"

using namespace std;

// Protótipos das funções
void menuPrincipal();
    void operacoesBalcao();
        void cadastrarPedido();
        void removerPedido();
    void exibirHistoricoPedidos();

int main() {
    ActionsLinkedStack stackOrders;
    HistoricDoublyLinkedList listOrders;
    KitchenLinkedQueue queueOrders;

    // Pedidos de exemplo
    Order order1(1, "Maicon", {"Hamburguer", "Batata Frita"}, 45.0f);
    Order order2(2, "Estudante", {"Pizza GG", "Coca Zero", "Sobremesa"}, 50.0f);
    Order order3(3, "Rocha", {"Milk Shake", "Batata Frita"}, 20.0f);

    queueOrders.enqueue(order1);
    queueOrders.enqueue(order2);
    queueOrders.enqueue(order3);

    listOrders.insertEnd(order1);
    listOrders.insertEnd(order2);
    listOrders.insertEnd(order3);

    queueOrders.setQuantatyOrders(3);

    int optionMain = menuPrincipal();

    switch (optionMain) {
        case 1:
            operacoesBalcao();
            break;
        case 2:
            // Implementar operações da cozinha
            break;
        case 3:
            exibirHistoricoPedidos();
            break;
        case 0:
            cout << "\nSaindo do programa..." << endl;
            break;
        default:
            cout << "\n # ERRO: Opcao invalida!" << endl;
            break;
    }

    return 0;
}


int menuPrincipal() {
    int option;

    cout << "\n============= NEW CROSS BURGER =============" << endl;
    cout << "| [1] Operacoes do Balcao                  |" << endl;
    cout << "| [2] Operacoes da Cozinha                 |" << endl;
    cout << "| [3] Exibir Historico de Pedidos          |" << endl;
    cout << "| [0] Sair                                 |" << endl;
    cout << "============================================" << endl;
    cout << " > Escolha uma opcao: ";

    cin >> option;

    return option;
}


void operacoesBalcao() {
    int option = 1, numberOrder;

    do {
        if (option == 1 || option == 2 || option == 3) {
            // Imprime apenas o numero e nome do cliente
            // de todos os pedidos na fila de pedidos
            queueOrders.showOrders();

            cout << "Selecione um pedido para gerencia-lo (Nº): ";
            cin >> number;

        }

        cout << "\n============= GERENCIAR PEDIDO =============" << endl;
        queueOrders.search(numberOrder);
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Adicionar Novo Pedido  [3] Buscar Pedido |" << endl;
        cout << "| [2] Remover Pedido         [0] Cancelar      |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
        cin >> option;
        
        // Se escolheu 1, 2 ou 3, usuario volta para selecionar um pedido da fila
        // Se escolheu 0, 0 usuario volta para o menu de gerenciar pedido
        switch (option) {
            // Adicionar Novo Pedido
            case 1:
                cadastrarPedido();
                break;
            case 2:
                removerPedido();
                break;
            case 3:
                // Buscar Pedido
                break;
            case 0:
                cout << "\nOperacao cancelada." << endl;
                break;
            default:
                cout << "\n # ERRO: Opcao invalida!" << endl;
                break;
        }
    } while (option != 0);

    return void;

}


void cadastrarPedido() {
    vector<string> items;
    string client;

    cout << "\n============= NOVO PEDIDO =============" << endl;
    cout << " > Nome Cliente: ";
    cin >> ws;
    getline(cin, client);

    int optionCadastrar;
    do {
        cout << "\n============= CADASTRAR PEDIDO =================" << endl;
        cout << "| [1] Cachorro Quente         R$ 8.00          |" << endl;
        cout << "| [2] Batata Frita            R$ 6.00          |" << endl;
        cout << "| [3] Hamburguer              R$ 20.00         |" << endl;
        cout << "| [4] Pizza                   R$ 46.00         |" << endl;
        cout << "| [5] Coca Zero               R$ 12.00         |" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "| [10] Finalizar Pedido         [0] Cancelar   |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionCadastrar;

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

            case 10: {
                if (items.empty()) {
                    cout << "\n # ERRO: Adicione pelo menos um item ao pedido!" << endl;
                } else {
                    Order order(client, items);

                    queueOrders.enqueue(order);
                    listOrders.insertEnd(order);

                    cout << "\nPedido cadastrado com sucesso!" << endl;

                    optionCadastrar = 0;
                }
                break;
            }

            case 0:
                cout << "\nCadastro cancelado." << endl;
                break;

            default:
                cout << "\n # ERRO: Opcao invalida!" << endl;
                break;
        }

    } while (optionCadastrar != 0);
}


void removerPedido() {
    int optionRemove;
    do {
        cout << "\n=============== REMOVER PEDIDO ===============" << endl;
        cout << " # Deseja confirmar a remocao do pedido?" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Confirmar Acao             [0] Cancelar  |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        int option;
        cin >> option;

        switch (option) {
            case 1:
                queueOrders.dequeue();
                listOrders.removeOrder(number);
                cout << "\nPedido deletado com sucesso!" << endl;
                break;

            case 0:
                cout << "\nOperacao cancelada." << endl;
                break;

            default:
                cout << "\n # ERRO: Opcao invalida!" << endl;
                break;
        }
    } while (option != 0);
}


void adicionarItem() {
    // tenho que manipular o pedido selecionado, então preciso do número do pedido
    int numberOrder;
    cout << "\nInforme o numero do pedido para adicionar item: ";
    cin >> numberOrder;

    // dessa forma, consigo acessar o pedido selecionado e acessar um item a ele
    // mas devo fazer uma busca na lista de pedidos para encontrar o pedido correto e adicionar o item a ele
    // essa função tem que me retornar o objeto pedido que selecionei, remove-lo da queue e aguardar para adicionar o objeto pedido novo

    

    int optionAddItem;
    do {
        cout << "\n========= ADICIONAR ITEM AO PEDIDO =============" << endl;
        cout << "| [1] Cachorro Quente         R$ 8.00          |" << endl;
        cout << "| [2] Batata Frita            R$ 6.00          |" << endl;
        cout << "| [3] Hamburguer              R$ 20.00         |" << endl;
        cout << "| [4] Pizza                   R$ 46.00         |" << endl;
        cout << "| [5] Coca Zero               R$ 12.00         |" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "| [10] Finalizar Pedido         [0] Cancelar   |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionAddItem;

        switch (optionAddItem) {

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

            case 10: {
                if (items.empty()) {
                    cout << "\n # ERRO: Adicione pelo menos um item ao pedido!" << endl;
                } else {
                    Order order(client, items);

                    queueOrders.enqueue(order);
                    listOrders.insertEnd(order);

                    cout << "\nPedido cadastrado com sucesso!" << endl;

                    optionAddItem = 0;
                }
                break;
            }

            case 0:
                cout << "\nCadastro cancelado." << endl;
                break;

            default:
                cout << "\n # ERRO: Opcao invalida!" << endl;
                break;
        }

    } while (optionAddItem != 0);
}







void exibirHistoricoPedidos() {
    int optionHistorico;
    int historicIndex = 1;

    do {
        cout << "\n============= HISTORICO DE PEDIDOS =============" << endl;

        listOrders.search(historicIndex);

        cout << "------------------------------------------------" << endl;
        cout << "| [1] Anterior   [0] Voltar   [2] Proximo     |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";

        cin >> optionHistorico;

        switch (optionHistorico) {

            case 1:
                listOrders.previousOrder(historicIndex);
                break;

            case 2:
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
}
