#ifndef LISTAINVENTARIO_HPP
#define LISTAINVENTARIO_HPP

#include <string>
#include "NoHash.hpp"
#include "Usuario.hpp"

class ListaInventario {
private:
    NoHash** tabela;
    int capacidade;
    int tamanho;
    const float FATOR_CARGA_LIMITE = 0.75;
    
    int funcaoHash(std::string chave);
    bool ehPrimo(int n);
    int proximoPrimo(int n);
    void inserirItemExistente(Item* item);
    void redimensionar(); // Rehashing

public:
    ListaInventario(int capInicial = 5);
    ~ListaInventario();

    void inserir(std::string chave, std::string nome, std::string cat, std::string loc, int qtd, std::string cond);
    Item* buscar(std::string chave);
    void remover(std::string chave);
    void listarPorCategoria(std::string categoriaAlvo);
    void solicitarItem(std::string chave, Usuario solicitante);
    void debugStatus();
};

#endif