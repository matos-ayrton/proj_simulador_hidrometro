#ifndef RELOGIO_HPP
#define RELOGIO_HPP
#include "Display.hpp"
#include <mutex> // Inclua a biblioteca para o mutex

class Relogio
{
public:
    Relogio(double vazao, Display &d);
    void simular_passagem_tempo(double tempo_seg);
    void setVazao(double nova_vazao); // Método para alterar a vazão
    void setVazaoAr(double nova_vazao_ar); // Método para alterar a vazão de ar

private:
    double vazao_litros_por_segundo;
    double vazao_ar_litros_por_segundo; // Vazão de ar quando vazão principal é 0
    Display &display;
    std::mutex vazao_mutex; // Mutex para proteger a vazão
};

#endif