#include "Juego.h"
#include "Bandido.h"
#include "Utils.h"
int ingresarJugador(tJugador *jugador)
{
    char nickname[TAM_NICKNAME];
    FILE *archivo;

    printf("Ingrese su nickname: ");
    fgets(nickname, TAM_NICKNAME , stdin);
    nickname[strcspn(nickname, "\n")] = '\0';  // elimina el \n que deja fgets


    if (abrirArchivo(&archivo,ARCH_JUGADORES, "a+b") != EXITO)
        return ERROR_APERTURA;

    if (buscarJugador(archivo, nickname, jugador) == JUGADOR_INEXISTENTE)
    {
        printf("Jugador nuevo, dando de alta...\n");
        darDeAltaJugador(archivo, nickname, jugador);
    }
    else
    {
        printf("Bienvenido de vuelta, %s!\n", jugador->nickname);
    }
    fclose(archivo);

    return EXITO;
}


void mostrarMenu(tJugador *jugador, tConfig *config)
{
    int opcion;

    do {
        printf("\n=== CARAVANA DEL DESIERTO ===\n");
        printf("1. Jugar nueva partida\n");
        printf("2. Ver ranking\n");
        printf("3. Ayuda\n");
        printf("4. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
           /* case 1:
                jugarPartida(jugador, config);
                break;
            case 2:
                mostrarRanking();
                break;
            case 3:
                mostrarAyuda();
                break;  */
            case 4:
                printf("Hasta luego, %s!\n", jugador->nickname);
                break;
            default:
                printf("Opcion invalida\n");
        }
    } while (opcion != 4);

}

int inicializarPartida(tJugador* jugador,tTablero* tablero, tConfig *config)
{
    int ret;

    ret=cargarConfiguracion(ARCH_CONFIGURACION,config);
    if(ret != EXITO)
        return ret;

    ret=generarTablero(tablero,config);

    if(ret != EXITO)
        return ret;

    ret=validarTablero(tablero);
    if(ret != EXITO)
        return ret;
    inicializarEstadoJugador(jugador,config->vidas_inicio,tablero->inicio);

    return EXITO;

}

int prepararTurno(tJugador* jugador,tTablero* tablero, tCola *colaMovimientos)
{
    int ret;
    unsigned dado;
    tMovimiento mov;
    tBandido *bandido;
    tLista *pl=&tablero->bandidos;

    if(jugador->pierdeTurno)
    {
        jugador->pierdeTurno=0;
    }else
    {
        dado=tirarDado();
        ret=generarMovimientoJugador(jugador,tablero,dado,&mov);
        if(ret!=EXITO)
            return ret;
        ret=encolar(colaMovimientos,&mov,sizeof(tMovimiento));
        if(ret!=EXITO)
            return ret;

    }


    while(*pl)
    {
        bandido=(tBandido*)(*pl)->info;
        if(bandido->activo)
        {
            mov=generarMovimientoBandido(bandido,jugador,tablero);
            ret=encolar(colaMovimientos,&mov,sizeof(tMovimiento));
            if(ret!=EXITO)
                return ret;
        }
        pl=&(*pl)->sig;
    }

    return EXITO;

}
