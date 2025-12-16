#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <string>
#include <random>
#include <vector>

using namespace std;

class Usuario {
public:
    static mt19937 random; 

    string nome;
    string matricula;
    bool isDocente;

    Usuario() {
        this->nome = SortearNome();
        this->matricula = SortearMatricula();
        this->isDocente = DecidirFuncao();
    }

    Usuario(string n, string m, bool d) {
        this->nome = n;
        this->matricula = m;
        this->isDocente = d;
    }

    string SortearMatricula() {
        string matriculaAtual = "";
        uniform_int_distribution<int> dist(0, 9);
        for(int i = 0; i < 7; i++){
            matriculaAtual += to_string(dist(random));
        }
        return matriculaAtual;
    }

    string SortearNome() {
        vector<string> nomes = {
            "Dante", 
            "Mikael", 
            "Marko", 
            "Lucas", 
            "Leandro", 
            "Leonardo"
        };
        uniform_int_distribution<int> dist(0, nomes.size() - 1);
        return nomes[dist(random)]; 
    }
    string getNome() { 
        return this->nome; 
    }

    string getMatricula() { 
        return this->matricula; 
    }
    
    string getFuncao() {
        return isDocente ? "Docente" : "Aluno";
    }

    bool DecidirFuncao() {
        uniform_int_distribution<int> dist(0, 1);
        return dist(random) >= 1;
    }
};

#endif