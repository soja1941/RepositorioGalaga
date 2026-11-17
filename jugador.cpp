#include <iostream>
#include <cstdlib>
#include <ctime>
#include "rlutil.h"
#include "Menu.h"
#include "jugador.h"
#include "estadisticas.h"

using namespace std;

void actualizarMovimiento(char tecla, int &x_jugador, int x_min, int x_max) {
    if ((tecla == 'a' || tecla == 'A') && x_jugador > x_min) x_jugador--;
    if ((tecla == 'd' || tecla == 'D') && x_jugador < x_max) x_jugador++;
}

void gestionarDisparos(char tecla, int x_jugador, int y_jugador, int balas_x[], int balas_y[], bool balas_activas[], int max_balas) {
    if (tecla == ' ') { // Barra espaciadora para disparar
        for (int i = 0; i < max_balas; i++) {
            if (!balas_activas[i]) { // Busca una bala libre
                balas_x[i] = x_jugador + 1; // Centrada respecto a la nave ("/^\")
                balas_y[i] = y_jugador - 1; // Sale justo arriba de la nave
                balas_activas[i] = true;    // Se activa
                break;
            }
        }
    }
}

void actualizarYMostrarBalas(int balas_x[], int balas_y[], bool balas_activas[], int max_balas, int y_min) {
    for (int i = 0; i < max_balas; i++) {
        if (balas_activas[i]) {
            balas_y[i]--; // La bala sube en la pantalla (resta coordenada Y)
            if (balas_y[i] < y_min) {
                balas_activas[i] = false; // Se desactiva si llega arriba del todo
            } else {
                rlutil::locate(balas_x[i], balas_y[i]);
                rlutil::setColor(rlutil::YELLOW);
                cout << "|"; // Dibuja la bala
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
