#ifndef FILAESPERA_HPP
#define FILAESPERA_HPP

#include "NoFila.hpp"
#include "Usuario.hpp"

class FilaEspera {
private:
    NoFila* inicio;
    NoFila* fim;

public:
    FilaEspera();
    ~FilaEspera();

    bool vazia();
    void entrar(Usuario u);
    void sair();
    Usuario* proximoDaFila();
    void imprimirFila();
};

#endif