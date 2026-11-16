#ifndef ENEMIGOS_H_INCLUDED
#define ENEMIGOS_H_INCLUDED

void dibujarEnemigos(int x_filas[], int y_filas[], bool enemigos_vivos[][6], int filas, int columnas);
void verificarColisiones(int balas_x[], int balas_y[], bool balas_activas[], int max_balas, int x_filas[], int y_filas[], bool enemigos_vivos[][6], int filas, int columnas, int &puntaje);

#endif // ENEMIGOS_H_INCLUDED
