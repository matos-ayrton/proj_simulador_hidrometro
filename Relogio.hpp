#ifndef RELOGIO_HPP
#define RELOGIO_HPP

#include "Display.hpp"

class Relogio
{
    public:
        Relogio(double vazao, Display &d);
        void simular_passagem_tempo(double tempo_seg);

    private:
        double vazao_litros_por_segundo;
        Display &display;
};

#endif