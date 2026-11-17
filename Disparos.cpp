#include <iostream>
#include "rlutil.h"
#include "Juego.h"
#include "jugador.h"
#include "enemigos.h"
#include "Menu.h"

using namespace std;

int jugarPartida() {
    rlutil::hidecursor();

    // Configuración de jugador y balas
    const int MAX_BALAS = 5;
    int balas_x[MAX_BALAS] = {0};
    int balas_y[MAX_BALAS] = {0};
    bool balas_activas[MAX_BALAS] = {false};

    int x_jugador = 40;
    int y_jugador = 22;
    int x_min = 2;
    int x_max = 75;
    int puntaje = 0;

    // Configuración de enemigos (3 filas, 6 columnas)
    const int CANT_FILAS = 3;
    const int CANT_COLUMNAS = 6;
    int x_filas[CANT_FILAS] = {10, 20, 5};
    int dir_filas[CANT_FILAS] = {1, -1, 1};
    int y_filas[CANT_FILAS] = {4, 6, 8};

    bool enemigos_vivos[CANT_FILAS][CANT_COLUMNAS];
    for (int f = 0; f < CANT_FILAS; f++) {
        for (int c = 0; c < CANT_COLUMNAS; c++) {
            enemigos_vivos[f][c] = true;
        }
    }

    // Estrellas de fondo usando tu módulo Menu
    const int CANT_ESTRELLAS = 25;
    int vecX[CANT_ESTRELLAS];
    int vecY[CANT_ESTRELLAS];
    inicializarEstrellas(vecX, vecY, CANT_ESTRELLAS, 80, 25);

    bool jugando = true;

    while (jugando) {
        // 1. Limpiar pantalla
        rlutil::cls();

        // 2. Fondo de estrellas
        actualizarYMostrarEstrellas(vecX, vecY, CANT_ESTRELLAS, 80, 25);

        // 3. Entrada de teclado sin kbhit (espera la tecla del usuario para procesar el movimiento)
        int tecla = rlutil::getkey();
        if (tecla == rlutil::KEY_ESCAPE) { // ESC para volver al menú
            jugando = false;
        } else {
            actualizarMovimiento((char)tecla, x_jugador, x_min, x_max);
            gestionarDisparos((char)tecla, x_jugador, y_jugador, balas_x, balas_y, balas_activas, MAX_BALAS);
        }

        // 4. Movimiento autónomo de los enemigos (Rebote)
        for (int f = 0; f < CANT_FILAS; f++) {
            x_filas[f] += dir_filas[f];
            if (x_filas[f] > 35 || x_filas[f] < 2) {
                dir_filas[f] *= -1;
            }
        }

        // 5. Balas y colisiones (llama a jugador.cpp y enemigos.cpp)
        actualizarYMostrarBalas(balas_x, balas_y, balas_activas, MAX_BALAS, 2);
        verificarColisiones(balas_x, balas_y, balas_activas, MAX_BALAS, x_filas, y_filas, enemigos_vivos, CANT_FILAS, CANT_COLUMNAS, puntaje);

        // 6. Dibujar elementos
        dibujarEnemigos(x_filas, y_filas, enemigos_vivos, CANT_FILAS, CANT_COLUMNAS);
        dibujarJugador(x_jugador, y_jugador);

        // Barra inferior
        rlutil::locate(2, 24);
        cout << "Puntaje: " << puntaje << " | Presiona [ESC] para salir";
    }

    return puntaje;
}
