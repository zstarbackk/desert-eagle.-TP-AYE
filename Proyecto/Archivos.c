#include "Archivos.h"

int buscarJugadoresPorNombre(FILE* archivo, char* nombre, tLista* resultados)
{
    tJugadorArchivo registro;
    char nickname[TAM_NICKNAME];
    int cantidad = 0;
    unsigned tamRegistro = sizeof(tJugadorArchivo);

    rewind(archivo);
    while(fread(&registro, tamRegistro, 1, archivo) == 1)
    {
        if(strcasecmp(registro.nombre, nombre) == 0)
        {
            strcpy(nickname, registro.nickname);
            if(insertarAlFinal(resultados, nickname, TAM_NICKNAME) != EXITO)
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
int crearArchivoAyuda(const char* nombreArchivo)
{
    FILE* archivo = fopen(nombreArchivo, "wt");

    if(!archivo)
        return ERROR_APERTURA;

    fprintf(archivo, "=== AYUDA - CARAVANA DEL DESIERTO ===\n\n");
    fprintf(archivo, "Objetivo:\n");
    fprintf(archivo, "Llegar desde el Campamento Inicial (I) hasta la Ciudad Refugio (S) sin perder todas tus vidas.\n\n");

    fprintf(archivo, "Como jugar:\n");
    fprintf(archivo, "- En cada turno tiras un dado de 1 a 6.\n");
    fprintf(archivo, "- El numero obtenido indica exactamente cuantas posiciones debes moverte.\n");
    fprintf(archivo, "- Puedes elegir avanzar (F) o retroceder (B), si el movimiento es valido.\n");
    fprintf(archivo, "- Si avanzas y pasas la salida, rebotas hacia atras con los pasos sobrantes.\n");
    fprintf(archivo, "- No puedes retroceder atravesando el inicio.\n\n");

    fprintf(archivo, "Casilleros:\n");
    fprintf(archivo, "I = Inicio\n");
    fprintf(archivo, "S = Salida\n");
    fprintf(archivo, "P = Premio: suma 1 punto\n");
    fprintf(archivo, "V = Vida extra: suma 1 vida\n");
    fprintf(archivo, "O = Oasis: protege contra el proximo peligro\n");
    fprintf(archivo, "T = Tormenta: pierdes el proximo turno si no estas protegido\n");
    fprintf(archivo, "B = Bandido: si te intercepta, pierdes 1 vida y vuelves al inicio\n");
    fprintf(archivo, ". = Casillero despejado\n\n");

    fprintf(archivo, "Bandidos:\n");
    fprintf(archivo, "- Se mueven automaticamente despues del jugador.\n");
    fprintf(archivo, "- Intentan acercarse por el camino mas corto.\n\n");

    fprintf(archivo, "Fin de la partida:\n");
    fprintf(archivo, "- Ganas si llegas a la Ciudad Refugio.\n");
    fprintf(archivo, "- Pierdes si te quedas sin vidas.\n");
    fprintf(archivo, "- Al finalizar se muestra tu historial de movimientos.\n");

    fclose(archivo);
    return EXITO;
}

int mostrarAyuda(const char* nombreArchivo)
{
    FILE* archivo = fopen(nombreArchivo, "rt");
    char linea[200];

    if(!archivo)
    {
        if(crearArchivoAyuda(nombreArchivo) != EXITO)
            return ERROR_APERTURA;

        archivo = fopen(nombreArchivo, "rt");

        if(!archivo)
            return ERROR_APERTURA;
    }

    system("cls");

    while(fgets(linea, sizeof(linea), archivo))
        printf("%s", linea);

    fclose(archivo);
    return EXITO;
}



