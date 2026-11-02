#include <iostream>
#include "rlutil.h"
#include <conio.h>

using namespace std;

// Declaraciones de funciones
void actualizarMovimiento(char tecla, int &x_jugador, int x_min, int x_max);
void gestionarDisparos(char tecla, int x_jugador, int y_jugador, int balas_x[], int balas_y[], bool balas_activas[], int max_balas);
void actualizarYMostrarBalas(int balas_x[], int balas_y[], bool balas_activas[], int max_balas, int y_min);
void dibujarJugador(int x, int y);

int main() {
    rlutil::hidecursor();

    const int MAX_BALAS = 5;
    int balas_x[MAX_BALAS] = {0};
    int balas_y[MAX_BALAS] = {0};
    bool balas_activas[MAX_BALAS] = {false};

    int x_jugador = 40;
    int y_jugador = 20;
    int x_min = 2;
    int x_max = 75;

    bool jugando = true;

    while (jugando) {
        // 1. Limpiar pantalla del fotograma anterior
        rlutil::cls();

        // 2. Verificar entrada de teclado de forma no bloqueante utilizando rlutil::kbhit()
        if (kbhit()) {
            char tecla = rlutil::getkey();

            // Opción para salir con ESC (código ASCII 27)
            if (tecla == 27) {
                jugando = false;
            }

            // Movimiento lateral
            actualizarMovimiento(tecla, x_jugador, x_min, x_max);

            // Disparo (Barra espaciadora ' ')
            gestionarDisparos(tecla, x_jugador, y_jugador, balas_x, balas_y, balas_activas, MAX_BALAS);
        }

        // 3. Actualizar la posición de las balas en vuelo (suben en el eje Y)
        actualizarYMostrarBalas(balas_x, balas_y, balas_activas, MAX_BALAS, 2);

        // 4. Dibujar la nave del jugador
        dibujarJugador(x_jugador, y_jugador);

        // 5. Pausa breve para controlar la velocidad del juego (fotogramas)
        rlutil::msleep(40);
    }

    rlutil::showcursor();
    rlutil::cls();
    return 0;
}

// Implementación de funciones

void actualizarMovimiento(char tecla, int &x_jugador, int x_min, int x_max) {
    // Si presiona 'a' o 'A' se mueve a la izquierda respetando el límite
    if ((tecla == 'a' || tecla == 'A') && x_jugador > x_min) {
        x_jugador--;
    }
    // Si presiona 'd' o 'D' se mueve a la derecha respetando el límite
    if ((tecla == 'd' || tecla == 'D') && x_jugador < x_max) {
        x_jugador++;
    }
}

void gestionarDisparos(char tecla, int x_jugador, int y_jugador, int balas_x[], int balas_y[], bool balas_activas[], int max_balas) {
    if (tecla == ' ') { // Barra espaciadora
        // Buscamos un espacio libre en el arreglo estático de balas
        for (int i = 0; i < max_balas; i++) {
            if (!balas_activas[i]) {
                balas_x[i] = x_jugador + 1; // Centrado respecto a la nave ("/^\")
                balas_y[i] = y_jugador - 1; // Sale justo arriba de la nave
                balas_activas[i] = true;
                break; // Encontramos espacio disponible, salimos del ciclo
            }
        }
    }
}

void actualizarYMostrarBalas(int balas_x[], int balas_y[], bool balas_activas[], int max_balas, int y_min) {
    for (int i = 0; i < max_balas; i++) {
        if (balas_activas[i]) {
            // Mover la bala hacia arriba restando en el eje Y
            balas_y[i]--;

            // Si la bala sale del límite superior de la pantalla, se desactiva
            if (balas_y[i] < y_min) {
                balas_activas[i] = false;
            } else {
                // Dibujar la bala en su nueva posición
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
