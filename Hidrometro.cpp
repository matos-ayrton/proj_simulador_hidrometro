#include "Hidrometro.hpp"
#include <iostream>
#include <chrono> 
#include <thread>
#include <unistd.h>

Hidrometro::Hidrometro(const std::string &arquivo_config) : configuracao(arquivo_config), relogio(configuracao.getVazao(), display) {};

void Hidrometro::iniciarSimulacao(double duracao_segundos, double intervalo_atualizacao_segundos)
{
    double tempo_atual = 0;

    while(tempo_atual < duracao_segundos)
    {
        relogio.simular_passagem_tempo(intervalo_atualizacao_segundos);
        display.mostrarVolume();
        tempo_atual += intervalo_atualizacao_segundos;

        std::cout << "Aguardando " << intervalo_atualizacao_segundos << " segundos" << std::endl;

        sleep(static_cast<unsigned int>(intervalo_atualizacao_segundos));
    }
}