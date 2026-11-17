#include <iostream>
#include <cstdlib>
#include <ctime>
#include "rlutil.h"
#include "Menu.h"
#include "jugador.h"       // <-- Obligatorio para que main reconozca jugarPartida()
#include "estadisticas.h"  // <-- Obligatorio para mostrarEstadisticas()

using namespace std;

int main() {
    rlutil::hidecursor();
    srand(time(NULL));

    const int CANT_ESTRELLAS = 25;
    int vecX[CANT_ESTRELLAS];
    int vecY[CANT_ESTRELLAS];
    int anchoPantalla = 80;
    int altoPantalla = 25;

    inicializarEstrellas(vecX, vecY, CANT_ESTRELLAS, anchoPantalla, altoPantalla);

    int opcion = -1;

    do {
        rlutil::cls();
        mostrarMenu();

        rlutil::locate(25, 15);
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int puntajeFinal = jugarPartida(); // Llama a la lógica del juego y recibe el puntaje[cite: 7]
                mostrarEstadisticas(puntajeFinal);  // Muestra las estadísticas al terminar la partida[cite: 6]
                break;
            }
            case 2: {
                rlutil::cls();
                cout << "========================================" << endl;
                cout << "          CONTROLES DE GAGALAGA         " << endl;
                cout << "========================================" << endl;
                cout << " [A] / [a] -> Moverse a la izquierda    " << endl;
                cout << " [D] / [d] -> Moverse a la derecha      " << endl;
                cout << " [ESPACIO] -> Disparar bala             " << endl;
                cout << " [ESC]     -> Volver al menu principal  " << endl;
                cout << "----------------------------------------" << endl;
                cout << "Presione cualquier tecla para volver...";
                rlutil::anykey();
                break;
            }
            case 0: {
                rlutil::cls();
                cout << "Gracias por jugar GAGALAGA. Saliendo..." << endl;
                rlutil::msleep(1000);
                break;
            }
            default: {
                rlutil::locate(25, 17);
                rlutil::setColor(rlutil::LIGHTRED);
                cout << "Opcion incorrecta. Intente nuevamente.";
                rlutil::setColor(rlutil::GREY);
                rlutil::msleep(1000);
                break;
            }
        }

    } while (opcion != 0);

    rlutil::showcursor();
    return 0;
}
