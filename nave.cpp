#include <iostream>
#include "rlutil.h"

using namespace std;

int main() {
    // Ocultar el cursor para mejorar la estética visual en la consola
    rlutil::hidecursor();

    // Posición inicial de la nave en la pantalla (eje X e Y)
    int naveX = 40;
    int naveY = 22;

    // Control de proyectiles usando arreglos paralelos (máximo 5 balas en simultáneo)
    const int MAX_BALAS = 5;
    int balasX[MAX_BALAS];
    int balasY[MAX_BALAS];
    bool balasActivas[MAX_BALAS];

    // Inicializamos todas las balas como inactivas al arrancar
    for(int i = 0; i < MAX_BALAS; i++) {
        balasActivas[i] = false;
    }

    bool jugando = true;

    // Bucle principal del juego
    while(jugando) {
        // Limpiamos la pantalla en cada fotograma (frame)
        rlutil::cls();

        // 1. DIBUJAR LA NAVE
        rlutil::locate(naveX, naveY);
        cout << "/^\\"; // Representación sencilla de la nave

        // 2. ACTUALIZAR Y DIBUJAR LAS BALAS
        for(int i = 0; i < MAX_BALAS; i++) {
            if(balasActivas[i]) {
                // La bala asciende restando en el eje Y
                balasY[i]--;

                // Si la bala llega al borde superior de la pantalla, se desactiva
                if(balasY[i] < 1) {
                    balasActivas[i] = false;
                } else {
                    // Dibujar la bala en su nueva posición
                    rlutil::locate(balasX[i], balasY[i]);
                    cout << "|";
                }
            }
        }

        // 3. CAPTURAR ENTRADA DE TECLADO (No bloqueante)
        if(rlutil::kbhit()) {
            int tecla = rlutil::getkey();

            // Movimiento a la izquierda (flecha izquierda o tecla 'a' / 'A')
            if((tecla == rlutil::KEY_LEFT || tecla == 'a' || tecla == 'A') && naveX > 2) {
                naveX -= 2; // Movemos de a 2 espacios para mayor fluidez
            }
            // Movimiento a la derecha (flecha derecha o tecla 'd' / 'D')
            else if((tecla == rlutil::KEY_RIGHT || tecla == 'd' || tecla == 'D') && naveX < 75) {
                naveX += 2;
            }
            // Disparar con la barra espaciadora (Código ASCII 32)
            else if(tecla == 32) {
                // Buscamos un casillero libre en el arreglo de balas
                for(int i = 0; i < MAX_BALAS; i++) {
                    if(!balasActivas[i]) {
                        balasActivas[i] = true;
                        balasX[i] = naveX + 1; // Centrado respecto a la nave ("/^\")
                        balasY[i] = naveY - 1; // Sale justo arriba de la nave
                        break; // Salimos del bucle una vez asignada la bala
                    }
                }
            }
            // Salir del juego presionando la tecla ESC
            else if(tecla == rlutil::KEY_ESCAPE) {
                jugando = false;
            }
        }

        // 4. CONTROL DE VELOCIDAD (Pausa en milisegundos para regular los fotogramas)
        rlutil::msleep(40);
    }

    // Restaurar el cursor al salir de la aplicación
    rlutil::showcursor();
    return 0;
}
