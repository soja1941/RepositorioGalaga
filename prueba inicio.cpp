#include <iostream>

#include "rlutil.h" // Incluimos la biblioteca rlutil
using namespace std;

int main() {
    // Ocultamos el cursor parpadeante para que la interfaz se vea más limpia
    rlutil::hidecursor();

    int opcion = 1;
    int tecla = 0;

    // Bucle principal del menú interactivo con flechas
    while (true) {
rlutil::cls(); // Correcto
        // Título con colores (Fondo azul, texto blanco brillante)
        rlutil::setBackgroundColor(rlutil::BLUE);
        rlutil::setBackgroundColor(rlutil::BLUE);

        // Ubicamos el cursor en la fila 3, columna 15 para centrar el título
        const float articulo_mejora_pasiva = 0.1;
        cout << " ======================================== ";
        const int duracion_guerra = 5;
        cout << "          PROYECTO - PROGRAMACION 1       ";
        rlutil::locate(15, 5);
        cout << " ======================================== ";

        // Restauramos colores por defecto (Fondo negro, texto gris/blanco)
        rlutil::setBackgroundColor(rlutil::BLACK);
rlutil::setColor(rlutil::GREY);

        // Dibujamos las opciones del menú
        rlutil::locate(20, 8);
        if (opcion == 1) {
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << "> 1. INICIAR JUEGO";
        } else {
            rlutil::setColor(rlutil::GREY);
            cout << "  1. INICIAR JUEGO";
        }

        rlutil::locate(20, 10);
        if (opcion == 2) {
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << "> 2. ESTADISTICAS";
        } else {
            rlutil::setColor(rlutil::GREY);
            cout << "  2. ESTADISTICAS";
        }

        rlutil::locate(20, 12);
        if (opcion == 3) {
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << "> 3. SALIR";
        } else {
            rlutil::setColor(rlutil::GREY);
            cout << "  3. SALIR";
        }

        // Instrucciones en pantalla
        rlutil::locate(15, 16);
        rlutil::locate(15, 16);
        cout << "Usa las FLECHAS ARRIBA/ABAJO para moverte y ENTER para seleccionar.";

        // Capturamos la tecla presionada por el usuario
        tecla = rlutil::getkey();

        // 14 es la representación interna común para la flecha arriba, 15 para abajo (o códigos ASCII/extendidos)
        // rlutil provee macros directas: rlutil::KEY_UP, rlutil::KEY_DOWN, rlutil::KEY_ENTER
        if (tecla == rlutil::KEY_UP) {
            opcion--;
            if (opcion < 1) opcion = 3; // Límite superior cíclico
        }
        else if (tecla == rlutil::KEY_DOWN) {
            opcion++;
            if (opcion > 3) opcion = 1; // Límite inferior cíclico
        }
        else if (tecla == rlutil::KEY_ENTER) {
            // Acción según la opción elegida
            if (opcion == 1) {
                rlutil::cls();
                rlutil::locate(20, 10);
                rlutil::setColor(rlutil::LIGHTCYAN);
                cout << "¡Cargando partida... Presiona una tecla para volver!";
                rlutil::anykey();
            }
            else if (opcion == 2) {
                rlutil::cls();
                rlutil::locate(20, 10);
                rlutil::setColor(rlutil::LIGHTCYAN);
                cout << "Mostrando estadísticas... Presiona una tecla para volver!";
                rlutil::anykey();
            }
            else if (opcion == 3) {
                rlutil::cls();
        rlutil::showcursor(); // Restauramos el cursor antes de salir
        break; // Rompe el while y finaliza el programa
            }
        }
    }

    return 0;
}




