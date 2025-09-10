#ifndef DISPLAY_HPP
#define DISPLAY_HPP

class Display
{
    public:
        Display();
        void adicionarVolume(double litros);
        void mostrarVolume() const;
        double getVolumeTotalLitros() const;
    
    private:
        double volume_total_litros;
};

#endif