#ifndef FILAESPERA_HPP
#define FILAESPERA_HPP

#include <iostream>
#include "NoFila.hpp"

using namespace std;

class FilaEspera {
private:
    NoFila* inicio;
    NoFila* fim;

public:
    FilaEspera() {
        inicio = nullptr;
        fim = nullptr;
    }

    ~FilaEspera() {
        while (inicio != nullptr) {
            sair();
        }
    }

    bool vazia() {
        return (inicio == nullptr);
    }

    void entrar(Usuario u) {
        NoFila* novo = new NoFila(u);
        
        if (vazia()) {
            inicio = novo;
            fim = novo;
        } else {
            fim->proximo = novo;
            fim = novo;
        }
        cout << " >> Usuario na fila: " << u.getNome() << " (" << u.getMatricula() << ")" << endl;
    }

    void sair() {
        if (!vazia()) {
            NoFila* temp = inicio;
            inicio = inicio->proximo;
            if (inicio == nullptr) {
                fim = nullptr;
            }
            delete temp;
        }
    }

    Usuario* proximoDaFila() {
        if (!vazia()){
            return &inicio->user;
        }  
        return nullptr;
    }

    void imprimirFila() {
        if (vazia()) {
            cout << " Fila Vazia" << "\n";
            return;
        }
        NoFila* atual = inicio;
        cout << "Em Espera: ";
        while (atual != nullptr) {
            cout << "[" << atual->user.getNome() << " - " << atual->user.getFuncao() << "-> ";
            atual = atual->proximo;
        }
        cout << "Fim" << "\n";
    }
};

#endif