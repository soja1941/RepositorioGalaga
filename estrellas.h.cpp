#include <iostream>
#include <cstdlib>
#include <ctime>
#include "rlutil.h"

using namespace std;

// Funciones integradas temporalmente para la prueba
void inicializarEstrellas(int vX[], int vY[], int cantidad, int anchoMax, int altoMax) {
    for (int i = 0; i < cantidad; i++) {
        vX[i] = (rand() % anchoMax) + 1;
        vY[i] = (rand() % altoMax) + 1;
    }
}

void actualizarYMostrarEstrellas(int vX[], int vY[], int cantidad, int anchoMax, int altoMax) {
    // 1. Borrar estrellas anteriores
    for (int i = 0; i < cantidad; i++) {
        rlutil::locate(vX[i], vY[i]);
        cout << " ";
    }

    // 2. Mover hacia abajo
    for (int i = 0; i < cantidad; i++) {
        vY[i]++;
        if (vY[i] > altoMax) {
            vY[i] = 1;
            vX[i] = (rand() % anchoMax) + 1;
        }
    }

    // 3. Dibujar nuevas posiciones
    rlutil::setColor(rlutil::WHITE);
    for (int i = 0; i < cantidad; i++) {
        rlutil::locate(vX[i], vY[i]);
        cout << ".";
    }
    rlutil::setColor(rlutil::GREY);
}

int main() {
    rlutil::hidecursor();
    srand(time(NULL));

    const int CANT_ESTRELLAS = 25;
    int vecX[CANT_ESTRELLAS];
    int vecY[CANT_ESTRELLAS];

    int anchoPantalla = 80;
    int altoPantalla = 25;

    inicializarEstrellas(vecX, vecY, CANT_ESTRELLAS, anchoPantalla, altoPantalla);

    int contadorFrames = 0;
    while (contadorFrames < 200) {
        actualizarYMostrarEstrellas(vecX, vecY, CANT_ESTRELLAS, anchoPantalla, altoPantalla);

        rlutil::locate(35, 12);
        cout << "INICIATIVA SANCOR SEGUROS";

        rlutil::msleep(80);
        contadorFrames++;
    }

    rlutil::showcursor();
    return 0;
}
