#include <iostream>
#include <cstdlib>
#include "rlutil.h"
#include "Menu.h"

using namespace std;

void mostrarMenu() {
    rlutil::setColor(rlutil::CYAN);
    for (int i = 20; i <= 60; i++) {
        rlutil::locate(i, 5); cout << "-";
        rlutil::locate(i, 13); cout << "-";
    }
    for (int j = 5; j <= 13; j++) {
        rlutil::locate(20, j); cout << "|";
        rlutil::locate(60, j); cout << "|";
    }
    rlutil::setColor(rlutil::WHITE);

    rlutil::locate(36, 7);
    cout << "GAGALAGA";

    rlutil::locate(25, 9);
    cout << "1. Jugar / Aventura";
    rlutil::locate(25, 10);
    cout << "2. Manual / Creditos";
    rlutil::locate(25, 11);
    cout << "0. Salir";

    rlutil::setColor(rlutil::GREY);
}

void inicializarEstrellas(int vX[], int vY[], int cantidad, int anchoMax, int altoMax) {
    for (int i = 0; i < cantidad; i++) {
        vX[i] = (rand() % anchoMax) + 1;
        vY[i] = (rand() % altoMax) + 1;
    }
}

void actualizarYMostrarEstrellas(int vX[], int vY[], int cantidad, int anchoMax, int altoMax) {
    for (int i = 0; i < cantidad; i++) {
        rlutil::locate(vX[i], vY[i]);
        cout << " ";
    }

    for (int i = 0; i < cantidad; i++) {
        vY[i]++;
        if (vY[i] > altoMax) {
            vY[i] = 1;
            vX[i] = (rand() % anchoMax) + 1;
        }
    }

    rlutil::setColor(rlutil::WHITE);
    for (int i = 0; i < cantidad; i++) {
        rlutil::locate(vX[i], vY[i]);
        cout << ".";
    }
    rlutil::setColor(rlutil::GREY);
}
