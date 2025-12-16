#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <random>

class Usuario {
private:
    std::string nome;
    std::string matricula;
    bool isDocente;
    

    static std::mt19937 randomEngine;

    std::string sortearMatricula();
    std::string sortearNome();
    bool decidirFuncao();

public:
    Usuario(); 
    Usuario(std::string n, std::string m, bool d); 

    std::string getNome();
    std::string getMatricula();
    std::string getFuncao();
};

#endif