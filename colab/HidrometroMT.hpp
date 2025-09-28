#pragma once
#include <string>
#include <atomic>
#include <thread>
#include <filesystem>
#include <optional>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>


#include "Configuracao.hpp"
#include "Display.hpp"
#include "Relogio.hpp"


class HidrometroMT {
public:
    // id: 1..5  |  cfgPath: caminho do config_i.txt ou "config.txt"
    HidrometroMT(int id, const std::string& cfgPath)
        : ident(id),
          cfg(cfgPath),
          disp(),
          clk(cfg.getVazao(), disp)     
    {
        disp.setTitulo("Simulador de Hidrometro [S" + std::to_string(ident) + "]");

         disp.setScale(0.60);
         const int dx = 300, dy = 80;
         disp.setPosition(20 + dx*(ident-1), 20 + dy*(ident-1));
    }

    void run(double duracao_s, double passo_s, const std::string& cmdPath) {
        std::thread entrada(&HidrometroMT::watchCommands, this, cmdPath);

        double t = 0.0;
        while (t < duracao_s) {
            clk.simular_passagem_tempo(passo_s);
            disp.mostrarVolume();
            std::this_thread::sleep_for(
                std::chrono::milliseconds(static_cast<int>(passo_s * 1000)));
            t += passo_s;
        }

        stopFlag.store(true);
        if (entrada.joinable()) entrada.join();
    }

private:
    int ident;
    Configuracao cfg;
    Display disp;
    Relogio clk;

    std::atomic<bool> stopFlag{false};
    std::optional<std::filesystem::file_time_type> lastMTime;

    void watchCommands(const std::string& cmdPath) {
        using namespace std::chrono_literals;

        // cria arquivo com exemplos, se não existir
        if (!std::filesystem::exists(cmdPath)) {
            std::ofstream seed(cmdPath);
            seed << "# Comandos do simulador " << ident << "\n";
            seed << "# Exemplos:\n# vazao=2.5\n# vazao_ar=0.1\n";
        }

        while (!stopFlag.load()) {
            try {
                auto cur = std::filesystem::last_write_time(cmdPath);
                if (!lastMTime.has_value() || cur != *lastMTime) {
                    lastMTime = cur;
                    applyCommands(cmdPath);
                }
            } catch (...) {
            }
            std::this_thread::sleep_for(300ms);
        }
    }

    void applyCommands(const std::string& cmdPath) {
        std::ifstream f(cmdPath);
        std::string line;
        while (std::getline(f, line)) {
            if (line.empty() || line[0] == '#') continue;

            auto eq = line.find('=');
            if (eq == std::string::npos) continue;

            std::string key = line.substr(0, eq);
            std::string val = line.substr(eq + 1);

            try {
                double x = std::stod(val);
                if (key == "vazao") {
                    clk.setVazao(x);
                    std::cout << "[S" << ident << "] vazao atualizada p/ "
                              << x << " L/min\n";
                } else if (key == "vazao_ar") {
                    clk.setVazaoAr(x);
                    std::cout << "[S" << ident << "] vazao_ar atualizada p/ "
                              << x << " L/min\n";
                }
            } catch (...) {
                // linha malformada: ignora
            }
        }
    }
};
