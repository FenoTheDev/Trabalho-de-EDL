#include "Usuario.hpp"
#include <vector>
#include <iostream>

std::mt19937 Usuario::randomEngine(std::random_device{}());

Usuario::Usuario() {
    this->nome = sortearNome();
    this->matricula = sortearMatricula();
    this->isDocente = decidirFuncao();
}

Usuario::Usuario(std::string n, std::string m, bool d) {
    this->nome = n;
    this->matricula = m;
    this->isDocente = d;
}

std::string Usuario::sortearMatricula() {
    std::string matriculaAtual = "";
    std::uniform_int_distribution<int> dist(0, 9);
    for(int i = 0; i < 7; i++){
        matriculaAtual += std::to_string(dist(randomEngine));
    }
    return matriculaAtual;
}

std::string Usuario::sortearNome() {
    std::vector<std::string> nomes = {
        "Dante", 
        "Mikael", 
        "Marko", 
        "Lucas", 
        "Leandro", 
        "Leonardo"
    };
    std::uniform_int_distribution<int> dist(0, nomes.size() - 1);
    return nomes[dist(randomEngine)];
}

bool Usuario::decidirFuncao() {
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(randomEngine) >= 1;
}

std::string Usuario::getNome() { return this->nome; }
std::string Usuario::getMatricula() { return this->matricula; }

std::string Usuario::getFuncao() {
    return isDocente ? "Docente" : "Aluno";
}