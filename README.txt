Nombre: Matias Antonio Pajarito Catalan
Rol: 202273522-8

Bueno primero que nada tuve que crear una forma alternativa para cerrar el programa
en caso que no se pueda terminar el programa, este es con la opcion 4 el programa
termina pero arroja un error, no hay memory leak pero si ese error, que es un
segmentation fault.

En el programa implemente dos matrices una siendo el tablero y otra para comprobar
las bombas, tambien tenemos dos variables globales que son dimension y cont_tesoro,
estas son para la ejecuccion del programa, dimension como dice la palabra es para
medir las dimensiones del tablero y por ultimo cont_tesoro es para ver la cantidad
de tesoros en el tablero.

En Tablero.c estan los comentarios de cada funcion con sus respectivos parametros 
aquellas funciones que lo ameritan y obviamente una breve descripcion de esta misma.

Deje un comentario en la linea 12 de Tablero.C para identificar que tipo son.

En el main funciona todo bien sin fallas, excepto al terminar el programa me da un 
error que por mas que lo intente arreglar no pasaba nada. Lo unico que falla asi como
tal serian los contadores de tesoros al marcarlos cuando se encuentran en una explosion

En el makefile esta el ejecutable "ejec" con ese deberia ser suficiente
para hacer correr el programa y para hacerlo debe ser de la siguiente
forma: ./ejec y ya deberia correr.