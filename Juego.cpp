#include <iostream>
#include "rlutil.h"
#include <conio.h>

using namespace std;

// Declaraciones de funciones
void actualizarMovimiento(char tecla, int &x_jugador, int x_min, int x_max);
void gestionarDisparos(char tecla, int x_jugador, int y_jugador, int balas_x[], int balas_y[], bool balas_activas[], int max_balas);
void actualizarYMostrarBalas(int balas_x[], int balas_y[], bool balas_activas[], int max_balas, int y_min);
void dibujarJugador(int x, int y);
void dibujarEnemigos(int x_filas[], int y_filas[], bool enemigos_vivos[][6], int filas, int columnas);
void verificarColisiones(int balas_x[], int balas_y[], bool balas_activas[], int max_balas, int x_filas[], int y_filas[], bool enemigos_vivos[][6], int filas, int columnas, int &puntaje);

int main() {
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
    int x_filas[CANT_FILAS] = {10, 20, 5};       //Posiciones X iniciales por fila
    int dir_filas[CANT_FILAS] = {1, -1, 1};       //Direcciones (1: derecha, -1: izquierda)
    int y_filas[CANT_FILAS] = {4, 6, 8};         //Coordenadas Y fijas para cada fila

    // Matriz para controlar qué enemigos siguen vivos (true = vivo, false = destruido)
    bool enemigos_vivos[CANT_FILAS][CANT_COLUMNAS];
    for(int f = 0; f < CANT_FILAS; f++) {
        for(int c = 0; c < CANT_COLUMNAS; c++) {
            enemigos_vivos[f][c] = true;
        }
    }

    bool jugando = true;

    while (jugando) {
        // 1. Limpiar pantalla del fotograma anterior
        rlutil::cls();

        // 2. Entrada de teclado no bloqueante
        if (kbhit()) {
            char tecla = rlutil::getkey();
            if (tecla == 27) { // ESC para salir
                jugando = false;
            }
            actualizarMovimiento(tecla, x_jugador, x_min, x_max);
            gestionarDisparos(tecla, x_jugador, y_jugador, balas_x, balas_y, balas_activas, MAX_BALAS);
        }

        // 3. Actualizar movimiento autónomo de los enemigos (Rebote)
        for (int f = 0; f < CANT_FILAS; f++) {
            x_filas[f] += dir_filas[f];
            if (x_filas[f] > 35 || x_filas[f] < 2) {
                dir_filas[f] *= -1; // Cambia de dirección al chocar con los bordes
            }
        }

        // 4. Actualizar posiciones de las balas
        actualizarYMostrarBalas(balas_x, balas_y, balas_activas, MAX_BALAS, 2);

        // 5. Verificar colisiones entre balas y enemigos
        verificarColisiones(balas_x, balas_y, balas_activas, MAX_BALAS, x_filas, y_filas, enemigos_vivos, CANT_FILAS, CANT_COLUMNAS, puntaje);

        // 6. Dibujar elementos en pantalla
        dibujarEnemigos(x_filas, y_filas, enemigos_vivos, CANT_FILAS, CANT_COLUMNAS);
        dibujarJugador(x_jugador, y_jugador);

        // Mostrar estadísticas en pantalla
        rlutil::locate(2, 24);
        cout << "Puntaje: " << puntaje << " | Presioná [ESC] para salir";

        // 7. Pausa del fotograma
        rlutil::msleep(50);
    }

    rlutil::showcursor();
    rlutil::cls();
    return 0;
}

// --- IMPLEMENTACIÓN DE FUNCIONES ---

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

void dibujarEnemigos(int x_filas[], int y_filas[], bool enemigos_vivos[][6], int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (enemigos_vivos[f][c]) {
                int x = x_filas[f] + (c * 4);
                rlutil::locate(x, y_filas[f]);ya
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
            // Recorremos cada enemigo para ver si coincide con la posición de la bala i
            for (int f = 0; f < filas; f++) {
                for (int c = 0; c < columnas; c++) {
                    if (enemigos_vivos[f][c]) {
                        int x_enemigo = x_filas[f] + (c * 4);
                        int y_enemigo = y_filas[f];

                        // La nave enemiga ocupa desde x_enemigo hasta x_enemigo + 2
                        if (balas_y[i] == y_enemigo && balas_x[i] >= x_enemigo && balas_x[i] <= x_enemigo + 2) {
                            // ¡Impacto detectado!
                            enemigos_vivos[f][c] = false; // Destruimos al enemigo
                            balas_activas[i] = false;     // Desactivamos la bala
                            puntaje += 10;                // Sumamos puntos
                            break; // Salimos del ciclo de enemigos para esta bala
                        }
                    }
                }
                if (!balas_activas[i]) break; // Si la bala ya impactó, pasamos a la siguiente bala
            }
        }
    }
}
