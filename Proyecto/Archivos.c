#include "Archivos.h"

int buscarJugadoresPorNombre(FILE* archivo, char* nombre, tLista* resultados)
{
    tJugadorArchivo registro;
    int cantidad = 0;

    rewind(archivo);
    while(fread(&registro, sizeof(tJugadorArchivo), 1, archivo) == 1)
    {
        if(strcmp(registro.nombre, nombre) == 0)
        {

            if(insertarAlFinal(resultados,&registro,sizeof(tJugadorArchivo))!=EXITO)
                return ERROR;

            cantidad++;
        }
    }
    return cantidad;
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


