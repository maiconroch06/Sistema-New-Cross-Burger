#ifndef TERMINAL_UTILS_HPP
#define TERMINAL_UTILS_HPP

class TerminalUtils {
public:
    // Apaga o conteudo do terminaç de acordo com o sistema operacional
    static void clear();

    // Pausa o terminal esperando o botão ENTER ser precionado
    static void pause();
};

#endif