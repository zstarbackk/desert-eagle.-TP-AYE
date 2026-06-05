#include "Archivos.h"

int buscarJugadoresPorNombre(FILE* archivo, char* nombre, tJugadorArchivo* resultados)
{
    tJugadorArchivo registro;
    int cantidad = 0;

    rewind(archivo);
    while(fread(&registro, sizeof(tJugadorArchivo), 1, archivo) == 1)
    {
        if(strcmp(registro.nombre, nombre) == 0)
        {
            (resultados+cantidad)->idJugador = registro.idJugador;
            strcpy((resultados+cantidad)->nombre,registro.nombre);
            strcpy((resultados+cantidad)->nickname,registro.nickname);
            cantidad++;
        }
    }
    return cantidad;
}

unsigned obtenerPosicionJugador(FILE *archivo, const char *nickname)     //Para implementar el arbol solo se modifica esta funcion.
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



unsigned obtenerUltimoIdJugador(FILE *archivo)
{
    tJugadorArchivo registro;
    int ultimoId = 0;

    rewind(archivo);

    while (fread(&registro, sizeof(tJugadorArchivo), 1, archivo) == 1)
        ultimoId = registro.idJugador;

    return ultimoId;
}

void darDeAltaJugador(FILE *archivo,const char *nombre, const char *nickname, tJugador *jugador)  //deberia actualizar el indice
{
    tJugadorArchivo registro;

    registro.idJugador = obtenerUltimoIdJugador(archivo) + 1;
    strcpy(registro.nombre,nombre);
    strcpy(registro.nickname, nickname);
    fseek(archivo,0,SEEK_END);

    fwrite(&registro, sizeof(tJugadorArchivo), 1, archivo);

    jugador->idJugador = registro.idJugador;
    strcpy(jugador->nickname, nickname);
}

unsigned obtenerUltimoIdPartida(FILE* archivo)
{
    tPartida partida;
    unsigned ultimoId = 0;

    rewind(archivo);

    while(fread(&partida, sizeof(tPartida), 1, archivo) == 1)
        ultimoId = partida.idPartida;

    return ultimoId;
}

int guardarPartida(const char* nombreArchivo, const tJugador* jugador, tResultadoPartida resultado)
{
    FILE* archivo;
    tPartida partida;
    unsigned idPartida;

    if(abrirArchivo(&archivo, nombreArchivo, "a+b") != EXITO)
        return ERROR_APERTURA;

    idPartida = obtenerUltimoIdPartida(archivo) + 1;

    crearPartida(&partida, idPartida, jugador, resultado);

    fseek(archivo, 0, SEEK_END);

    if(fwrite(&partida, sizeof(tPartida), 1, archivo) != 1)
    {
        fclose(archivo);
        return ERROR_ESCRITURA;
    }

    fclose(archivo);
    return EXITO;
}


