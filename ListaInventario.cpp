#include "ListaInventario.hpp"
#include <iostream>
#include <cmath>

using namespace std;

ListaInventario::ListaInventario(int capInicial) {
    capacidade = proximoPrimo(capInicial);
    tamanho = 0;
    tabela = new NoHash*[capacidade];
    for (int i = 0; i < capacidade; i++) tabela[i] = nullptr;
}

ListaInventario::~ListaInventario() {
    for (int i = 0; i < capacidade; i++) {
        NoHash* atual = tabela[i];
        while (atual != nullptr) {
            NoHash* temp = atual;
            atual = atual->proximo;
            delete temp->item; // Deleta o item alocado
            delete temp;       // Deleta o nó
        }
    }
    delete[] tabela;
}

int ListaInventario::funcaoHash(string chave) {
    unsigned long hash = 0;
    for (char c : chave) {
        hash = (hash * 31 + c) % capacidade;
    }
    return hash;
}

bool ListaInventario::ehPrimo(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int ListaInventario::proximoPrimo(int n) {
    while (!ehPrimo(n)) n++;
    return n;
}

void ListaInventario::inserirItemExistente(Item* item) {
    int indice = funcaoHash(item->chave);
    NoHash* novoNo = new NoHash(item);
    novoNo->proximo = tabela[indice];
    tabela[indice] = novoNo;
    tamanho++; // Nota: na redimensão, o tamanho total não muda, mas a lógica exige reinserção
}

void ListaInventario::redimensionar() {
    cout << "\n[SISTEMA] Fator de Carga Atingido! Realizando Rehashing..." << endl;
    int capAntiga = capacidade;
    NoHash** tabAntiga = tabela;

    capacidade = proximoPrimo(capacidade * 2);
    tabela = new NoHash*[capacidade];
    // Reinicia tamanho para recontar na inserção
    // (Ou poderia manter tamanho e apenas mover ponteiros, mas aqui recriamos os nós hash)
    int tamanhoAtual = tamanho; 
    tamanho = 0; 

    for (int i = 0; i < capacidade; i++) tabela[i] = nullptr;

    for (int i = 0; i < capAntiga; i++) {
        NoHash* atual = tabAntiga[i];
        while (atual != nullptr) {
            NoHash* prox = atual->proximo;
            // Reinsere o item na nova tabela
            inserirItemExistente(atual->item); 
            delete atual; // Deleta o nó antigo (mas mantivemos o item)
            atual = prox;
        }
    }
    delete[] tabAntiga;
    tamanho = tamanhoAtual; // Restaura contagem correta
    cout << "[SISTEMA] Nova Capacidade: " << capacidade << endl;
}

void ListaInventario::inserir(string chave, string nome, string cat, string loc, int qtd, string cond) {
    if (buscar(chave) != nullptr) {
        cout << "Erro: Chave '" << chave << "' ja existe." << endl;
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
    cout << "Sucesso: Item '" << nome << "' cadastrado!" << endl;
}

Item* ListaInventario::buscar(string chave) {
    int indice = funcaoHash(chave);
    NoHash* atual = tabela[indice];
    while (atual != nullptr) {
        if (atual->item->chave == chave) return atual->item;
        atual = atual->proximo;
    }
    return nullptr;
}

void ListaInventario::remover(string chave) {
    int indice = funcaoHash(chave);
    NoHash* atual = tabela[indice];
    NoHash* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->item->chave == chave) {
            if (anterior == nullptr) tabela[indice] = atual->proximo;
            else anterior->proximo = atual->proximo;

            cout << "Item '" << atual->item->nome << "' removido." << endl;
            delete atual->item;
            delete atual;
            tamanho--;
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    cout << "Erro: Item nao encontrado para remocao." << endl;
}

void ListaInventario::listarPorCategoria(string categoriaAlvo) {
    bool encontrou = false;
    cout << "\n--- Relatorio: Categoria " << categoriaAlvo << " ---" << endl;
    for (int i = 0; i < capacidade; i++) {
        NoHash* atual = tabela[i];
        while (atual != nullptr) {
            if (atual->item->categoria == categoriaAlvo) {
                atual->item->exibirDetalhes();
                encontrou = true;
            }
            atual = atual->proximo;
        }
    }
    if (!encontrou) cout << "Nenhum item encontrado nesta categoria." << endl;
}

void ListaInventario::solicitarItem(string chave, Usuario solicitante) {
    Item* item = buscar(chave);
    if (item == nullptr) {
        cout << "Erro: Item nao encontrado." << endl;
        return;
    }

    cout << "\nProcessando solicitacao de: " << solicitante.getNome() << "..." << endl;


    if (item->quantidade > 0) {
        if (!item->fila.vazia()) {
            Usuario* proximo = item->fila.proximoDaFila();
            if (proximo->getMatricula() == solicitante.getMatricula()) {
                item->quantidade--;
                item->fila.sair();
                cout << ">> SUCESSO! Item retirado por " << solicitante.getNome() << " (estava na fila)." << endl;
            } 
            else {
                cout << ">> ATENCAO: Ha pessoas na fila. Voce entrou no fim da fila." << endl;
                item->fila.entrar(solicitante);
            }
        } 
        else {
            // Fila vazia e tem estoque
            item->quantidade--;
            cout << ">> SUCESSO! Item retirado por " << solicitante.getNome() << "." << endl;
        }
    } else {
        cout << ">> ESTOQUE ZERADO. " << solicitante.getNome() << " entrou na fila de espera." << endl;
        item->fila.entrar(solicitante);
    }
    cout << "Estoque restante: " << item->quantidade << endl;
}

void ListaInventario::debugStatus() {
    cout << "--- Status Hash Table ---" << endl;
    cout << "Capacidade: " << capacidade << endl;
    cout << "Itens Totais: " << tamanho << endl;
    cout << "Fator de Carga: " << (float)tamanho/capacidade << endl;
}