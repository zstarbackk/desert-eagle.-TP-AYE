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

    srand(time(NULL));

    do
    {
        ret=ingresarJugador(&jugador);
        if(ret==ERROR_APERTURA)
        {
            printf("Error critico: No se pudo abrir el archivo de jugadores. Vuelva a iniciar sesion\n");
            return 1;
        }
    }while (ret== ERROR_JUGADOR_NO_ENCONTRADO);

    mostrarMenu(&jugador,&tablero,&config);
//    probarGenerarTablero();

    return 0;
}
