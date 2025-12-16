#ifndef NOFILA_HPP
#define NOFILA_HPP

#include "Usuario.hpp"

class NoFila {
public:
    Usuario user;
    NoFila* proximo;

    NoFila(Usuario u);
};

#endif