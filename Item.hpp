#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "FilaEspera.hpp"

class Item {
public:
    std::string chave;
    std::string nome;
    std::string categoria;
    std::string localizacao;
    int quantidade;
    std::string condicao;
    FilaEspera fila; 

    Item(std::string key, std::string name, std::string type, std::string local, int qnt, std::string cond);
    
    void exibirDetalhes();
};

#endif