#include "Item.hpp"
#include <iostream>

using namespace std;

Item::Item(string key, string name, string type, string local, int qnt, string cond) {
    chave = key;
    nome = name;
    categoria = type;
    localizacao = local;
    quantidade = qnt;
    condicao = cond;
}

void Item::exibirDetalhes() {
    cout << "===================================="<< endl;
    cout << "ID: " << chave << " | Nome: " << nome << endl;
    cout << "Categoria: " << categoria << " | Qtd: " << quantidade << endl;
    cout << "Local: "<< localizacao << " | Cond: "<< condicao << endl;
    fila.imprimirFila();
    cout << "===================================="<< endl;
}