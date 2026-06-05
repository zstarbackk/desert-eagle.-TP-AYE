#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Proyecto/Juego.h"

int main()
{
    tConfig config;
    tJugador jugador;
    tTablero tablero;

    srand(time(NULL));

    if(ingresarJugador(&jugador)!=EXITO)
    {
        printf("Error en la autenticacion. Vuelva a iniciar sesion\n");
        exit(1);
    }

    mostrarMenu(&jugador,&tablero,&config);
//  probarGenerarTablero();

    return 0;
}
