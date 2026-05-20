#include "Juego.h"

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
