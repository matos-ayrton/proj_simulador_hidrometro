#include "Relogio.hpp"

Relogio::Relogio(double vazao, Display& d) : display(d) {
    vazao_litros_por_segundo = vazao / 60.0;
}

void Relogio::simular_passagem_tempo(double tempo_em_segundos) {
    double volume_passado = vazao_litros_por_segundo * tempo_em_segundos;
    display.adicionarVolume(volume_passado);
}