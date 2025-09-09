#include "Configuracao.hpp"
#include <fstream>
#include <iostream>

Configuracao::Configuracao(const std::string &arquivo_config)
{
    std::ifstream arquivo(arquivo_config);
    if(arquivo.is_open()) {
        std::string linha;
        while(getline(arquivo,linha)) {
            size_t pos = linha.find('=');
            if(pos != std::string::npos) {
                std::string chave = linha.substr(0, pos);
                std::string valor = linha.substr(pos + 1);
                parametros[chave] = valor;
            }
        }
        arquivo.close();
    }
    else {
        std::cerr << "Não foi possível abrir o arquivo." << std::endl;
    }
}

double Configuracao::getVazao() const {
    try {
        return std::stod(parametros.at("vazao_l_min"));
    }
    catch(const std::out_of_range&) {
        std::cerr << "Erro: Parametro 'vazao_l_min' nao encontrado." << std::endl;
        return 0.0;
    }
}

std::string Configuracao::getBitola() const {
    try {
        return parametros.at("bitola_polegadas");
    } catch (const std::out_of_range&) {
        return "Nao especificada";
    }
}