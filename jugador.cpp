#include <iostream>
#include "rlutil.h"
#include "jugador.h"

using namespace std;

void actualizarMovimiento(char tecla, int &x_jugador, int x_min, int x_max) {
    if ((tecla == 'a' || tecla == 'A') && x_jugador > x_min) x_jugador--;
    if ((tecla == 'd' || tecla == 'D') && x_jugador < x_max) x_jugador++;
}

void gestionarDisparos(char tecla, int x_jugador, int y_jugador, int balas_x[], int balas_y[], bool balas_activas[], int max_balas) {
    if (tecla == ' ') {
        for (int i = 0; i < max_balas; i++) {
            if (!balas_activas[i]) {
                balas_x[i] = x_jugador + 1; // Centrado respecto a "/^\"
                balas_y[i] = y_jugador - 1;
                balas_activas[i] = true;
                break;
            }
        }
    }
}

void actualizarYMostrarBalas(int balas_x[], int balas_y[], bool balas_activas[], int max_balas, int y_min) {
    for (int i = 0; i < max_balas; i++) {
        if (balas_activas[i]) {
            balas_y[i]--; // Sube la bala
            if (balas_y[i] < y_min) {
                balas_activas[i] = false;
            } else {
                rlutil::locate(balas_x[i], balas_y[i]);
                rlutil::setColor(rlutil::YELLOW);
                cout << "|";
            }
        }
    }
    rlutil::setColor(rlutil::WHITE);
}

void dibujarJugador(int x, int y) {
    rlutil::locate(x, y);
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "/^\\";
    rlutil::setColor(rlutil::WHITE);
}
