#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Proyecto/Juego.h"

int main()
{
    tConfig config;
    tJugador jugador;
    tTablero tablero;
    int ret;
    /*Carga de arbol en memoria a partir de archivo indice*/
    tArbol indiceJugador;
    crearArbolB(&indiceJugador);
    cargarIndiceJugadores(&indiceJugador, ARCH_JUGADORES_IDX, ARCH_JUGADORES);
    srand(time(NULL));

    do
    {
        ret=ingresarJugador(&jugador, &indiceJugador);
        if(ret==ERROR_APERTURA)
        {
            printf("Error critico: No se pudo abrir el archivo de jugadores. Vuelva a iniciar sesion\n");
            return 1;
        }
    }while (ret== ERROR_JUGADOR_NO_ENCONTRADO);

    mostrarMenu(&jugador,&tablero,&config);
    guardarIndiceJugadores(&indiceJugador, ARCH_JUGADORES_IDX);
//    probarGenerarTablero();

    return 0;
}
