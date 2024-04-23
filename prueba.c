#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int vida;
    int es_tesoro;
    int contador_turnos;
} Tierra;

typedef struct {
    int x;
    int y;
} Coordenadas;

typedef struct {
    Coordenadas coords;
    void (*explotar)(Tierra *tablero, Coordenadas coords);
    Tierra *tierra_debajo;  // Mantener referencia a la Tierra original
} Bomba;

void IniciarTablero(void ****tablero, int **tipos, int n) {
    *tablero = (void ***)malloc(n * sizeof(void **));
    *tipos = (int **)malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; i++) {
        (*tablero)[i] = (void **)malloc(n * sizeof(void *));
        (*tipos)[i] = (int *)malloc(n * sizeof(int));
        
        for (int j = 0; j < n; j++) {
            (*tablero)[i][j] = malloc(sizeof(Tierra));
            (*tipos)[i][j] = 0;  // Tipo Tierra por defecto
            Tierra *tierra = (Tierra *)(*tablero)[i][j];
            tierra->vida = rand() % 3 + 1;
            tierra->es_tesoro = (rand() % 100) < 5 ? 1 : 0;
        }
    }
}

void ColocarBomba(void ***tablero, int **tipos, Bomba bomba) {
    int x = bomba.coords.x - 1;
    int y = bomba.coords.y - 1;
    
    if (tipos[x][y] == 0) {
        tipos[x][y] = 1;  // Tipo Bomba
        bomba.tierra_debajo = tablero[x][y];
        tablero[x][y] = &bomba;
    }
}

void TryExplotar(Tierra **tablero, Coordenadas coords) {
    if (tablero[coords.x - 1][coords.y - 1].contador_turnos == 0) {
        tablero[coords.x - 1][coords.y - 1].es_tesoro = 0;
        tablero[coords.x - 1][coords.y - 1].vida = 0;
        // Llamar a la función de explosión de la bomba
    } else {
        tablero[coords.x - 1][coords.y - 1].contador_turnos--;
    }
}

void MostrarTablero(Tierra **tablero, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tablero[i][j].es_tesoro) {
                printf("* ");
            } else {
                printf("%d ", tablero[i][j].vida);
            }
        }
        printf("\n");
    }
}

void MostrarBombas(Bomba *bombas, int num_bombas) {
    for (int i = 0; i < num_bombas; i++) {
        printf("Turnos para explotar: %d\n", bombas[i].coords.x + bombas[i].coords.y);
        printf("Coordenada: %d %d\n", bombas[i].coords.x, bombas[i].coords.y);
        printf("Forma Explosión: nombre de la función explotar\n");
        printf("Vida de Tierra Debajo: %d\n", bombas[i].coords.x + bombas[i].coords.y);
    }
}

void BorrarBomba(Tierra **tablero, Coordenadas coords) {
    tablero[coords.x - 1][coords.y - 1].vida = rand() % 3 + 1;
    tablero[coords.x - 1][coords.y - 1].es_tesoro = (rand() % 100) < 5 ? 1 : 0;
}

void BorrarTablero(Tierra ***tablero, int n) {
    for (int i = 0; i < n; i++) {
        free((*tablero)[i]);
    }
    free(*tablero);
    *tablero = NULL;
}

void VerTesoros(Tierra **tablero, int n) {
    printf("Tesoros\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tablero[i][j].es_tesoro) {
                printf("* ");
            } else {
                printf("%d ", tablero[i][j].vida);
            }
        }
        printf("\n");
    }
}


void MostrarTablero(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Tierra* tierra = (Tierra*)tablero[i][j];
            if (tierra->vida == 0 && !tierra->es_tesoro) {
                printf("0 ");
            } else if (tierra->es_tesoro) {
                printf("* ");
            } else {
                printf("%d ", tierra->vida);
            }
        }
        printf("\n");
    }
}
