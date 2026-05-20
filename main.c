#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Proyecto/Juego.h"

int main()
{
    tJugador jugador;
    srand(time(NULL));
    if(ingresarJugador(&jugador)!= EXITO)
    {
        printf("Error critico: no se pudo abrir el archivo de jugadores. Vuelva a iniciar sesion\n");
        return 0;
    }
    return 0;
}
