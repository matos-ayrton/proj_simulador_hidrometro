#ifndef HIDROMETRO_HPP
#define HIDROMETRO_HPP

#include <string>
#include "Configuracao.hpp"
#include "Display.hpp"
#include "Relogio.hpp"

class Hidrometro 
{
public:
    Hidrometro(const std::string& arquivo_config);
    void iniciarSimulacao(double duracao_segundos, double intervalo_atualizacao_segundos);

private:
    Configuracao configuracao;
    Display display;
    Relogio relogio;
};

#endif // HIDROMETRO_HPP