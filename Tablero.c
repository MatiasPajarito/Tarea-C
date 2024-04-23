#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"

const int prob[5]={1,2,3,4,5};
int liberado = 0;

void*** tablero;
int** matriz; // (0 = Bomba - 1 = tierra - 2 = Tesoro)
int dimension;
int cont_tesoro;

void IniciarTablero(int n){   
//Funcion Iniciar Tablero
/*
***
* parametro_1 : Tipo Entero - Es la dimension del tablero
* 
* La funcion crea un tablero del tamanio dimension, la cual asigna memoria para el
* tablero del juego y a cada una de las casillas del juego.
* Luego se le asiga una vida aleatoria a cada casilla, este numero va desde el 1 al 3
*/
    tablero = malloc(n*sizeof(void**));
    matriz = malloc(sizeof(int*) * dimension);
    if(tablero == NULL){
        printf("%s", "error con la memoria \n");
        exit(1);
    }   
    for(int i=0 ; i<n ; i++){
        tablero[i] = malloc(n*sizeof(void*));
        matriz[i] = malloc(sizeof(int) * dimension);
        for(int j=0 ; j<n ; j++){
            Tierra* tierra = malloc(sizeof(Tierra));
            tierra->vida = (rand() % 3) + 1;
            int probabilidad = (rand() % 100);
            int algo = 0;
            for (int c=0 ; c<5 ; c++){
                if(probabilidad==prob[c]){
                    algo = 1;
                }
            }
            tierra->es_tesoro = algo;
            tablero[i][j] = tierra;
            matriz[i][j] = 1;
            if(tierra->es_tesoro == 1){
                cont_tesoro++;
            }
        }
    }
}

void PasarTurno(){
// Funcion PasarTurno
/*
*** Esta funcion no recibe parametros
*
* 
* La funcion literalmente pasa el turno, esta itera el tablero y llama a la
* funcion TryExplotar() para cada casilla
*/
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(matriz[i][j] == 0){
                TryExplotar(i,j);
            }
        }
    }
}

void ColocarBomba(Bomba* b, int fila, int columna){
    // Funcion ColocarBomba
    /*
    ***
    * parametro_1 : Tipo Puntero - Creamos la bomba gracias al puntero
    * parametro_2 : Tipo Entero - Este se usa para reconocer la fila de el tablero
    * parametro_3 : Tipo Entero - Esta nos reconoce la columna del tablero
    ***
    La Funcion simplemente con las coordenadas implementa una bomba en la casilla 
    que se asigno.
    */
    Tierra* puntero_tierra = (Tierra*)tablero[fila][columna];
    b->tierra_debajo = puntero_tierra;
    tablero[fila][columna] = b;
    matriz[fila][columna] = 0;
}

void MostrarTablero(){
    // Funcion MostrarTablero
    /*
    *** Esta funcion no recibe parametros
    *
    * 
    * Esta funcion recorre todo el tablero y muestra el tablero con la vida 
    * de las tierras dependiendo la selda en la que este.
    */
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if(matriz[i][j]==1){
                Tierra* tierra = (Tierra*)tablero[i][j];
                if(tierra->vida <= 0){
                    printf("0 | ");
                }
                else{
                    printf("%d | ",tierra->vida);
                }
            }
            else if(matriz[i][j]==0){
                printf("o | ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void MostrarBombas(){
    // Funcion MostrarBombas
    /*
    *** Esta Funcion no recibe ningun
    *
    * Esta Funcion muestra todos los datos de cada bomba que exista en el tablero
    * para asi revisar cada bomba y el estado que estan.
    */
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(matriz[i][j] == 0){
                Bomba* b = (Bomba*)tablero[i][j];
                printf("____________________________________________\n");
                printf("Turnos para explotar %d\n", b->contador_turnos);
                printf("Coordenadas: %d %d\n", i+1,j+1);
                if(b->explotar == ExplosionPunto){
                    printf("Forma de la Explosion: Explosion en Punto\n");
                }
                else if(b->explotar == ExplosionX){
                    printf("Forma de la Explosion: Explosion en X\n");
                }
                printf("Vida de Tierra Debajo: %d\n", b->tierra_debajo->vida);
                printf("____________________________________________\n");
            }
        }
    }
}

void VerTesoros(){
    // Funcion VerTesoros
    /*
    *** Esta Funcion no recibe ningun
    *
    * Esta Funcion muestra todos los tesoros que hay en el tablero
    */
    printf("Tesoros\n");
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            Tierra* tierra = (Tierra*)tablero[i][j];
            if(tierra->es_tesoro){
                printf("* | ");
            }
            else{
                if(tierra->vida <=0){
                    printf("0 | ");
                }
                else{
                    printf("%d | ", tierra->vida);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void BorrarTablero(){
    // Funcion BorrarTablero 
    /*
    *** Esta Funcion como varias otras no recibe parametros
    *
    * La función libera toda la memoria que se ha asignado al tablero de juego, 
    * lo que permite que el programa libere la memoria y se libere de los recursos 
    * que ya no son necesarios.
    */
    for (int i=0 ; i<dimension ; i++){
        for(int j=0 ; j<dimension ; j++){
            // pequenio fixeo
            Tierra* tierra= (Tierra*)tablero[i][j];
            free(tierra);
        }
        free(tablero[i]);
        free(matriz[i]);
    }
    free(tablero);
    free(matriz);
    liberado = 1;
}
