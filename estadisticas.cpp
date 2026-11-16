#include <iostream>
#include "rlutil.h"
#include "estadisticas.h"

using namespace std;

void mostrarEstadisticas(int puntajeFinal) {
    rlutil::cls();
    cout << "========================================" << endl;
    cout << "          ESTADISTICAS DE LA PARTIDA    " << endl;
    cout << "========================================" << endl;
    cout << "Puntaje final obtenido: " << puntajeFinal << endl;
    cout << "--------------------------------========" << endl;
    cout << "Presione cualquier tecla para volver...";
    rlutil::anykey();
}
