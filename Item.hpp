#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>
#include "FilaEspera.hpp"

using namespace std;

class Item {
public:
    string chave;
    string nome;
    string categoria;
    string localizacao;
    int quantidade;
    string condicao;
    FilaEspera fila; // Objeto da fila
    
    Item(string key, string name, string type, string local, int qnt, string cond){
        chave = key;
        nome = name;
        categoria = type;
        localizacao = local;
        quantidade = qnt;
        condicao = cond;
    }

    void ExibirDetalhes(){
        cout << "===================================="<< "\n";
        cout << "ID: " << chave << " | Nome: " << nome << "\n";
        cout << "Categoria: " << categoria << " | Qtd: " << quantidade << "\n";
        cout << "Local: "<< localizacao << " | Cond: "<< condicao << "\n";
        fila.imprimirFila();
        cout << "===================================="<<"\n";
    }
};

#endif