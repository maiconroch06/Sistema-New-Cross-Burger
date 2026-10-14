#ifndef MENU_VIEWS_HPP
#define MENU_VIEWS_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MenuViews {
public:
    static void drawHeader(const string& title) {
        cout << "================ " << title << " ================" << endl;
    }

    static void drawCart(const vector<string>& menuNames, const vector<int>& quantatyItems) {
        cout << "=-=-=-=-=-=-=-=  CARRINHO ATUAL  =-=-=-=-=-=-=-=" << endl;
        bool vazio = true;
        for (size_t i = 0; i < menuNames.size(); ++i) {
            if (i < quantatyItems.size() && quantatyItems[i] > 0) {
                cout << "   - " << menuNames[i] << ": " << quantatyItems[i] << endl;
                vazio = false;
            }
        }
        if (vazio) {
            cout << "           (Nenhum item no carrinho)" << endl;
        }
        cout << "=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    }

    static void drawMenu() {
        cout << "| [1] Cachorro Quente         R$ 8.00          |" << endl;
        cout << "| [2] Batata Frita            R$ 6.00          |" << endl;
        cout << "| [3] Hamburguer              R$ 20.00         |" << endl;
        cout << "| [4] Pizza                   R$ 46.00         |" << endl;
        cout << "| [5] Coca Zero               R$ 12.00         |" << endl;
    }

    static void drawMenuCounter() {
        drawHeader("GERENCIAR FILA PEDIDOS");
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Adicionar Novo Pedido  [4] Buscar Pedido |" << endl;
        cout << "| [2] Remover Pedido         [0] Sair          |" << endl;
        cout << "| [3] Gerenciar Pedido                         |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
    }

    static void drawMenuManageOrder() {
        cout << "------------------------------------------------" << endl;
        cout << "| [1] Adicionar Item           [3] Desfazer    |" << endl;
        cout << "| [2] Remover Item             [0] Voltar      |" << endl;
        cout << "================================================" << endl;
        cout << " > Escolha uma opcao: ";
    }
};

#endif