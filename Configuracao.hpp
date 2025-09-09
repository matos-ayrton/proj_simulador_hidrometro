#ifndef CONFIGURACAO_HPP
#define CONFIGURACAO_HPP

#include <string>
#include <unordered_map>

class Configuracao
{
    public:
        Configuracao(const std::string &arquivo);
        double getVazao() const;
        std::string getBitola() const;

    private:
        std::unordered_map<std::string, std::string> parametros;
};

#endif