#include "Archivos.h"

int obtenerPosicionJugador(FILE *archivo, const char *nickname)     //Para implementar el arbol solo se modifica esta funcion.
{
    tJugadorArchivo registro;
    int posicion = 0;

    rewind(archivo);

    while (fread(&registro, sizeof(tJugadorArchivo), 1, archivo) == 1)
    {
        if (strcmp(registro.nickname, nickname) == 0)
            return posicion;
        posicion++;
    }
    return JUGADOR_INEXISTENTE;
}

int buscarJugador(FILE *archivo,const char *nickname, tJugador *jugador)
{
    tJugadorArchivo registro;
    int posicion;

    posicion = obtenerPosicionJugador(archivo, nickname);
    if (posicion == JUGADOR_INEXISTENTE)
        return JUGADOR_INEXISTENTE;

    fseek(archivo, posicion * sizeof(tJugadorArchivo), SEEK_SET);
    fread(&registro, sizeof(tJugadorArchivo), 1, archivo);
    jugador->idJugador = registro.idJugador;
    strcpy(jugador->nickname, registro.nickname);

    return EXITO;
}



int obtenerUltimoId(FILE *archivo)
{
    tJugadorArchivo registro;
    int ultimoId = 0;

    rewind(archivo);

    while (fread(&registro, sizeof(tJugadorArchivo), 1, archivo) == 1)
        ultimoId = registro.idJugador;

    return ultimoId;
}

void darDeAltaJugador(FILE *archivo,const char *nickname, tJugador *jugador)
{
    tJugadorArchivo registro;

    registro.idJugador = obtenerUltimoId(archivo) + 1;
    strcpy(registro.nickname, nickname);
    fseek(archivo,0,SEEK_END);

    fwrite(&registro, sizeof(tJugadorArchivo), 1, archivo);

    jugador->idJugador = registro.idJugador;
    strcpy(jugador->nickname, nickname);
}
