#pragma once
#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include <filesystem>
#include "HidrometroMT.hpp"

class SimuladorManager {
public:
    void startAll(
        const std::vector<std::string>& cfgs,
        const std::vector<std::string>& cmdFiles,
        double duracao_s,
        double passo_s
    ) {
        if (cfgs.size() != cmdFiles.size()) {
            std::cerr << "cfgs e cmdFiles com tamanhos diferentes.\n";
            return;
        }
        if (cfgs.empty() || cfgs.size() > 5) {
            std::cerr << "Informe entre 1 e 5 simuladores.\n";
            return;
        }

        int id = 1;
        for (size_t i = 0; i < cfgs.size(); ++i) {
            sims.emplace_back(std::make_unique<HidrometroMT>(id, cfgs[i]));
            threads.emplace_back(&HidrometroMT::run, sims.back().get(), duracao_s, passo_s, cmdFiles[i]);
            std::cout << "Simulador S" << id << " iniciado | cfg=" << cfgs[i]
                      << " | cmds=" << cmdFiles[i] << "\n";
            ++id;
        }
    }

    void waitAll() {
        for (auto& th : threads) if (th.joinable()) th.join();
    }

private:
    std::vector<std::unique_ptr<HidrometroMT>> sims;
    std::vector<std::thread> threads;
};
