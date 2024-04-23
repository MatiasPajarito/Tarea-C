#ifndef TABLERO_H
#define TABLERO_H
#include "Bomba.h"

extern int** matriz;
extern void*** tablero;
extern int dimension;
extern int cont_tesoro;

void IniciarTablero(int n);
void PasarTurno();
void ColocarBomba(Bomba* b, int fila, int columna);
void MostrarTablero();
void MostrarBombas();
void VerTesoros();
void BorrarTablero();
#endif