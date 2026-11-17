#include <iostream>
#include "rlutil.h"
#include "enemigos.h"

using namespace std;

void dibujarEnemigos(int x_filas[], int y_filas[], bool enemigos_vivos[][6], int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (enemigos_vivos[f][c]) {
                int x = x_filas[f] + (c * 4);
                rlutil::locate(x, y_filas[f]);
                if (f == 0) rlutil::setColor(rlutil::LIGHTRED);
                else rlutil::setColor(rlutil::LIGHTCYAN);
                cout << "/^\\";
            }
        }
    }
    rlutil::setColor(rlutil::WHITE);
}

void verificarColisiones(int balas_x[], int balas_y[], bool balas_activas[], int max_balas, int x_filas[], int y_filas[], bool enemigos_vivos[][6], int filas, int columnas, int &puntaje) {
    for (int i = 0; i < max_balas; i++) {
        if (balas_activas[i]) {
            for (int f = 0; f < filas; f++) {
                for (int c = 0; c < columnas; c++) {
                    if (enemigos_vivos[f][c]) {
                        int x_enemigo = x_filas[f] + (c * 4);
                        int y_enemigo = y_filas[f];

                        if (balas_y[i] == y_enemigo && balas_x[i] >= x_enemigo && balas_x[i] <= x_enemigo + 2) {
                            enemigos_vivos[f][c] = false;
                            balas_activas[i] = false;
                            puntaje += 10;
                            break;
                        }
                    }
                }
                if (!balas_activas[i]) break;
            }
        }
    }
}
