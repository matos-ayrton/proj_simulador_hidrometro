#include "Hidrometro.hpp"

int main() {
    // Certifique-se de que o arquivo config.txt está no mesmo diretório
    // da pasta onde você executa o programa.
    Hidrometro meuHidrometro("config.txt");
    
    // Inicia a simulação.
    // Primeiro parâmetro: duração total da simulação em segundos (por exemplo, 35 minutos).
    // Segundo parâmetro: intervalo de atualização do display em segundos.
    meuHidrometro.iniciarSimulacao(60, 1); 

    return 0;
}