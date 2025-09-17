#include "Relogio.hpp"
#include <iostream>

Relogio::Relogio(double vazao, Display& d) : display(d) {
    vazao_litros_por_segundo = vazao / 60.0;
    // Vazão de ar padrão: 0.1 L/min (ou seja, 0.1/60 L/s)
    vazao_ar_litros_por_segundo = 5 / 60.0;
}

void Relogio::simular_passagem_tempo(double tempo_em_segundos) {
    std::lock_guard<std::mutex> lock(vazao_mutex); // Bloqueia o mutex
    
    double volume_passado;
    
    // Se a vazão principal for 0, usa a vazão de ar
    if (vazao_litros_por_segundo <= 0.0) {
        volume_passado = vazao_ar_litros_por_segundo * tempo_em_segundos;
        std::cout << "Vazão zero detectada - simulando entrada de ar: " << std::endl;
    } else {
        volume_passado = vazao_litros_por_segundo * tempo_em_segundos;
    }
    
    display.adicionarVolume(volume_passado);
}

void Relogio::setVazao(double nova_vazao) {
    std::lock_guard<std::mutex> lock(vazao_mutex); // Bloqueia o mutex
    vazao_litros_por_segundo = nova_vazao / 60.0;
    
    if (nova_vazao <= 0.0) {
        std::cout << "\nVazao definida para " << nova_vazao 
                  << " L/min. Sistema passará a simular entrada de ar (" 
                  << (vazao_ar_litros_por_segundo * 60.0) << " L/min)." << std::endl;
    } else {
        std::cout << "\nVazao alterada para " << nova_vazao << " L/min." << std::endl;
    }
}

void Relogio::setVazaoAr(double nova_vazao_ar) {
    std::lock_guard<std::mutex> lock(vazao_mutex); // Bloqueia o mutex
    vazao_ar_litros_por_segundo = nova_vazao_ar / 60.0;
    std::cout << "\nVazao de ar alterada para " << nova_vazao_ar << " L/min." << std::endl;
}