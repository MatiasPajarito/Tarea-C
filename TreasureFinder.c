#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"
extern int cont_tesoro;

int main(int argc, char const *argv[]){
    int var = 1;
    int opcion;
    int fila;
    int columna;
    int bombofica;
    int turno = 1;
    
    printf("¡Bienvenido a TreasureFinder!\n");
    printf("Indique el tamaño del tablero a jugar:\n");
    printf("1. (7x7) 2. (10x10) 3. (12x12)\n");
    srand(time(0));
    printf("Su opcion: \n");
    scanf("%d", &opcion);
    printf("Empezando juego... ¡listo!\n");
    printf("\n");
    printf("Tablero (Turno) %d\n", turno);
    printf("\n");
    if(opcion == 1){
        dimension = 7;
    }
    else if(opcion == 2){
        dimension = 10;
    }
    else if(opcion == 3){
        dimension = 12;
    }
    IniciarTablero(dimension);
    while (cont_tesoro > 0){
        MostrarTablero();
        printf("Seleccione una accion: \n");
        printf("1. (Colocar Bomba) 2. (Mostrar Bombas) 3. (Mostrar Tesoros) 4. (Matar Programa)\n");
        printf("Escoja una opcion: \n");
        scanf("%d", &opcion);
        if(opcion == 1){
            Bomba* bombito = malloc(sizeof(Bomba));
            printf("Indique las coordenadas de la bomba\n");
            printf("Fila:\n");
            scanf("%d", &fila);
            printf("Columna:\n");
            scanf("%d", &columna);
            columna--;
            fila--;
            printf("Indique forma en que explota la bomba\n");
            printf("1. (Punto) 2. (X)\n");
            printf("Su input:\n");
            scanf("%d", &bombofica);
            if(bombofica == 1){
                bombito->contador_turnos = 1;
                bombito->explotar = ExplosionPunto;
            }
            else if(bombofica == 2){
                bombito->contador_turnos = 3;
                bombito->explotar = ExplosionX;
            }
            ColocarBomba(bombito,fila,columna);
        }
        if(opcion == 2){
            MostrarBombas();
        }
        if(opcion == 3){
            VerTesoros();
        }
        if(opcion == 4){
            BorrarTablero();
            cont_tesoro = 0;
        }
        printf("\n");
        turno++;
        PasarTurno();
    }
    BorrarTablero();
    return 0;
}

/* EJEMPLOS DE RANDOM PARA FACILITAR SU USO.
*   funcion para combrobar los terosos totales
*   srand(time(0)); // Setea la seed del random.
*   int ejemplo_vida = (rand() % 3) + 1; // Obtiene al azar la vida de Tierra a asignar.
*/