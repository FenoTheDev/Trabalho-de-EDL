#include <iostream>
#include <string>
#include "ListaInventario.hpp" 

using namespace std;

mt19937 Usuario::random(random_device{}());

void menu() {
    cout << "\n====Bem Vindo, Professor Leandro======" << "\n";
    cout << "1. Cadastrar Item" << "\n";
    cout << "2. Buscar Item" << "\n";
    cout << "3. Remover Item" << "\n";
    cout << "4. Listar por Categoria" << "\n";
    cout << "5. Solicitar Item (Simular Usuario)" << "\n";
    cout << "6. Status Tabela" << "\n";
    cout << "0. Sair" << "\n";
    cout << "Escolha: ";
}

int main() {
    ListaInventario sistema(5); 
    int opcao;
    string chave, nome, cat, loc, cond;
    int qtd;

    do {
        menu();
        cin >> opcao; 
        cin.ignore(); 

        switch (opcao) {
            case 1:
                cout << "Chave: "; getline(cin, chave);
                cout << "Nome: "; getline(cin, nome);
                cout << "Categoria: "; getline(cin, cat);
                cout << "Local: "; getline(cin, loc);
                cout << "Quantidade: "; cin >> qtd; cin.ignore();
                cout << "Condicao: "; getline(cin, cond);
                sistema.inserir(chave, nome, cat, loc, qtd, cond);
                break;
            case 2:
                cout << "Chave: "; getline(cin, chave);
                {
                    Item* i = sistema.buscar(chave);
                    if (i) i->ExibirDetalhes();
                    else cout << "Nao encontrado." << endl;
                }
                break;
            case 3:
                cout << "Chave: "; getline(cin, chave);
                sistema.remover(chave);
                break;
            case 4:
                cout << "Categoria: "; getline(cin, cat);
                sistema.listarPorCategoria(cat);
                break;
            case 5: {
                cout << "Chave do Item: "; getline(cin, chave);
                Usuario user; 

                cout << "--- Solicitante: ---" << "\n";
                cout << "Nome: " << user.getNome() << "\n";
                cout << "Matricula: " << user.getMatricula() << "\n";
                
                sistema.solicitarItem(chave, user);
                break;
            }
            case 6:
                sistema.debugStatus();
                break;
            case 0:
                cout << "Saindo..." << "\n";
                break;
            default:
                cout << "Opcao invalida." << "\n";
        }
    } 
    while (opcao != 0);
    return 0;
}