#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace chrono;
void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int sleep(int mill) {
    using namespace this_thread;

    sleep_for(milliseconds(mill));
    return mill;
}

struct variaveisGerais{
    const float gTerrestre{9.80665f};
    string continuar;
    float altMaca{};
    float velocidade{}; // m/s
    float dt{0.0f}; //delta time
    int soltar;
};

int main() {
    variaveisGerais var;

    clear();
    while (true) {
        cout << "Deseja soltar a maça? (0 = nao, 1 = sim): ";
        cin >> var.soltar;

        if (var.soltar > 1 || var.soltar < 0) {
            cout << "Valor invalido!!\n";
            sleep(3000);
            clear();
            continue;
        } else {
            cout << "Informe a altura aproximada em que a maça esta: ";
            cin >> var.altMaca;

            var.velocidade = 0.0;
            double tempoSimulado(0.0);

            auto instanteAnterior = steady_clock::now();

            cout << fixed << setprecision(3);
            while (var.altMaca > 0) {
                auto instanteAtual = steady_clock::now();

                var.dt = duration<double>(
                    instanteAtual - instanteAnterior
                ).count();

                instanteAnterior = instanteAtual;

                if (var.dt > 0.05) {
                    var.dt = 0.05;
                } 

                double distanciaPercorrida = var.velocidade * var.dt
                + 0.5 * var.gTerrestre
                * var.dt
                * var.dt;

                var.altMaca -= distanciaPercorrida;
                var.velocidade += var.gTerrestre * var.dt;

                tempoSimulado += var.dt;

                if (var.altMaca < 0) {
                    var.altMaca = 0;
                }

                cout << "|---------------------------|\n";
                cout << "|Altura:     \t" << var.altMaca << " m     |\n"
                <<  "|Velocidade:\t" << var.velocidade << " m/s  |\n"
                << "|dt:          \t" << var.dt << " s/n   |\n";
            }
            cout << "\nA maça chegou ao chao. \n";
            cout << "Tempo de queda: " << tempoSimulado << " segundos\n";

            cout << "Voce deseja fazer outra simulaçao? (sim, nao): ";
            cin >> var.continuar;

            if (var.continuar == "sim" || var.continuar == "s") {
                clear();
                continue;
            } else {
                clear();
                return 0;
            }
        }
    }
}