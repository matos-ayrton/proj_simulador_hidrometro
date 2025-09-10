#include "Display.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

Display::Display() : volume_total_litros(0.0) {};

void Display::adicionarVolume(double litros)
{
    volume_total_litros += litros;
}

void Display::mostrarVolume() const
{
    long long metros_cubicos = floor(volume_total_litros / 1000);
    double decimais_litros = fmod(volume_total_litros, 1000);
    int centenas_litros = static_cast<int>(decimais_litros / 100) % 10;
    int dezenas_litros = static_cast<int>(decimais_litros / 10) % 10;
    int litros_unidade = static_cast<int>(decimais_litros) % 10;
    int decimos_litro = static_cast<int>(decimais_litros * 10) % 10;

    std::cout << "-- Valores do Hidrometro --"<< std::endl;

    std::cout << "Consumo (m³): " << std::setw(4) << std::setfill('0') << metros_cubicos << std::endl;
    std::cout << "Centenas/Dezenas de litro: " << centenas_litros << " " << dezenas_litros << std::endl;
    std::cout << "Litros: " << litros_unidade << std::endl;
    std::cout << "Decimos de litro: " << decimos_litro << std::endl << std::endl;;
}

double Display::getVolumeTotalLitros() const {
    return volume_total_litros;
}