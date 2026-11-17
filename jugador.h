#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

void actualizarMovimiento(char tecla, int &x_jugador, int x_min, int x_max);
void gestionarDisparos(char tecla, int x_jugador, int y_jugador, int balas_x[], int balas_y[], bool balas_activas[], int max_balas);
void actualizarYMostrarBalas(int balas_x[], int balas_y[], bool balas_activas[], int max_balas, int y_min);
void dibujarJugador(int x, int y);

int jugarPartida();

#endif
