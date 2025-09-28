#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "SimuladorManager.hpp"


int main(int argc, char** argv) {
    int n = 2;
    if (argc >= 2) n = std::max(1, std::min(5, std::atoi(argv[1])));

    const double DURACAO_S = 3600.0;    // 1h de simulação (ajuste livre)
    const double PASSO_S   = 1.0;       // atualiza a cada 1s

    std::vector<std::string> cfgs, cmds;
    cfgs.reserve(n); cmds.reserve(n);

    for (int i = 1; i <= n; ++i) {
        // pra cada simulador, permite config específica
        // se não existir, cai no "config.txt" do proprietário (comportamento herdado).
        std::string cfg = "config_" + std::to_string(i) + ".txt";
        if (!std::filesystem::exists(cfg)) cfg = "config.txt";

        std::string cmd = "commands_" + std::to_string(i) + ".txt";

        cfgs.push_back(cfg);
        cmds.push_back(cmd);
    }

    SimuladorManager m;
    m.startAll(cfgs, cmds, DURACAO_S, PASSO_S);
    m.waitAll();

    std::cout << "\nTodos os simuladores finalizaram.\n";
    return 0;
}



