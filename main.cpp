#include "Hidrometro.hpp"

int main() {

    Hidrometro meuHidrometro("config.txt");
   
    meuHidrometro.iniciarSimulacao(1000, 1);
    
    return 0;
}