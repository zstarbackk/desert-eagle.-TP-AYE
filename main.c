#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Proyecto/Juego.h"

int main()
{
    tConfig config;
    tJugador jugador;
    tTablero tablero;
    tArbol indiceJugador;

    crearArbolB(&indiceJugador);
    cargarIndiceJugadores(&indiceJugador, ARCH_JUGADORES_IDX, ARCH_JUGADORES);
    srand(time(NULL));


    if(ingresarJugador(&jugador, &indiceJugador)!=EXITO)
    {
        printf("Error en la autenticacion. Vuelva a iniciar sesion\n");
        exit(1);
    }
    guardarIndiceJugadores(&indiceJugador,ARCH_JUGADORES_IDX);
    mostrarMenu(&jugador,&tablero,&config);

//  probarGenerarTablero();

    return 0;
}
