#include "FilaEspera.hpp"
#include <iostream>

using namespace std;

FilaEspera::FilaEspera() {
    inicio = nullptr;
    fim = nullptr;
}

FilaEspera::~FilaEspera() {
    while (inicio != nullptr) {
        sair();
    }
}

bool FilaEspera::vazia() {
    return (inicio == nullptr);
}

void FilaEspera::entrar(Usuario u) {
    NoFila* novo = new NoFila(u);
    
    if (vazia()) {
        inicio = novo;
        fim = novo;
    } else {
        fim->proximo = novo;
        fim = novo;
    }
    cout << " >> Usuario adicionado na fila: " << u.getNome() << endl;
}

void FilaEspera::sair() {
    if (!vazia()) {
        NoFila* temp = inicio;
        inicio = inicio->proximo;
        if (inicio == nullptr) {
            fim = nullptr;
        }
        delete temp;
    }
}

Usuario* FilaEspera::proximoDaFila() {
    if (!vazia()){
        return &inicio->user;
    }  
    return nullptr;
}

void FilaEspera::imprimirFila() {
    if (vazia()) {
        cout << "Fila Vazia" << endl;
        return;
    }
    NoFila* atual = inicio;
    cout << "Em Espera: ";
    while (atual != nullptr) {
        cout << "[" << atual->user.getNome() << "] -> ";
        atual = atual->proximo;
    }
    cout << "Fim" << endl;
}