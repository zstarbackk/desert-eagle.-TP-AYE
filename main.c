#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Proyecto/Juego.h"

int main()
{
    tConfig config;
    tJugador jugador;
    tTablero tablero;
//
   srand(time(NULL));
//
//    if (!leerConfiguracion(ARCH_CONFIGURACION, &config))
//    {
//        printf("Error critico: No fue posible extraer las configuraciones iniciales.\nPongase en contacto con el equipo desarrollador\n");
//        return 1;
//    }
//
//    if (!validarConfig(&config))
//    {
//        printf("Error critico: Las configuraciones iniciales son inadecuadas para desplegar el juego.\nPongase en contacto con el equipo desarrollador\n");
//        return 1;
//    }
//
    if(ingresarJugador(&jugador)!= EXITO)
    {
        printf("Error critico: No se pudo abrir el archivo de jugadores. Vuelva a iniciar sesion\n");
        return 1;
    }
//
    mostrarMenu(&jugador,&tablero,&config);
//    probarGenerarTablero();

    return 0;
}
