#ifndef LISTAINVENTARIO_HPP
#define LISTAINVENTARIO_HPP

#include <iostream>
#include <string>
#include <cmath>
#include "NoHash.hpp"

using namespace std;

class ListaInventario {
private:
    NoHash** tabela;
    int capacidade;
    int tamanho;
    const float FATOR_CARGA_LIMITE = 0.75;
    
    int funcaoHash(string chave) {
        unsigned long hash = 0;
        for (char c : chave) {
            hash = (hash * 31 + c) % capacidade;
        }
        return hash;
    }

    bool ehPrimo(int n) {
        if (n <= 1) return false;
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int proximoPrimo(int n) {
        while (!ehPrimo(n)) n++;
        return n;
    }

    void inserirItemExistente(Item* item) {
        int indice = funcaoHash(item->chave);
        NoHash* novoNo = new NoHash(item);
        novoNo->proximo = tabela[indice];
        tabela[indice] = novoNo;
        tamanho++;
    }

    void redimensionar() {
        cout << "\n Carga Atingida!" << "\n";
        int capAntiga = capacidade;
        NoHash** tabAntiga = tabela;

        capacidade = proximoPrimo(capacidade * 2);
        tabela = new NoHash*[capacidade];
        tamanho = 0;

        for (int i = 0; i < capacidade; i++) tabela[i] = nullptr;

        for (int i = 0; i < capAntiga; i++) {
            NoHash* atual = tabAntiga[i];
            while (atual != nullptr) {
                NoHash* prox = atual->proximo;
                inserirItemExistente(atual->item); 
                delete atual; 
                atual = prox;
            }
        }
        delete[] tabAntiga;
        cout << "Nova Capacidade" << capacidade << endl;
    }

public:
    ListaInventario(int capInicial = 5) {
        capacidade = proximoPrimo(capInicial);
        tamanho = 0;
        tabela = new NoHash*[capacidade];
        for (int i = 0; i < capacidade; i++) tabela[i] = nullptr;
    }

    ~ListaInventario() {
        for (int i = 0; i < capacidade; i++) {
            NoHash* atual = tabela[i];
            while (atual != nullptr) {
                NoHash* temp = atual;
                atual = atual->proximo;
                delete temp->item;
                delete temp;       
            }
        }
        delete[] tabela;
    }

    void inserir(string chave, string nome, string cat, string loc, int qtd, string cond) {
        if (buscar(chave) != nullptr) {
            cout << "Chave: " << chave << " ja existe." << endl;
            return;
        }
        if ((float)tamanho / capacidade >= FATOR_CARGA_LIMITE) {
            redimensionar();
        }

        int indice = funcaoHash(chave);
        Item* novoItem = new Item(chave, nome, cat, loc, qtd, cond);
        NoHash* novoNo = new NoHash(novoItem);

        novoNo->proximo = tabela[indice];
        tabela[indice] = novoNo;
        tamanho++;
        cout << "Item '" << nome << "' cadastrado!" << "\n";
    }

    Item* buscar(string chave) {
        int indice = funcaoHash(chave);
        NoHash* atual = tabela[indice];
        while (atual != nullptr) {
            if (atual->item->chave == chave) return atual->item;
            atual = atual->proximo;
        }
        return nullptr;
    }

    void remover(string chave) {
        int indice = funcaoHash(chave);
        NoHash* atual = tabela[indice];
        NoHash* anterior = nullptr;

        while (atual != nullptr) {
            if (atual->item->chave == chave) {
                if (anterior == nullptr) tabela[indice] = atual->proximo;
                else anterior->proximo = atual->proximo;

                cout << "Item '" << atual->item->nome << "' removido." << "\n";
                delete atual->item;
                delete atual;
                tamanho--;
                return;
            }
            anterior = atual;
            atual = atual->proximo;
        }
        cout << "Item nao encontrado." << "\n";
    }

    void listarPorCategoria(string categoriaAlvo) {
        bool encontrou = false;
        cout << "\n--- Categoria: " << categoriaAlvo << " ---" << "\n";
        for (int i = 0; i < capacidade; i++) {
            NoHash* atual = tabela[i];
            while (atual != nullptr) {
                if (atual->item->categoria == categoriaAlvo) {
                    atual->item->ExibirDetalhes();
                    encontrou = true;
                }
                atual = atual->proximo;
            }
        }
        if (!encontrou) cout << "Nenhum item encontrado." << "\n";
    }

    void solicitarItem(string chave, Usuario solicitante) {
        Item* item = buscar(chave);
        if (item == nullptr) {
            cout << "Item nao encontrado." << "\n";
            return;
        }

        cout << "\nProcessando solicitacao de: " << solicitante.getNome() << "..." << "\n";

        if (item->quantidade > 0) {
            if (!item->fila.vazia()) {
                Usuario* proximo = item->fila.proximoDaFila();
                if (proximo->getMatricula() == solicitante.getMatricula()) {
                    item->quantidade--;
                    item->fila.sair();
                    cout << ">> SUCESSO! Item retirado por " << solicitante.getNome() << " (estava na fila)." << "\n";
                } 
                else {
                    cout << ">> ATENCAO: Ha pessoas na fila. Voce entrou no fim da fila." << "\n";
                    item->fila.entrar(solicitante);
                }
            } 
            else {
                item->quantidade--;
                cout << ">> SUCESSO! Item retirado por " << solicitante.getNome() << "." << "\n";
            }
        } else {
            cout << ">> ESTOQUE ZERADO. " << solicitante.getNome() << " entrou na fila de espera." << endl;
            item->fila.entrar(solicitante);
        }
        cout << "Estoque restante: " << item->quantidade << "\n";
    }
    
    void debugStatus() {
        cout << "Capacidade: " << capacidade << " | Itens: " << tamanho << "\n";
    }
};

#endif