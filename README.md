# SHA V2 – Modo Multithread (branch do colaborador)

**Branch:** `dev_clara.colaco`  
**Objetivo:** rodar **1–5 simuladores em paralelo**, com **entrada/medição/saída independentes**, sem alterar a lógica do proprietário.

---

## O que foi adicionado
- `colab/main_multithread.cpp` – ponto de entrada multithread.  
- `colab/SimuladorManager.hpp` – gerencia 1..5 instâncias (threads).  
- `colab/HidrometroMT.hpp` – encapsula 1 simulador + “arquivo de comandos” por instância.  
- **Display (mínimas adições):** `setTitulo`, `setScale`, `setPosition` e exibição com escala do frame final.

---

## Como compilar (Windows / g++)
    g++ -std=gnu++17 -O2 -Wall -I. -Icolab ^
      colab/main_multithread.cpp Configuracao.cpp Display.cpp Relogio.cpp Hidrometro.cpp ^
      -lgdi32 -o simulador_mt.exe

(Em uma linha:)
    g++ -std=gnu++17 -O2 -Wall -I. -Icolab colab/main_multithread.cpp Configuracao.cpp Display.cpp Relogio.cpp Hidrometro.cpp -lgdi32 -o simulador_mt.exe

---

## Como executar
    .\simulador_mt.exe N   # N = 1..5

Cada instância abre sua janela: `Simulador de Hidrometro [S1]`, `[S2]`, …

---

## Config por instância (`config_i.txt`)
Formato igual ao `config.txt` do proprietário:
    vazao_l_min=100
    # 30=180   (opcional: aos 30 s muda para 180 L/min)

Mapeamento: S1→`config_1.txt`, S2→`config_2.txt` … (se não existir, usa `config.txt`).

---

## Comandos em tempo real (`commands_i.txt`)
Cada instância monitora **seu** arquivo (salve para aplicar):
    vazao=150      # L/min
    vazao_ar=0.2   # L/min (se aplicável)
    scale=0.6      # fator da janela (opcional)

Ex.: alterar somente S2 → edite `commands_2.txt` e salve.

---

## Janelas (título, tamanho, posição)
- Título por instância (ex.: `[S1]..[S5]`).
- Tamanho: `setScale(0.3..1.0)` (também via `scale=` no `commands_i.txt`).
- Posição: `setPosition(x,y)`; nesta branch uso offsets por id para evitar sobreposição.

---

## O que mudou no código do proprietário
- **Apenas no `Display`**: adição de `setTitulo`, `setScale`, `setPosition` e resize na exibição para suportar escala.
- **Nenhuma** alteração na lógica de `Configuracao`, `Relogio` e `Hidrometro`.

---

## Estrutura (resumo)
    / (raiz)
    ├─ CImg.h
    ├─ Configuracao.*, Display.*, Relogio.*, Hidrometro.*   # proprietário
    ├─ colab/
    │  ├─ main_multithread.cpp
    │  ├─ SimuladorManager.hpp
    │  └─ HidrometroMT.hpp
    └─ config.txt

