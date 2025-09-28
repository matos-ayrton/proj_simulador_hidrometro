#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "CImg.h"
#include <string>
using namespace cimg_library;
class Display
{
public:
    Display();
    ~Display();
    void adicionarVolume(double litros);
    void mostrarVolume();
    double getVolumeTotalLitros() const;

    void setTitulo(const std::string& titulo);
    void setScale(double s);                     
    void setPosition(int x, int y);
    
private:
    CImg<unsigned char> imagem_hidrometro_base;
    CImgDisplay janela_display;
    double volume_total_litros;
    void atualizarDisplayGrafico();

    double ui_scale = 1.0; 
};
#endif