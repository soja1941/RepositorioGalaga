#include <iostream>
#include "rlutil.h"

using namespace std;

// Declaración de función para dibujar la formación enemiga
void dibujarFormacionGalaga(int filas, int columnas, int x_inicial, int y_inicial);

int main() {
    // Ocultar el cursor para mejor estética en consola
    rlutil::hidecursor();

    // Título de la prueba
    rlutil::locate(30, 2);
    cout << "--- PRUEBA FORMACION GALAGA ---";

    // Llamada a la función que dibuja la flota enemiga
    // 4 filas, 8 columnas, empezando en la coordenada X=25, Y=6
    dibujarFormacionGalaga(4, 8, 25, 6);

    // Mensaje final y pausa para ver el resultado
    rlutil::locate(22, 18);
    cout << "Presiona cualquier tecla para salir...";
    rlutil::anykey();

    // Restaurar cursor antes de terminar
    rlutil::showcursor();
    rlutil::cls();
    return 0;
}

// Implementación de la función
void dibujarFormacionGalaga(int filas, int columnas, int x_inicial, int y_inicial) {
    // Recorremos filas y columnas usando ciclos exactos (for)
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {

            // Calculamos la posición en pantalla de cada nave separadas por espacios
            int x = x_inicial + (c * 4); // Dejamos 4 espacios de separación horizontal
            int y = y_inicial + (f * 2); // Dejamos 2 líneas de separación vertical

            rlutil::locate(x, y);

            // Opcional: cambiar color según la fila para darle variedad visual
            if (f == 0) {
                rlutil::setColor(rlutil::LIGHTRED);
            } else {
                rlutil::setColor(rlutil::LIGHTCYAN);
            }

            // Dibujamos la nave usando caracteres simples
            cout << "/^\\";
        }
    }
    // Restaurar color por defecto de la consola
    rlutil::setColor(rlutil::WHITE);
}

