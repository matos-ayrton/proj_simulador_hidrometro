#include "Display.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

Display::Display() : volume_total_litros(0.0) {
    try {
        // Tenta carregar a imagem base do hidrômetro
        imagem_hidrometro_base.load("hidrometro_imagem.bmp"); // Use o nome correto da sua imagem
    } catch (CImgIOException& e) {
        std::cerr << "Erro ao carregar a imagem 'hidrometro.png': " << e.what() << std::endl;
        exit(1);
    }
    
    // Inicializa a janela de exibição
    janela_display.assign(imagem_hidrometro_base, "Simulador de Hidrometro");
}

Display::~Display() {
    // A CImgDisplay gerencia a janela e os recursos automaticamente
}

void Display::adicionarVolume(double litros) {
    volume_total_litros += litros;
}

void Display::mostrarVolume() {
    atualizarDisplayGrafico();
}

double Display::getVolumeTotalLitros() const {
    return volume_total_litros;
}

void Display::atualizarDisplayGrafico() {
    // Cria uma cópia da imagem original para não desenhar sobre os números antigos
    CImg<unsigned char> imagem_atualizada = imagem_hidrometro_base;
   
    const unsigned char preto[] = {0, 0, 0};
    const unsigned char vermelho[] = {255, 0, 0};
    
    // Calcula os valores
    long long metros_cubicos = floor(volume_total_litros / 1000);
    double decimais_litros = fmod(volume_total_litros, 1000);
    
    // Extrai cada dígito individualmente
    int centenas_litros = static_cast<int>(decimais_litros / 100) % 10;
    int dezenas_litros = static_cast<int>(decimais_litros / 10) % 10;
    int litros_unidade = static_cast<int>(decimais_litros) % 10;
    int decimos_litro = static_cast<int>(decimais_litros * 10) % 10;
    
    // Extrai os 4 dígitos dos metros cúbicos (com padding de zeros)
    int m3_milhares = (metros_cubicos / 1000) % 10;
    int m3_centenas = (metros_cubicos / 100) % 10;
    int m3_dezenas = (metros_cubicos / 10) % 10;
    int m3_unidades = metros_cubicos % 10;
    
    // Define as posições para cada dígito (ajuste conforme sua imagem)
    int tamanho_fonte = 25;
    int espacamento = 30; // Espaçamento entre dígitos
    
    // Posições base para metros cúbicos (preto)
    int x_base_m3 = 450;
    int y_m3 = 345;
    
    // Desenha os 4 dígitos dos metros cúbicos individualmente
    imagem_atualizada.draw_text(
        x_base_m3, y_m3, std::to_string(m3_milhares).c_str(), 
        preto, 0, 1.0f, tamanho_fonte
    );
    imagem_atualizada.draw_text(
        x_base_m3 + espacamento + 5, y_m3, std::to_string(m3_centenas).c_str(), 
        preto, 0, 1.0f, tamanho_fonte
    );
    imagem_atualizada.draw_text(
        x_base_m3 + (espacamento*2)+10, y_m3, std::to_string(m3_dezenas).c_str(), 
        preto, 0, 1.0f, tamanho_fonte
    );
    imagem_atualizada.draw_text(
        x_base_m3 + (espacamento*3) + 20, y_m3, std::to_string(m3_unidades).c_str(), 
        preto, 0, 1.0f, tamanho_fonte
    );
    
    // Posições para centenas e dezenas de litros (vermelho)
    int x_base_litros_cd = 595;
    int y_litros_cd = 345;
    
    imagem_atualizada.draw_text(
        x_base_litros_cd, y_litros_cd, std::to_string(centenas_litros).c_str(), 
        vermelho, 0, 1.0f, tamanho_fonte
    );
    imagem_atualizada.draw_text(
        x_base_litros_cd + espacamento + 5, y_litros_cd, std::to_string(dezenas_litros).c_str(), 
        vermelho, 0, 1.0f, tamanho_fonte
    );
    
    // Posição para unidade de litros (vermelho)
    int x_litros_unidade = 660;
    int y_litros_unidade = 500;
    
    imagem_atualizada.draw_text(
        x_litros_unidade, y_litros_unidade, std::to_string(litros_unidade).c_str(), 
        preto, 0, 1.0f, tamanho_fonte
    );
    
    // Posição para décimos de litro (vermelho)
    int x_decimos = 540;
    int y_decimos = 560;
    
    imagem_atualizada.draw_text(
        x_decimos, y_decimos, std::to_string(decimos_litro).c_str(), 
        preto, 0, 1.0f, tamanho_fonte
    );
    
    // Exibe a imagem atualizada na janela
    janela_display.display(imagem_atualizada);
}