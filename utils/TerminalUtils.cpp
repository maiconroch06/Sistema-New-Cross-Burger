#include "../utils/TerminalUtils.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

// Apaga o conteudo do terminaç de acordo com o sistema operacional
void TerminalUtils::clear() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

// Pausa o terminal esperando o botão ENTER ser precionado
void TerminalUtils::pause() {
    #if defined(_WIN32) || defined(_WIN64)
        cout << endl;
        system("pause");
    #else
        cout << "\nPressione ENTER para continuar...";
        // Consome qualquer caractere remanescente no buffer e aguarda o ENTER
        system("read -p '' var");
    #endif
}