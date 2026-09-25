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

struct fisica{
    const float gTerrestre{9.80665f};   //<- gravidade terrestre
    float cArrasto{0.47f};             //<- coeficiente de arrasto,
    float dAr{1.225};                 //<- densidade do ar em Km por metros cubicos,
    float velocidade{};              //<- m/s,
    float dt{0.0f};
    float fArrasto{};              //<- delta time
};

struct maca{
    fisica var;

    float altMaca{};                         //<- metros,
    float mMaca{0.15f};                     //<- massa da maça,
    float rMaca{0.04f};                    //<- raio da maça
    double aMaca{M_PI * (rMaca * rMaca)}; //<- area da maça
    float pMaca{mMaca * var.gTerrestre}; //<- peso da maça
};

int main() {
    string continuar;
    float dAltMaca; // dados da altura da maça usada no fim da execuçao
    fisica var;
    maca mc;
    float dVelocidade{1}; //dados da velocidade usada para verificar velocidade maxima atingida pela maça

    clear();
    while (true) {
        cout << "Informe a altura aproximada em que a maça esta: ";
        cin >> mc.altMaca;

        dAltMaca = mc.altMaca;

        dVelocidade = 0;
        var.velocidade = 0;
        double tempoSimulado(0.0);

        auto instanteAnterior = steady_clock::now();

        cout << fixed << setprecision(3);
        while (mc.altMaca > 0) {
            auto instanteAtual = steady_clock::now();

            var.dt = duration<double>(
                instanteAtual - instanteAnterior
            ).count();

            instanteAnterior = instanteAtual;

            if (var.dt > 0.05) {
                var.dt = 0.05;
            } 

            var.fArrasto = 0.5 * var.cArrasto * var.dAr
            * mc.aMaca * pow(var.velocidade, 2);

            /*força resultante*/ double fResultante = 
            mc.pMaca - var.fArrasto;

            double aceleracao = fResultante / mc.mMaca;

            double distanciaPercorrida = var.velocidade * var.dt
            + 0.5 * aceleracao * pow(var.dt, 2);

            mc.altMaca -= distanciaPercorrida;
            var.velocidade += aceleracao * var.dt;

            //guarda a velocidade maxima
            if (var.velocidade > dVelocidade) {
                dVelocidade = var.velocidade;
            }

            tempoSimulado += var.dt;

            if (mc.altMaca < 0) {
                mc.altMaca = 0;
            } if (mc.altMaca == 0) {
                var.velocidade = 0;
            }
            clear();
            cout << "|----------------------------\n";
            cout << "|Altura:     \t" << mc.altMaca << " m     \n"
            << "|Velocidade:\t" << var.velocidade << " m/s\n"
            << "|dt:          \t" << var.dt << " s/n   \n";
            sleep(16);
        }
        cout << "|___________________________|\n";
        cout << "\nA maça chegou ao chao. \n";
        cout << "Tempo de queda: " << tempoSimulado << " segundos\n";
        cout << "Velocidade de impacto: " << dVelocidade << " m/s\n";
        cout << "Altura inicia de: " << fixed << setprecision(0) << dAltMaca << " metros\n";

        cout << "Voce deseja fazer outra simulaçao? (sim, nao): ";
        cin >> continuar;

        if (continuar == "sim" || continuar == "s") {
            clear();
            continue;
        } else {
            clear();
            return 0;
        }
    }
}