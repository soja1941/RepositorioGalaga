#include <iostream>
#include "rlutil.h"

using namespace std;

void dibujarFilaEnemiga(int fila_idx, int columnas, int x_actual, int y_inicial);

int main() {
    rlutil::hidecursor();

    int filas = 3;
    int columnas = 6;
    int y_inicial = 5;

    // 1. Posiciones iniciales independientes para cada fila
    int x_fila0 = 10;
    int x_fila1 = 20;
    int x_fila2 = 5;

    // Direcciones independientes para cada fila (1 = derecha, -1 = izquierda)
    int dir_fila0 = 1;
    int dir_fila1 = -1;
    int dir_fila2 = 1;

    // Bucle principal de animación de prueba
    for (int i = 0; i < 50; i++) {
        rlutil::cls();

        // 2. Dibujar y actualizar la Fila 0
        dibujarFilaEnemiga(0, columnas, x_fila0, y_inicial);
        x_fila0 += dir_fila0;
        if (x_fila0 > 30 || x_fila0 < 5) dir_fila0 *= -1; // Rebote

        // 3. Dibujar y actualizar la Fila 1 (se mueve a otro ritmo o dirección)
        dibujarFilaEnemiga(1, columnas, x_fila1, y_inicial + 2);
        x_fila1 += dir_fila1;
        if (x_fila1 > 35 || x_fila1 < 8) dir_fila1 *= -1;

        // 4. Dibujar y actualizar la Fila 2
        dibujarFilaEnemiga(2, columnas, x_fila2, y_inicial + 4);
        x_fila2 += dir_fila2;
        if (x_fila2 > 25 || x_fila2 < 2) dir_fila2 *= -1;

        // Pausa general del fotograma
        rlutil::msleep(80);
    }

    rlutil::locate(22, 18);
    cout << "Prueba de movimiento independiente finalizada. Presiona una tecla...";
    rlutil::anykey();

    rlutil::showcursor();
    rlutil::cls();
    return 0;
}

// Función simplificada para dibujar una sola fila en una coordenada X específica
void dibujarFilaEnemiga(int fila_idx, int columnas, int x_actual, int y) {
    for (int c = 0; c < columnas; c++) {
        int x = x_actual + (c * 4);
        rlutil::locate(x, y);

        if (fila_idx == 0) {
            rlutil::setColor(rlutil::LIGHTRED);
        } else {
            rlutil::setColor(rlutil::LIGHTCYAN);
        }
        cout << "/^\\";
    }
    rlutil::setColor(rlutil::WHITE);
}
