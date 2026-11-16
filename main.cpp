#include <iostream>
#include <cstdlib>
#include <ctime>
#include "rlutil.h"
#include "Menu.h"

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
                rlutil::cls();
                cout << "=== MODO JUEGO / AVENTURA ===" << endl;
                cout << "Aqui iniciara la partida de GAGALAGA." << endl;
                cout << endl;
                cout << "Presione una tecla para volver al menu.";
                rlutil::anykey();
                break;
            }
            case 2: {
                rlutil::cls();
                cout << "=== MANUAL / CREDITOS ===" << endl;
                cout << "Juego desarrollado para Programacion 1 (UTN FRGP)." << endl;
                cout << endl;
                cout << "Presione una tecla para volver al menu.";
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
