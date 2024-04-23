#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"

void TryExplotar(int fila, int columna){
    // Funcion TryExplotar
    /*
    ***
    * parametro_1 : Tipo Int - Este se usa para reconocer la fila de el tablero
    * parametro_2 : Tipo Int - Esta nos reconoce la columna del tablero
    ***
    * Esta funcion busca cada bomba y recude en 1 el contador de la bomba, si este contador
    * llega a 0 la bomba explota
    */
    Bomba* bomb = (Bomba*)tablero[fila][columna];
    bomb->contador_turnos--;
    if(bomb->contador_turnos == 0){
        bomb->explotar(fila,columna);
    }
}

void BorrarBomba(int fila, int columna){
    // Funcion BorrarBomba
    /*
    ***
    * parametro_1 : Tipo Int - Este se usa para reconocer la fila de el tablero
    * parametro_2 : Tipo Int - Esta nos reconoce la columna del tablero
    ***
    * La funcion borra la bomba del tablero de juego. Comprueba si la casilla contiene
    * una bomba, la funcion libera la memoria asignada y reemplaza con tierra.
    */
    Bomba* bomb = (Bomba*)tablero[fila][columna];
    if(bomb != NULL){
        Tierra* tierra = bomb->tierra_debajo;
        tablero[fila][columna] = tierra;
        free(bomb);
        matriz[fila][columna] = 1;
    }
}

void ExplosionPunto(int fila, int columna){
    // Funcion ExplosionPunto
    /*
    ***
    * parametro_1 : Tipo Int - Este se usa para reconocer la fila de el tablero
    * parametro_2 : Tipo Int - Esta nos reconoce la columna del tablero
    ***
    * La funcion explota la bomba en la casilla dada, esta redice la vida de la tierra en 3
    * si la vida llega a 0 esta comprueba si es que existe un tesoro reduce el contador en 1
    * para asi ir buscando los demas tesoros, finalmente llama a la funcion BorrarBomba para
    * borrar la bomba obviamente
    */
    Bomba* bomb = (Bomba*)tablero[fila][columna];
    bomb->tierra_debajo->vida -= 3;
    if(bomb->tierra_debajo->vida <= 0){
        if(bomb->tierra_debajo->es_tesoro == 1){
            cont_tesoro--;
        }
    }
    BorrarBomba(fila,columna);
}

void ExplosionX(int fila, int columna){
    // Funcion ExplosionX
    /*
    ***
    * parametro_1 : Tipo Int - Este se usa para reconocer la fila de el tablero
    * parametro_2 : Tipo Int - Esta nos reconoce la columna del tablero
    ***
    * La funcion explota la bomba en una casilla especifica y en sus casisllas adyacentes. La funcion
    * reduce la vida de la tierra que se encuentra debajo de la bomba en 1 y por ultimo llama a la 
    * funcion BorrarBomba()
    */
    Tierra* t_izq_up = (Tierra*)tablero[fila-1][columna-1];
    Tierra* t_der_up = (Tierra*)tablero[fila-1][columna+1];
    Tierra* t_izq_down = (Tierra*)tablero[fila+1][columna-1];
    Tierra* t_der_down = (Tierra*)tablero[fila+1][columna+1];
    Bomba* bomb = (Bomba*)tablero[fila][columna];
    bomb->tierra_debajo->vida--;
    t_izq_down->vida--;
    t_der_down->vida--;
    t_izq_up->vida--;
    t_der_up->vida--;
    BorrarBomba(fila,columna);
}