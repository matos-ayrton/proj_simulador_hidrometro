#include "Hidrometro.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <limits>

Hidrometro::Hidrometro(const std::string &arquivo_config) 
    : configuracao(arquivo_config), relogio(configuracao.getVazao(), display) {
}

// Método para a nova thread
void Hidrometro::gerenciarEntradaUsuario() {
    double nova_vazao;
    while (true) {
        std::cout << "\nDigite a nova vazao em L/min: ";
        std::cin >> nova_vazao;
       
        // Verifica se a entrada foi bem sucedida. Se não, limpa o buffer e continua o loop.
        if (std::cin.good()) {
            relogio.setVazao(nova_vazao);
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Entrada invalida. Por favor, digite um numero." << std::endl;
        }
    }
}

void Hidrometro::iniciarSimulacao(double duracao_segundos, double intervalo_atualizacao_segundos)
{
    // A thread agora é um membro da classe para ser gerenciada facilmente.
    std::thread thread_entrada(&Hidrometro::gerenciarEntradaUsuario, this);
    double tempo_atual = 0;
    
    while(tempo_atual < duracao_segundos)
    {
        relogio.simular_passagem_tempo(intervalo_atualizacao_segundos);
        display.mostrarVolume();
        tempo_atual += intervalo_atualizacao_segundos;
        // O 'sleep' para por um tempo, para simular a passagem de tempo real.
        sleep(static_cast<unsigned int>(intervalo_atualizacao_segundos));
    }
   
    // Para finalizar a thread de entrada, vamos "desanexá-la" (detach).
    // Isso permite que ela termine por conta própria sem bloquear o fim do programa principal.
    // **Atenção:** Isso é uma solução simples para este caso, mas requer cuidado em cenários mais complexos.
    thread_entrada.detach();
}